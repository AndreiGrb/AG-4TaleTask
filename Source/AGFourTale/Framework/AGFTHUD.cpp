#include "AGFTHUD.h"

#include "AGFourTale/UI/AGFTLeaderboard.h"
#include "AGFourTale/UI/AGFTWidgetHUD.h"
#include "AGFourTale/Utils/AGFTLogCategories.h"


void AAGFTHUD::OpenLeaderboard()
{
	if (!LeaderboardClass)
	{
		UE_LOG(LogHUD, Error, TEXT("[AAGFTHUD::CreateLeaderboard] LeaderboardClass == nullptr"));
		return;
	}

	if (IsValid(LeaderboardWeakPtr.Get()))
	{
		LeaderboardWeakPtr.Get()->AddToViewport();
	}
	
	if (const auto Leaderboard = CreateWidget<UAGFTLeaderboard>(GetWorld(), LeaderboardClass))
	{
		LeaderboardWeakPtr = Leaderboard;
		Leaderboard->AddToViewport();
	}
	else
	{
		UE_LOG(LogHUD, Error, TEXT("[AAGFTHUD::CreateLeaderboard] Failed to create LeaderboardClass"));
	}
}

void AAGFTHUD::CloseLeaderboard()
{
	if (IsValid(LeaderboardWeakPtr.Get()))
	{
		LeaderboardWeakPtr.Get()->CloseLeaderboard();
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
