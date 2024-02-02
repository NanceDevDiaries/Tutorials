// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraGameSettingRegistry.h"

#include "GameSettingCollection.h"
#include "LyraSettingsLocal.h"
#include "LyraSettingsShared.h"
#include "Player/LyraLocalPlayer.h"

// ... other code

void ULyraGameSettingRegistry::OnInitialize(ULocalPlayer* InLocalPlayer)
{
	ULyraLocalPlayer* LyraLocalPlayer = Cast<ULyraLocalPlayer>(InLocalPlayer);

	// ... other code
	RegisterSetting(GamepadSettings);

	// @Game-Change start initializing the accessibility settings
	AccessibilitySettings = InitializeAccessibilitySettings(LyraLocalPlayer);
	RegisterSetting(AccessibilitySettings);
	// @Game-Change end initializing the accessibility settings
}

// ... other code
