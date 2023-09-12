
TSubclassOf<ULyraCameraMode> ULyraHeroComponent::DetermineCameraMode() const
{
	/** @Game-Change  **/
	if (VolumeCameraMode)
	{
		return VolumeCameraMode;
	}

	if (AbilityCameraMode)
	{
		return AbilityCameraMode;
	}

	const APawn* Pawn = GetPawn<APawn>();
	if (!Pawn)
	{
		return nullptr;
	}

	if (ULyraPawnExtensionComponent* PawnExtComp = ULyraPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
	{
		if (const ULyraPawnData* PawnData = PawnExtComp->GetPawnData<ULyraPawnData>())
		{
			return PawnData->DefaultCameraMode;
		}
	}

	return nullptr;
}


/** @Game-Change **/
void ULyraHeroComponent::SetVolumeCameraMode(TSubclassOf<ULyraCameraMode> CameraMode)
{
	if (CameraMode)
	{
		VolumeCameraMode = CameraMode;
	}
}

void ULyraHeroComponent::ClearVolumeCameraMode()
{
	VolumeCameraMode = nullptr;
}

/** @Game-Change end **/