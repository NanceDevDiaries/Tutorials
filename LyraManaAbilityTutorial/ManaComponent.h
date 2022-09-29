// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "ManaComponent.generated.h"

struct FOnAttributeChangeData;
class ULyraCombatSet;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMana_AttributeChanged, UManaComponent*, ManaComponent, float,
                                               OldValue, float, NewValue);

class ULyraAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class LYRAGAME_API UManaComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:
	UManaComponent(const FObjectInitializer& ObjectInitializer);

	// Returns the Mana component if one exists on the specified actor.
	UFUNCTION(BlueprintPure, Category = "Lyra|Mana")
	static UManaComponent* FindManaComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UManaComponent>() : nullptr); }

	// Initialize the component using an ability system component.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Mana")
	void InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC);

	// Uninitialize the component, clearing any references to the ability system.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Mana")
	void UninitializeFromAbilitySystem();

	// Returns the current Mana value.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Mana")
	float GetMana() const;

	// Returns the current maximum Mana value.
	UFUNCTION(BlueprintCallable, Category = "Lyra|Mana")
	float GetMaxMana() const;

	// Returns the current Mana in the range [0.0, 1.0].
	UFUNCTION(BlueprintCallable, Category = "Lyra|Mana")
	float GetManaNormalized() const;

public:

	// Delegate fired when the mana value has changed.
	UPROPERTY(BlueprintAssignable)
	FMana_AttributeChanged OnManaChanged;

	// Delegate fired when the max mana value has changed.
	UPROPERTY(BlueprintAssignable)
	FMana_AttributeChanged OnMaxManaChanged;

protected:
	virtual void OnUnregister() override;
	
	virtual void HandleManaChanged(const FOnAttributeChangeData& ChangeData);
	virtual void HandleMaxManaChanged(const FOnAttributeChangeData& ChangeData);

	
	// Ability system used by this component.
	UPROPERTY()
	ULyraAbilitySystemComponent* AbilitySystemComponent;

	// Mana set used by this component.
	UPROPERTY()
	const ULyraCombatSet* CombatSet;
};
