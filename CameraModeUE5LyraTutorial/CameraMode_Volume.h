// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/LyraCameraMode.h"
#include "CameraModeVolume.h"
#include "CameraMode_Volume.generated.h"


class ACameraModeVolume;
/**
 * 
 */
UCLASS(Abstract)
class LYRAGAME_API UCameraMode_Volume : public ULyraCameraMode
{
	GENERATED_BODY()

public:
	void SetVolume(ACameraModeVolume* volume);
	
	UPROPERTY(transient)
	TWeakObjectPtr<ACameraModeVolume> Volume;
};
