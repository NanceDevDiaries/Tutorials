#pragma once

#include "GameFramework/SaveGame.h"
#include "SubtitleDisplayOptions.h"

#include "UObject/ObjectPtr.h"
#include "LyraSettingsShared.generated.h"

class UObject;
struct FFrame;


// ... Some other code
UENUM(BlueprintType)
enum class ELyraAllowBackgroundAudioSetting : uint8
{
	Off,
	AllSounds,

	Num UMETA(Hidden),
};

// @Game-Change start difficulty enum
UENUM(BlueprintType)
enum class EDifficultySetting : uint8
{
	Easy,
	Normal,
	Hard
};
// @Game-Change end difficulty enum

UCLASS()
class ULyraSettingsShared : public ULocalPlayerSaveGame
{
	GENERATED_BODY()

	
public:
	// ... some other code
	
	// @Game-Change start Difficulty Options
	////////////////////////////////////////////////////////
	// Difficulty Options
	
	UFUNCTION()
	EDifficultySetting GetDifficulty() const;
	UFUNCTION()
	void SetDifficulty(EDifficultySetting InDifficulty);

private:
	UPROPERTY()
	EDifficultySetting Difficulty = EDifficultySetting::Normal;

public:
	// @Game-Change end Difficulty Options
	////////////////////////////////////////////////////////
	// Color Blind Options

	// ... some other code
};
