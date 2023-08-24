const ULyraPawnData* ALyraGameMode::GetPawnDataForController(const AController* InController) const
{
	/** @Game-Change start use the pawn data info if that's been setup. Useful for not using the experience default pawn data and/or when there's no playerState **/
	if (const ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(InController->GetPawn()))
	{
		if (const ULyraPawnData* PawnData = PawnExtComp->GetPawnData<ULyraPawnData>())
		{
			return PawnData;
		}
	}
	/** @Game-Change end **/
	
	// See if pawn data is already set on the player state
	if (InController != nullptr)
	{
		if (const ALyraPlayerState* LyraPS = InController->GetPlayerState<ALyraPlayerState>())
		{
			if (const ULyraPawnData* PawnData = LyraPS->GetPawnData<ULyraPawnData>())
			{
				return PawnData;
			}
		}
	}

	// If not, fall back to the the default for the current experience
	check(GameState);
	ULyraExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
	check(ExperienceComponent);

	if (ExperienceComponent->IsExperienceLoaded())
	{
		const ULyraExperienceDefinition* Experience = ExperienceComponent->GetCurrentExperienceChecked();
		if (Experience->DefaultPawnData != nullptr)
		{
			return Experience->DefaultPawnData;
		}

		// Experience is loaded and there's still no pawn data, fall back to the default for now
		return ULyraAssetManager::Get().GetDefaultPawnData();
	}

	// Experience not loaded yet, so there is no pawn data to be had
	return nullptr;
}
