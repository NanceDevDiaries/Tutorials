// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraModeVolume.h"

#include "LyraCameraComponent.h"
#include "LyraCameraMode.h"
#include "Character/LyraHeroComponent.h"

void ACameraModeVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	if (!CameraMode)
	{
		return;
	}

	const APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn)
	{
		return;
	}

	if (ULyraCameraComponent* CameraComponent = ULyraCameraComponent::FindCameraComponent(Pawn))
	{
		CameraComponent->SetCameraVolume(this);
	}

	if (ULyraHeroComponent* heroComponent = ULyraHeroComponent::FindHeroComponent(OtherActor))
	{
		heroComponent->SetVolumeCameraMode(CameraMode);
	}
}

void ACameraModeVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	const APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn)
	{
		return;
	}

	if (ULyraCameraComponent* CameraComponent = ULyraCameraComponent::FindCameraComponent(Pawn))
	{
		CameraComponent->ClearCameraVolume();
	}
	
	if (ULyraHeroComponent* heroComponent = ULyraHeroComponent::FindHeroComponent(OtherActor))
	{
		heroComponent->ClearVolumeCameraMode();
	}
	
	Super::NotifyActorEndOverlap(OtherActor);
}
