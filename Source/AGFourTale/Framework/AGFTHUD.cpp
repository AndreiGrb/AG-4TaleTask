#include "AGFTHUD.h"

#include "AGFourTale/UI/AGFTWidgetHUD.h"
#include "AGFourTale/Utils/AGFTLogCategories.h"


void AAGFTHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateWidgetHUD();
}

void AAGFTHUD::CreateWidgetHUD()
{
	if (!WidgetHUDClass)
	{
		UE_LOG(LogHUD, Error, TEXT("[AAGFTHUD::CreateWidgetHUD] WidgetHUDClass == nullptr"));
		return;
	}
	
	if (const auto WidgetHUD = CreateWidget<UAGFTWidgetHUD>(GetWorld(), WidgetHUDClass))
	{
		WidgetHUD->AddToViewport();
	}
	else
	{
		UE_LOG(LogHUD, Error, TEXT("[AAGFTHUD::CreateWidgetHUD] Failed to create WidgetHUD"));
	}
}
