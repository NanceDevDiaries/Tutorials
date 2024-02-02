// Code from NanceDevDiaries. Feel free to modify or extend

#include "GameSettingCollection.h"
#include "GameSettingValueDiscreteDynamic.h"
#include "GameSettingValueScalarDynamic.h"
#include "LyraGameSettingRegistry.h"
#include "LyraSettingsShared.h"
#include "EditCondition/WhenPlayingAsPrimaryPlayer.h"
#include "Player/LyraLocalPlayer.h"

#define LOCTEXT_NAMESPACE "Lyra"

UGameSettingCollection* ULyraGameSettingRegistry::InitializeAccessibilitySettings(ULyraLocalPlayer* InLocalPlayer)
{
	UGameSettingCollection* Screen = NewObject<UGameSettingCollection>();
	Screen->SetDevName(TEXT("AccessibilityCollection"));
	Screen->SetDisplayName(LOCTEXT("AccessibilityCollection_Name", "Accessibility"));
	Screen->Initialize(InLocalPlayer);
	
	{
		UGameSettingCollection* ExperienceSubsection = NewObject<UGameSettingCollection>();
		ExperienceSubsection->SetDevName(TEXT("ExperienceAccessibilityCollection"));
		ExperienceSubsection->SetDisplayName(LOCTEXT("ExperienceAccessibilityCollection_Name", "Gameplay"));
		Screen->AddSetting(ExperienceSubsection);

		//----------------------------------------------------------------------------------
		{
			UGameSettingValueDiscreteDynamic_Bool* Setting = NewObject<UGameSettingValueDiscreteDynamic_Bool>();
			Setting->SetDevName(TEXT("ArachnophobiaMode"));
			Setting->SetDisplayName(LOCTEXT("ArachnophobiaModeSetting_Name", "Arachnophobia mode"));
			Setting->SetDescriptionRichText(LOCTEXT("ArachnophobiaModeSetting_Description", "Make the scary spiders look like cute capybaras."));

			Setting->SetDynamicGetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(ShouldUseArachnophobiaMode));
			Setting->SetDynamicSetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(SetShouldUseArachnophobiaMode));
			Setting->SetDefaultValue(GetDefault<ULyraSettingsLocal>()->ShouldUseArachnophobiaMode());

			Setting->AddEditCondition(FWhenPlayingAsPrimaryPlayer::Get());

			ExperienceSubsection->AddSetting(Setting);
		}
		//----------------------------------------------------------------------------------
		{
			UGameSettingValueDiscreteDynamic_Enum* Setting = NewObject<UGameSettingValueDiscreteDynamic_Enum>();
			Setting->SetDevName(TEXT("Difficulty"));
			Setting->SetDisplayName(LOCTEXT("Difficulty_Name", "Difficulty"));
			Setting->SetDescriptionRichText(LOCTEXT("DifficultySetting_Description", "Difficulty, how well you'll survive without any skills."));

			Setting->SetDynamicGetter(GET_SHARED_SETTINGS_FUNCTION_PATH(GetDifficulty));
			Setting->SetDynamicSetter(GET_SHARED_SETTINGS_FUNCTION_PATH(SetDifficulty));
			Setting->SetDefaultValue(GetDefault<ULyraSettingsShared>()->GetDifficulty());
			Setting->AddEnumOption(EDifficultySetting::Easy, LOCTEXT("EasyDifficulty", "Stroll in the park"));
			Setting->AddEnumOption(EDifficultySetting::Normal, LOCTEXT("MediumDifficulty", "Survivable"));
			Setting->AddEnumOption(EDifficultySetting::Hard, LOCTEXT("HardDifficulty", "Everything hurts"));

			Setting->AddEditCondition(FWhenPlayingAsPrimaryPlayer::Get());
			
			ExperienceSubsection->AddSetting(Setting);
		}
	}

	{
		UGameSettingCollection* UISubsection = NewObject<UGameSettingCollection>();
		UISubsection->SetDevName(TEXT("UIAccessibilityCollection"));
		UISubsection->SetDisplayName(LOCTEXT("UIAccessibilityCollection_Name", "UI"));
		Screen->AddSetting(UISubsection);

		//----------------------------------------------------------------------------------
		{
			UGameSettingValueScalarDynamic* Setting = NewObject<UGameSettingValueScalarDynamic>();
			Setting->SetDevName(TEXT("UIScale"));
			Setting->SetDisplayName(LOCTEXT("UIScale_Name", "UI Scale"));
			Setting->SetDescriptionRichText(LOCTEXT("UIScale_Description", "Adjusts the UI scale of everything."));

			Setting->SetDynamicGetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(GetUIScale));
			Setting->SetDynamicSetter(GET_LOCAL_SETTINGS_FUNCTION_PATH(SetUIScale));
			Setting->SetDefaultValue(GetDefault<ULyraSettingsLocal>()->GetUIScale());
			Setting->SetDisplayFormat([](double SourceValue, double NormalizedValue) {
				return FText::Format(LOCTEXT("UIScaleFormat", "{0}%"), static_cast<int32>(FMath::GetMappedRangeValueClamped(FVector2D(0, 1), FVector2D(10, 200), NormalizedValue)));
			});
			Setting->SetSourceRangeAndStep(TRange<double>(10, 200), 10);
			Setting->SetMinimumLimit(10);
			
			Setting->AddEditCondition(FWhenPlayingAsPrimaryPlayer::Get());

			UISubsection->AddSetting(Setting);
		}
	}
	
	return Screen;
}

#undef LOCTEXT_NAMESPACE
