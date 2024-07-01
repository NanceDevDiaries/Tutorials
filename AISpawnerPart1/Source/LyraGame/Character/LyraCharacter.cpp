#include "LyraPawnData.h" //Add this line to the beginning of the source if it does not exist

void ALyraCharacter::PossessedBy(AController* NewController)
{
	const FGenericTeamId OldTeamID = MyTeamID;

	Super::PossessedBy(NewController);

	/** @Game-Change begin replacement for ALyraPlayerState::PostInitializeComponents() binding to OnExperience ready.
	** Useful to ensure PawnExtension is ready with PawnData if pawn doesn't want to use default pawn data from the experience **/
	if (ALyraPlayerState* LyraPlayerState = GetLyraPlayerState())
	{
		if (GetWorld()->GetNetMode() < NM_Client)
		{
			if (const ULyraPawnData* PawnData = PawnExtComponent->GetPawnData<ULyraPawnData>())
			{
				// check if we already have pawn data. This will be true in the case of PlayerControllers, their PlayerState persists
				if (!LyraPlayerState->GetPawnData<ULyraPawnData>())
				{
					LyraPlayerState->SetPawnData(PawnData);
				}
			}
			else
			{
				// setup waiting for the experience to be loaded so we can use the pawn data from the experience
				LyraPlayerState->RegisterToExperienceLoadedToSetPawnData();
			}
		}
	}
	/** @Game-Change end **/

	PawnExtComponent->HandleControllerChanged();
	
	// Grab the current team ID and listen for future changes
	if (ILyraTeamAgentInterface* ControllerAsTeamProvider = Cast<ILyraTeamAgentInterface>(NewController))
	{
		MyTeamID = ControllerAsTeamProvider->GetGenericTeamId();
		ControllerAsTeamProvider->GetTeamChangedDelegateChecked().AddDynamic(this, &ThisClass::OnControllerChangedTeam);
	}
	ConditionalBroadcastTeamChanged(this, OldTeamID, MyTeamID);
}
