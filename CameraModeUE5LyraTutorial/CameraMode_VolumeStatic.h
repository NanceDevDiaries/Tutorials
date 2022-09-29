// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraMode_Volume.h"
#include "CameraMode_VolumeStatic.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class LYRAGAME_API UCameraMode_VolumeStatic : public UCameraMode_Volume
{
	GENERATED_BODY()
	
public:

	UCameraMode_VolumeStatic();

protected:

	//~ULyraCameraMode interface
	virtual void UpdateView(float DeltaTime) override;
	//~End of ULyraCameraMode interface

	protected:
	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	float ArenaWidth;

	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	float ArenaHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	FRotator DefaultPivotRotation;

	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	FRuntimeFloatCurve BoundsSizeToDistance;
};
