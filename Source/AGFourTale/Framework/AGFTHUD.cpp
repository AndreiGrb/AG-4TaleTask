#include "AGFTHUD.h"

#include "AGFourTale/UI/AGFTLeaderboard.h"
#include "AGFourTale/UI/AGFTWidgetHUD.h"
#include "AGFourTale/Utils/AGFTLogCategories.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void AAGFTHUD::OpenLeaderboard()
{
	if (!LeaderboardClass)
	{
		UE_LOG(LogHUD, Error, TEXT("[AAGFTHUD::CreateLeaderboard] LeaderboardClass == nullptr"));
		return;
	}
	
	if (const auto Leaderboard = CreateWidget<UAGFTLeaderboard>(GetWorld(), LeaderboardClass))
	{
		Leaderboard->AddToViewport();
	}
	else
	{
		UE_LOG(LogHUD, Error, TEXT("[AAGFTHUD::CreateLeaderboard] Failed to create LeaderboardClass"));
	}
}

void AAGFTHUD::CloseLeaderboard()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, FoundWidgets, UAGFTLeaderboard::StaticClass());

	if (FoundWidgets.Num())
	{
		Cast<UAGFTLeaderboard>(FoundWidgets[0])->CloseLeaderboard();
	}
}

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
