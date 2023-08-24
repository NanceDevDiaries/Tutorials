#include "NPC/NPCSpawner.h"
#include "AbilitySystemGlobals.h"
#include "AIController.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Character/LyraPawnData.h"
#include "Character/LyraPawnExtensionComponent.h"
#include "GameFramework/PlayerState.h"
#include "GameModes/LyraExperienceManagerComponent.h"
#include "Teams/LyraTeamSubsystem.h"

ANPCSpawner::ANPCSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ANPCSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Delayed for the sake of the cosmetics components added in the experience
	
	// Listen for the experience load to complete
	const AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	ULyraExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceComponent);
	ExperienceComponent->CallOrRegister_OnExperienceLoaded_LowPriority(FOnLyraExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void ANPCSpawner::OnExperienceLoaded(const ULyraExperienceDefinition* Experience)
{
#if WITH_SERVER_CODE
	if (HasAuthority())
	{
		ServerCreateNPCs();
	}
#endif
}

void ANPCSpawner::ServerCreateNPCs()
{
	if (ControllerClass == nullptr)
	{
		return;
	}

	// Create them
	for (int32 Count = 0; Count < NumNPCToCreate; ++Count)
	{
		SpawnOneNPC();
	}
}

// similar to UAIBlueprintHelperLibrary::SpawnAIFromClass but we use the controller class defined here instead of the one set on the pawn
// #todo could make a new static function in  UAIBlueprintHelperLibrary, like SpawnAIFromClassSpecifyController
APawn* ANPCSpawner::SpawnAIFromClass(UObject* WorldContextObject, ULyraPawnData* LoadedPawnData, UBehaviorTree* BehaviorTreeToRun, FVector Location, FRotator Rotation, bool bNoCollisionFail, AActor *PawnOwner, TSubclassOf
                                     <AAIController> ControllerClassToSpawn)
{
	// GetWorld(), LoadedPawnData->PawnClass, BehaviorTree, GetActorLocation(), GetActorRotation(), true, this, ControllerClass
	
	APawn* NewPawn = NULL;

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World && *LoadedPawnData->PawnClass)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Owner = PawnOwner;
		ActorSpawnParams.ObjectFlags |= RF_Transient;	// We never want to save spawned AI pawns into a map
		ActorSpawnParams.SpawnCollisionHandlingOverride = bNoCollisionFail ? ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn : ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		// defer spawning the pawn to setup the AIController, else it spawns the default controller on spawn if set to spawn AI on spawn
		ActorSpawnParams.bDeferConstruction = ControllerClassToSpawn != nullptr;
		
		NewPawn = World->SpawnActor<APawn>(*LoadedPawnData->PawnClass, Location, Rotation, ActorSpawnParams);
		if (ControllerClassToSpawn)
		{
			NewPawn->AIControllerClass = ControllerClassToSpawn;
			if (ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(NewPawn))
			{
				PawnExtComp->SetPawnData(LoadedPawnData);
			}
			NewPawn->FinishSpawning(FTransform(Rotation, Location, GetActorScale3D()));
		}
		
		if (NewPawn != NULL)
		{
			if (NewPawn->Controller == NULL)
			{
				// NOTE: SpawnDefaultController ALSO calls Possess() to possess the pawn (if a controller is successfully spawned).
				NewPawn->SpawnDefaultController();
			}

			if (BehaviorTreeToRun != NULL)
			{
				AAIController* AIController = Cast<AAIController>(NewPawn->Controller);

				if (AIController != NULL)
				{
					AIController->RunBehaviorTree(BehaviorTreeToRun);
				}
			}
		}
	}

	return NewPawn;
}

void ANPCSpawner::OnSpawnedPawnDestroyed(AActor* DestroyedActor)
{
	if (!HasAuthority())
	{
		return;
	}

	//#todo remove from the SpawnedNPCList list correctly
	
	if (ShouldRespawn)
	{
		FTimerHandle RespawnHandle;
		GetWorldTimerManager().SetTimer(RespawnHandle, this, &ThisClass::SpawnOneNPC, RespawnTime, false);
	}
}

void ANPCSpawner::SpawnOneNPC()
{
	ULyraPawnData* LoadedPawnData = PawnData.Get();
	if (!PawnData.IsValid())
	{
		LoadedPawnData = PawnData.LoadSynchronous();
	}

	if (LoadedPawnData)
	{
		if (APawn* SpawnedNPC = SpawnAIFromClass(GetWorld(), LoadedPawnData, BehaviorTree, GetActorLocation(), GetActorRotation(), true, this, ControllerClass))
		{
			bool bWantsPlayerState = true;
			if (const AAIController* AIController = Cast<AAIController>(SpawnedNPC->Controller))
			{
				bWantsPlayerState = AIController->bWantsPlayerState;
			}
			
			if (ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(SpawnedNPC))
			{
				AActor* AbilityOwner = bWantsPlayerState ? SpawnedNPC->GetPlayerState() : Cast<AActor>(SpawnedNPC);
				
				if (UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(AbilityOwner))
				{
					PawnExtComp->InitializeAbilitySystem(Cast<ULyraAbilitySystemComponent>(AbilitySystemComponent), AbilityOwner);
				}
			}

			if (ULyraTeamSubsystem* TeamSubsystem = UWorld::GetSubsystem<ULyraTeamSubsystem>(GetWorld()))
			{
				TeamSubsystem->ChangeTeamForActor(SpawnedNPC->Controller, TeamID);
			}
			
			SpawnedNPCList.Add(Cast<AAIController>(SpawnedNPC->Controller));

			SpawnedNPC->OnDestroyed.AddDynamic(this, &ThisClass::OnSpawnedPawnDestroyed);
		}
	}
}
