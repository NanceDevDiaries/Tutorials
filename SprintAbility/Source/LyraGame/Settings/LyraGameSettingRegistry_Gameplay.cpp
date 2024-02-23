// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraGameSettingRegistry.h"

#include "GameSettingCollection.h"
#include "EditCondition/WhenPlayingAsPrimaryPlayer.h"
#include "EditCondition/WhenPlatformHasTrait.h"
#include "CustomSettings/LyraSettingValueDiscrete_Language.h"
#include "LyraSettingsLocal.h"
#include "GameSettingValueDiscreteDynamic.h"
#include "Player/LyraLocalPlayer.h"
#include "Replays/LyraReplaySubsystem.h"

#define LOCTEXT_NAMESPACE "Lyra"

UGameSettingCollection* ULyraGameSettingRegistry::InitializeGameplaySettings(ULyraLocalPlayer* InLocalPlayer)
{
	// .... Some other code

	// @Game-Change start Accessibility settings
	{
		UGameSettingCollection* AccessibilitySubsection = NewObject<UGameSettingCollection>();
		AccessibilitySubsection->SetDevName(TEXT("GameplayAccessibilityCollection"));
		AccessibilitySubsection->SetDisplayName(LOCTEXT("GameplayAccessibilityCollection_Name", "Accessibility"));
		Screen->AddSetting(AccessibilitySubsection);

		//----------------------------------------------------------------------------------
		{
			UGameSettingValueDiscreteDynamic_Bool* Setting = NewObject<UGameSettingValueDiscreteDynamic_Bool>();
			Setting->SetDevName(TEXT("SprintSection"));
			Setting->SetDisplayName(LOCTEXT("SprintSection_Name", "Tap To Sprint"));
			Setting->SetDescriptionRichText(LOCTEXT("SprintSection_Description", "If ON, tap to start sprinting, "
																		"tap again to stop sprinting. If Off, hold down sprint input to sprint, release to stop sprinting"));

			Setting->SetDynamicGetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(WantsToUseTapForSprint));
			Setting->SetDynamicSetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(SetWantsToUseTapForSprint));
			Setting->SetDefaultValue(GetDefault<ULyraSettingsLocal>()->WantsToUseTapForSprint());

			Setting->AddEditCondition(FWhenPlayingAsPrimaryPlayer::Get());

			AccessibilitySubsection->AddSetting(Setting);

		}
		//----------------------------------------------------------------------------------
		// @Game-Change end Accessibility settings
	}

	return Screen;
}

#undef LOCTEXT_NAMESPACE
