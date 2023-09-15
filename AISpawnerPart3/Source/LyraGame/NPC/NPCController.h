#pragma once

#include "CoreMinimal.h"
#include "ModularAIController.h"
#include "Teams/LyraTeamAgentInterface.h"
#include "NPCController.generated.h"

/**
 * ANPCController
 *
 *	The controller class used by NPC bots in this project that don't need a PlayerState, mostly just PawnWithAbilities and CharacterWithAbilities
 */
UCLASS(Blueprintable)
class LYRAGAME_API ANPCController : public AModularAIController, public ILyraTeamAgentInterface
{
	GENERATED_BODY()

public:
	ANPCController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~ILyraTeamAgentInterface interface
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
	virtual FOnLyraTeamIndexChangedDelegate* GetOnTeamIndexChangedDelegate() override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~End of ILyraTeamAgentInterface interface

	//Update Team Attitude for the AI
	UFUNCTION(BlueprintCallable, Category = "Lyra AI Player Controller")
	void UpdateTeamAttitude(UAIPerceptionComponent* AIPerception);
private:
	// Keep track of TeamID if there's no PlayerState. No OnRep because AIController only exists on Server 
	UPROPERTY()
	FOnLyraTeamIndexChangedDelegate OnTeamChangedDelegate;
	
	UPROPERTY()
	FGenericTeamId MyTeamID = FGenericTeamId::NoTeam;
};

