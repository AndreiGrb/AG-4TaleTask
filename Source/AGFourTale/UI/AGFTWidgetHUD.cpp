#include "AGFTWidgetHUD.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

void UAGFTWidgetHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (!TopCanvas || !TestCrosshair)
	{
		UE_LOG(LogTemp, Error, TEXT("[UAGFTWidgetHUD::NativeConstruct] TopCanvas || TestCrosshair == nullptr"));
		return;
	}
	
}
