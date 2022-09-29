// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetDataFilter.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitForTargetLoop.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPawnsOverlappedChangedEvent, const TArray<AActor*>&, OverlappedActors);

/**
 * 
 */
UCLASS()
class LYRAGAME_API UAbilityTask_WaitForTargetLoop : public UAbilityTask
{
	GENERATED_BODY()

public:
	virtual void OnDestroy(bool bInOwnerFinished) override;

	UPROPERTY(BlueprintAssignable)
	FPawnsOverlappedChangedEvent PawnsOverlappedChanged;
	
	/** Wait until we trace new set of target pawns.  This task automatically loops. */
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_WaitForTargetLoop* WaitForTargets_SphereOverlapPawn(UGameplayAbility* OwningAbility, float TargetScanRange = 100, float TargetScanRate = 0.100, bool bShowDebug = false);
	
protected:
	virtual void Activate() override;
	
	void PerformTrace();

	float TargetScanRadius = 100;
	float TargetScanRate = 0.100;
	float Debug = false;

	UPROPERTY()
	TArray<AActor*> CurrentOverlappingPawns;
private:
	FTimerHandle TimerHandle;
};
