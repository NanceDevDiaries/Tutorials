// Add at the top under #include "Engine/World.h"
#include "Teams/LyraTeamSubsystem.h"

void ULyraHealthComponent::HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayEffectSpec& DamageEffectSpec, float DamageMagnitude)
{
#if WITH_SERVER_CODE
	if (AbilitySystemComponent)
	{
		// Send the "GameplayEvent.Death" gameplay event through the owner's ability system.  This can be used to trigger a death gameplay ability.
		{
			FGameplayEventData Payload;
			Payload.EventTag = LyraGameplayTags::GameplayEvent_Death;
			Payload.Instigator = DamageInstigator;
			Payload.Target = AbilitySystemComponent->GetAvatarActor();
			Payload.OptionalObject = DamageEffectSpec.Def;
			Payload.ContextHandle = DamageEffectSpec.GetEffectContext();
			Payload.InstigatorTags = *DamageEffectSpec.CapturedSourceTags.GetAggregatedTags();
			Payload.TargetTags = *DamageEffectSpec.CapturedTargetTags.GetAggregatedTags();
			Payload.EventMagnitude = DamageMagnitude;

			FScopedPredictionWindow NewScopedWindow(AbilitySystemComponent, true);
			AbilitySystemComponent->HandleGameplayEvent(Payload.EventTag, &Payload);
		}

		// Send a standardized verb message that other systems can observe
		{
			/** @Game-Change begin don't send elimination message if we're an NPC team **/
			bool bSkipEliminationMessage = false;
			if (ULyraTeamSubsystem* TeamSubsystem = UWorld::GetSubsystem<ULyraTeamSubsystem>(GetWorld()))
			{
				bSkipEliminationMessage |= TeamSubsystem->IsPartOfAnNPCTeam(AbilitySystemComponent->GetAvatarActor());
				// put |= in case there are other flags or reason we would want to not send this message
			}
			if (!bSkipEliminationMessage)
			{
				FLyraVerbMessage Message;
				Message.Verb = TAG_Lyra_Elimination_Message;
				Message.Instigator = DamageInstigator;
				Message.InstigatorTags = *DamageEffectSpec.CapturedSourceTags.GetAggregatedTags();
				Message.Target = ULyraVerbMessageHelpers::GetPlayerStateFromObject(AbilitySystemComponent->GetAvatarActor());
				Message.TargetTags = *DamageEffectSpec.CapturedTargetTags.GetAggregatedTags();
				//@TODO: Fill out context tags, and any non-ability-system source/instigator tags
				//@TODO: Determine if it's an opposing team kill, self-own, team kill, etc...

				UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
				MessageSystem.BroadcastMessage(Message.Verb, Message);
			}
			/** @Game-Change end don't send elimination message if we're an NPC team **/
		}

		//@TODO: assist messages (could compute from damage dealt elsewhere)?
	}

#endif // #if WITH_SERVER_CODE
}


