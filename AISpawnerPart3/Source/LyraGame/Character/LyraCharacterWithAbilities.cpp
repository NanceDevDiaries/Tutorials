#include "LyraPawnData.h" // @Game-Change 
#include "LyraPawnExtensionComponent.h" // @Game-Change 
#include "AbilitySystem/LyraAbilitySet.h" // @Game-Change 
#include "Components/GameFrameworkComponentManager.h"  // @Game-Change 

// @Game-Change name for the stage when we're ready for the abilities
const FName ALyraCharacterWithAbilities::NAME_LyraAbilityReady("LyraAbilitiesReady");

/* @Game-Change start since the ability system lives here and not on the playerState we want to set the ability set here */
void ALyraCharacterWithAbilities::SetPawnData(const ULyraPawnData* InPawnData)
{
	check(InPawnData);

	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	for (const ULyraAbilitySet* AbilitySet : InPawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
		}
	}

	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, NAME_LyraAbilityReady);
}

void ALyraCharacterWithAbilities::OnAbilitySystemInitialized()
{
	Super::OnAbilitySystemInitialized();

	if (const ULyraPawnExtensionComponent* LyraPawnExtensionComponent = ULyraPawnExtensionComponent::FindPawnExtensionComponent(this))
	{
		SetPawnData(LyraPawnExtensionComponent->GetPawnData<ULyraPawnData>());
	}
}
/* @Game-Change end since the ability system lives here and not on the playerState we want to set the ability set here */
