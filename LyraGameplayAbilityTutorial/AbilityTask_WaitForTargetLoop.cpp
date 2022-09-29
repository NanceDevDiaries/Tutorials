// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Task/AbilityTask_WaitForTargetLoop.h"

UAbilityTask_WaitForTargetLoop* UAbilityTask_WaitForTargetLoop::WaitForTargets_SphereOverlapPawn(
	UGameplayAbility* OwningAbility, float TargetScanRadius, float TargetScanRate,
	bool bShowDebug)
{
	UAbilityTask_WaitForTargetLoop* MyObj = NewAbilityTask<UAbilityTask_WaitForTargetLoop>(OwningAbility);
	MyObj->TargetScanRadius = TargetScanRadius;
	MyObj->TargetScanRate = TargetScanRate;
	MyObj->Debug = bShowDebug;

	return MyObj;
}

void UAbilityTask_WaitForTargetLoop::Activate()
{
	SetWaitingOnAvatar();

	const UWorld* World = GetWorld();
	World->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::PerformTrace, TargetScanRate, true);
}

void UAbilityTask_WaitForTargetLoop::PerformTrace()
{
	AActor* AvatarActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
	if (!AvatarActor)
	{
		return;
	}

	const UWorld* World = GetWorld();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(AvatarActor);

	constexpr bool bTraceComplex = false;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(UAbilityTask_WaitForTargets_Radius), bTraceComplex);
	Params.AddIgnoredActors(ActorsToIgnore);

	const FVector origin = AvatarActor->GetActorLocation();
	
	TArray<FOverlapResult> Overlaps;
	World->OverlapMultiByObjectType(Overlaps, origin, FQuat::Identity, FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(TargetScanRadius), Params);

	TArray<AActor*> RefreshedOverlapList;
	
	bool hasNewOverlappingPawn = false;
	for (int32 i = 0; i < Overlaps.Num(); ++i)
	{
		if (APawn* PawnActor = Overlaps[i].OverlapObjectHandle.FetchActor<APawn>())
		{
			RefreshedOverlapList.Add(PawnActor);
			if (!CurrentOverlappingPawns.Contains(PawnActor))
			{
				hasNewOverlappingPawn = true;
			}
		}
	}

	if (hasNewOverlappingPawn)
	{
		CurrentOverlappingPawns = RefreshedOverlapList;
		PawnsOverlappedChanged.Broadcast(CurrentOverlappingPawns);
	}

#if ENABLE_DRAW_DEBUG
	if (Debug)
	{
		const FColor DebugColor = Overlaps.Num() > 0 ? FColor::Red : FColor::Green;
		DrawDebugSphere(World, origin, TargetScanRadius, 16, DebugColor, false, TargetScanRate);
	}
#endif // ENABLE_DRAW_DEBUG
}

void UAbilityTask_WaitForTargetLoop::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);

	const UWorld* World = GetWorld();
	World->GetTimerManager().ClearTimer(TimerHandle);
}
