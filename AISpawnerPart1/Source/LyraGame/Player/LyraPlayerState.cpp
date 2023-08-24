void ALyraPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());

	// @Game-Change delete CallOrRegister_OnExperienceLoaded section, logic moved to ALyraPlayerState::RegisterToExperienceLoadedToSetPawnData()
}

/** @Game-Change start delay OnExperienceLoaded to wait until the pawn is set, and so is their pawn data in their Pawn Extension Component
** for pawns that don't want to use the Pawn Data from the experience component. **/
void ALyraPlayerState::RegisterToExperienceLoadedToSetPawnData()
{
	if (bRegisteredToExperienceLoaded) return;
	
	const UWorld* World = GetWorld();
	if (World && World->IsGameWorld() && World->GetNetMode() != NM_Client)
	{
		const AGameStateBase* GameState = GetWorld()->GetGameState();
		check(GameState);

		ULyraExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
		check(ExperienceComponent);
		ExperienceComponent->CallOrRegister_OnExperienceLoaded(FOnLyraExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
	}

	bRegisteredToExperienceLoaded = true; // only set this once. In the player's case the PlayerState is persistant while it gets destroyed with the AIs that don't have a player 
}
/** @Game-Change end **/
