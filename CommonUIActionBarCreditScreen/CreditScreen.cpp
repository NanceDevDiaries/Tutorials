// NanceDevDiaries please credit but use for your own devices.


#include "CreditScreen.h"

#include "Input/CommonUIInputTypes.h"

void UCreditScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BackHandle = RegisterUIActionBinding(FBindUIActionArgs(BackInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleBackAction)));
	SlowDownHandle = RegisterUIActionBinding(FBindUIActionArgs(SlowDownInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleSlowDownAction)));
	SpeedUpHandle = RegisterUIActionBinding(FBindUIActionArgs(SpeedUpInputActionData, true, FSimpleDelegate::CreateUObject(this, &ThisClass::HandleSpeedUpAction)));
}

void UCreditScreen::HandleBackAction()
{
	DeactivateWidget();
}
