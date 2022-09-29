// Fill out your copyright notice in the Description page of Project Settings.

#include "LyraLogChannels.h"
#include "Character/ManaComponent.h"

#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LyraCombatSet.h"

UManaComponent::UManaComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	AbilitySystemComponent = nullptr;
	CombatSet = nullptr;
}

void UManaComponent::InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		UE_LOG(LogLyra, Error, TEXT("LyraManaComponent: Mana component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogLyra, Error, TEXT("LyraManaComponent: Cannot initialize Mana component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}

	CombatSet = AbilitySystemComponent->GetSet<ULyraCombatSet>();
	if (!CombatSet)
	{
		UE_LOG(LogLyra, Error, TEXT("LyraManaComponent: Cannot initialize Mana component for owner [%s] with NULL Mana set on the ability system."), *GetNameSafe(Owner));
		return;
	}

	// Register to listen for attribute changes.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ULyraCombatSet::GetManaAttribute()).AddUObject(this, &ThisClass::HandleManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ULyraCombatSet::GetMaxManaAttribute()).AddUObject(this, &ThisClass::HandleMaxManaChanged);
}

void UManaComponent::UninitializeFromAbilitySystem()
{
	CombatSet = nullptr;
	AbilitySystemComponent = nullptr;
}

float UManaComponent::GetMana() const
{
	return (CombatSet ? CombatSet->GetMana() : 0.0f);
}

float UManaComponent::GetMaxMana() const
{
	return (CombatSet ? CombatSet->GetMaxMana() : 0.0f);
}

float UManaComponent::GetManaNormalized() const
{
	if (CombatSet)
	{
		const float Mana = CombatSet->GetMana();
		const float MaxMana = CombatSet->GetMaxMana();

		return ((MaxMana > 0.0f) ? (Mana / MaxMana) : 0.0f);
	}

	return 0.0f;
}

void UManaComponent::OnUnregister()
{
	UninitializeFromAbilitySystem();
	
	Super::OnUnregister();
}

void UManaComponent::HandleManaChanged(const FOnAttributeChangeData& ChangeData)
{
	OnManaChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue);
}

void UManaComponent::HandleMaxManaChanged(const FOnAttributeChangeData& ChangeData)
{
	OnMaxManaChanged.Broadcast(this, ChangeData.OldValue, ChangeData.NewValue);
}
