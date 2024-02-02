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
UCLASS()
class ULyraSettingsLocal : public UGameUserSettings
{

// ...More code
	UPROPERTY(Config)
	int32 NumberOfReplaysToKeep = 5;

	// @Game-Change start Accessibility settings
public:
	UFUNCTION()
	int32 GetUIScale() const { return UIScalePercent; }
	UFUNCTION()
	void SetUIScale(float InUIScale) { UIScalePercent = InUIScale;}

private:
	UPROPERTY(Config)
	int32 UIScalePercent = 100;
public:

	UFUNCTION()
	bool ShouldUseArachnophobiaMode() const { return bShouldUseArachnophobiaMode; }
	UFUNCTION()
	void SetShouldUseArachnophobiaMode(bool bEnabled) { bShouldUseArachnophobiaMode = bEnabled;}

private:

	UPROPERTY(Config)
	bool bShouldUseArachnophobiaMode = false;
	// @Game-Change end Accessibility settings
	
private:
	void OnAppActivationStateChanged(bool bIsActive);

	// ... more code

};