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
	UGameSettingCollection* Screen = NewObject<UGameSettingCollection>();
	Screen->SetDevName(TEXT("GameplayCollection"));
	Screen->SetDisplayName(LOCTEXT("GameplayCollection_Name", "Gameplay"));
	Screen->Initialize(InLocalPlayer);

	// ... More code
	
	// @Game-Change start Accessibility settings
	{
		UGameSettingCollection* AccessibilitySubsection = NewObject<UGameSettingCollection>();
		AccessibilitySubsection->SetDevName(TEXT("GameplayAccessibilityCollection"));
		AccessibilitySubsection->SetDisplayName(LOCTEXT("GameplayAccessibilityCollection_Name", "Accessibility"));
		Screen->AddSetting(AccessibilitySubsection);

		//----------------------------------------------------------------------------------
		{
			UGameSettingValueDiscreteDynamic_Bool* Setting = NewObject<UGameSettingValueDiscreteDynamic_Bool>();
			Setting->SetDevName(TEXT("GameplayArachnophobiaMode"));
			Setting->SetDisplayName(LOCTEXT("GameplayArachnophobiaModeSetting_Name", "Arachnophobia mode"));
			Setting->SetDescriptionRichText(LOCTEXT("GameplayArachnophobiaModeSetting_Description", "Make the scary spiders look like cute capybaras."));

			Setting->SetDynamicGetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(ShouldUseArachnophobiaMode));
			Setting->SetDynamicSetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(SetShouldUseArachnophobiaMode));
			Setting->SetDefaultValue(GetDefault<ULyraSettingsLocal>()->ShouldUseArachnophobiaMode());

			Setting->AddEditCondition(FWhenPlayingAsPrimaryPlayer::Get());

			AccessibilitySubsection->AddSetting(Setting);
		}
		//----------------------------------------------------------------------------------
	}
	// @Game-Change end Accessibility settings

	return Screen;
}

#undef LOCTEXT_NAMESPACE
