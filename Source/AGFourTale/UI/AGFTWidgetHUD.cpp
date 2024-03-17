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
	
	if(UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(TestCrosshair->Slot))
	{
		PanelSlot->SetPosition(FVector2D(0, 0));  // Sets the position to coordinates (100, 100)
	}
}
