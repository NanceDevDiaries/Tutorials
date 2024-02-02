#pragma once

#include "DataSource/GameSettingDataSourceDynamic.h" // IWYU pragma: keep
#include "GameSettingRegistry.h"
#include "Settings/LyraSettingsLocal.h" // IWYU pragma: keep

#include "LyraGameSettingRegistry.generated.h"

UCLASS()
class ULyraGameSettingRegistry : public UGameSettingRegistry
{
	GENERATED_BODY()

public:
	// ... other code
	UGameSettingCollection* InitializeGamepadSettings(ULyraLocalPlayer* InLocalPlayer);

	// @Game-Change initialize accessibility settings
	UGameSettingCollection* InitializeAccessibilitySettings(ULyraLocalPlayer* InLocalPlayer);
	
	// ... other code

	UPROPERTY()
	TObjectPtr<UGameSettingCollection> GamepadSettings;

	// @Game-Change game setting collection for accessibility
	UPROPERTY()
	TObjectPtr<UGameSettingCollection> AccessibilitySettings;
};
