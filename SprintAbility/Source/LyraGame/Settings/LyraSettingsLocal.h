// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/GameUserSettings.h"
#include "Input/LyraMappableConfigPair.h"
#include "InputCoreTypes.h"

#include "LyraSettingsLocal.generated.h"

enum class ECommonInputType : uint8;
enum class ELyraDisplayablePerformanceStat : uint8;
enum class ELyraStatDisplayMode : uint8;

class ULyraLocalPlayer;
class UObject;
class UPlayerMappableInputConfig;
class USoundControlBus;
class USoundControlBusMix;
struct FFrame;

/**
 * ULyraSettingsLocal
 */
UCLASS(BlueprintType) // @Lyra-Change get settings local from BP
class ULyraSettingsLocal : public UGameUserSettings
{
	GENERATED_BODY()

public:

	ULyraSettingsLocal();

	// ...some other code
	UPROPERTY(Config)
	int32 NumberOfReplaysToKeep = 5;

	// @Game-Change sprint toggle
public:

	UFUNCTION(BlueprintCallable, Category = Settings)
	bool WantsToUseTapForSprint() const { return bUseTapForSprint; }
	UFUNCTION()
	void SetWantsToUseTapForSprint(bool bWantsToUseTapForSprint) { bUseTapForSprint = bWantsToUseTapForSprint;}

private:

	// If true, player has to tap the sprint key to sprint, tap again to end.
	// If false, sprint will happen when they have the input down.
	UPROPERTY(Config)
	bool bUseTapForSprint = true;
	// @Game-Change end sprint toggle
	
private:
	void OnAppActivationStateChanged(bool bIsActive);
	// ....some other code
};
