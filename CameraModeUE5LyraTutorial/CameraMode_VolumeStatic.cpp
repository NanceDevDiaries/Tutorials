// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraMode_VolumeStatic.h"

#include "CameraModeVolume.h"

UCameraMode_VolumeStatic::UCameraMode_VolumeStatic()
{
	ArenaWidth = 1000.0f;
	ArenaHeight = 1000.0f;
}

void UCameraMode_VolumeStatic::UpdateView(float DeltaTime)
{
	FBox ArenaBounds(FVector(-ArenaWidth, -ArenaHeight, 0.0f), FVector(ArenaWidth, ArenaHeight, 100.0f));

	const double BoundsMaxComponent = ArenaBounds.GetSize().GetMax();

	const double CameraLoftDistance = BoundsSizeToDistance.GetRichCurveConst()->Eval(BoundsMaxComponent);
	
	FVector PivotLocation = ArenaBounds.GetCenter() - DefaultPivotRotation.Vector() * CameraLoftDistance;
	
	FRotator PivotRotation = DefaultPivotRotation;

	if (Volume.Get())
	{
		PivotRotation = FRotator(DefaultPivotRotation.Pitch, Volume->GetActorRotation().Yaw + 180, 0);
		PivotLocation = Volume->GetActorLocation() - PivotRotation.Vector() * CameraLoftDistance;
	}
	
	View.Location = PivotLocation;
	View.Rotation = PivotRotation;
	View.ControlRotation = View.Rotation;
	View.FieldOfView = FieldOfView;
}
