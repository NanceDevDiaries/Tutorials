// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities/GATargetActor_ActorPlacementFace.h"
#include "AbilitySystem/Abilities/GAWorldReticle_ActorVisualization.h"

#include "Engine/World.h"
#include "Abilities/GameplayAbilityWorldReticle_ActorVisualization.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GATargetActor_ActorPlacementFace)

// --------------------------------------------------------------------------------------------------------------------------------------------------------
//
//	AGATargetActor_ActorPlacementFace
//
// --------------------------------------------------------------------------------------------------------------------------------------------------------

AGATargetActor_ActorPlacementFace::AGATargetActor_ActorPlacementFace(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AGATargetActor_ActorPlacementFace::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ActorVisualizationReticle.IsValid())
	{
		ActorVisualizationReticle.Get()->Destroy();
	}

	Super::EndPlay(EndPlayReason);
}

void AGATargetActor_ActorPlacementFace::StartTargeting(UGameplayAbility* InAbility)
{
	Super::StartTargeting(InAbility);
	if (AActor *VisualizationActor = GetWorld()->SpawnActor(PlacedActorClass))
	{
		ActorVisualizationReticle = GetWorld()->SpawnActor<AGAWorldReticle_ActorVisualization>();
		ActorVisualizationReticle->InitializeReticleVisualizationInformation(SourceActor.Get(), VisualizationActor, PlacedActorMaterial);
		GetWorld()->DestroyActor(VisualizationActor);
	}
	if (AGameplayAbilityWorldReticle* CachedReticleActor = ReticleActor.Get())
	{
		ActorVisualizationReticle->AttachToActor(CachedReticleActor, FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		ReticleActor = ActorVisualizationReticle;
		ActorVisualizationReticle = nullptr;
	}
}

//Might want to override this function to allow for a radius check against the ground, possibly including a height check. Or might want to do it in ground trace.
//FHitResult AGameplayAbilityTargetActor_ActorPlacement::PerformTrace(AActor* InSourceActor) const

