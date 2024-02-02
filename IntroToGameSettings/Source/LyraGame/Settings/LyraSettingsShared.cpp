#include "LyraSettingsShared.h"

#include "Framework/Application/SlateApplication.h"
#include "Internationalization/Culture.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/App.h"
#include "Misc/ConfigCacheIni.h"
#include "Player/LyraLocalPlayer.h"
#include "Rendering/SlateRenderer.h"
#include "SubtitleDisplaySubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"

// ... more code

// @Game-Change start setting and getting difficulty
EDifficultySetting ULyraSettingsShared::GetDifficulty() const
{
	return Difficulty;
}

void ULyraSettingsShared::SetDifficulty(EDifficultySetting InDifficulty)
{
	if (Difficulty != InDifficulty)
	{
		Difficulty = InDifficulty;
		// put logic for whatever difficulty entails
	}
}
// @Game-Change end setting and getting difficulty

void ULyraSettingsShared::SetColorBlindStrength(int32 InColorBlindStrength)
{
	// ... more code
}

// ... more code
