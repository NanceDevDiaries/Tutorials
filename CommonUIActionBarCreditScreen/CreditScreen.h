// NanceDevDiaries please credit but use for your own devices.

#pragma once

#include "CoreMinimal.h"
#include "LyraActivatableWidget.h"
#include "CreditScreen.generated.h"

/**
 * 
 */
UCLASS(Abstract, meta = (Category = "UI", DisableNativeTick))
class LYRAGAME_API UCreditScreen : public ULyraActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	void HandleBackAction();
	UFUNCTION(BlueprintImplementableEvent)
	void HandleSlowDownAction();
	UFUNCTION(BlueprintImplementableEvent)
	void HandleSpeedUpAction();

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle BackInputActionData;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle SlowDownInputActionData;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle SpeedUpInputActionData;

	FUIActionBindingHandle BackHandle;
	FUIActionBindingHandle SlowDownHandle;
	FUIActionBindingHandle SpeedUpHandle;
};
