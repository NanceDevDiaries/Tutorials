// under #include "NativeGameplayTags.h"
#include "Teams/LyraTeamSubsystem.h"

void UAssistProcessor::OnEliminationMessage(FGameplayTag Channel, const FLyraVerbMessage& Payload)
{
	/** @Game-Change start filter out NPC killed player(s) assists. Unless you want that. **/
	if (const ULyraTeamSubsystem* TeamSubsystem = UWorld::GetSubsystem<ULyraTeamSubsystem>(GetWorld()))
	{
		if (TeamSubsystem->IsPartOfAnNPCTeam(Payload.Instigator))
		{
			return; // don't count assist if the killer is an NPC. Helps understanding why assist was higher than the number of kills per team
		}
	}
	/** @Game-Change end filter out NPC killed player(s) assists. Unless you want that. **/
	
	if (APlayerState* TargetPS = Cast<APlayerState>(Payload.Target))
	{
		// Grant an assist to each player who damaged the target but wasn't the instigator
		if (FPlayerAssistDamageTracking* DamageOnTarget = DamageHistory.Find(TargetPS))
		{
			for (const auto& KVP : DamageOnTarget->AccumulatedDamageByPlayer)
			{
				if (APlayerState* AssistPS = KVP.Key)
				{
					if (AssistPS != Payload.Instigator)
					{
						FLyraVerbMessage AssistMessage;
						AssistMessage.Verb = TAG_Lyra_Assist_Message;
						AssistMessage.Instigator = AssistPS;
						//@TODO: Get default tags from a player state or save off most recent tags during assist damage?
						//AssistMessage.InstigatorTags = ;
						AssistMessage.Target = TargetPS;
						AssistMessage.TargetTags = Payload.TargetTags;
						AssistMessage.ContextTags = Payload.ContextTags;
						AssistMessage.Magnitude = KVP.Value;

						UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
						MessageSubsystem.BroadcastMessage(AssistMessage.Verb, AssistMessage);
					}
				}
			}

			// Clear the damage log for the eliminated player
			DamageHistory.Remove(TargetPS);
		}
	}
}

