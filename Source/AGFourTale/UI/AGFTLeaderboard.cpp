#include "AGFTLeaderboard.h"

#include "AGFTLeaderboard_Row.h"
#include "AGFourTale/Framework/AGFTGameState.h"
#include "AGFourTale/Framework/AGFTPlayerController.h"
#include "AGFourTale/Framework/AGFTPlayerState.h"
#include "AGFourTale/Utils/AGFTLogCategories.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"


void UAGFTLeaderboard::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const auto GameState = Cast<AAGFTGameState>(GetWorld()->GetGameState());

	UpdateLeaderboardHeaderAndObjective(GameState, InDeltaTime);
	UpdateLeaderboardRows(GameState);
}

void UAGFTLeaderboard::UpdateLeaderboardHeaderAndObjective(const AAGFTGameState* GameState, const float DeltaTime)
{
	const FString& Objective = FString::Printf(TEXT("%i Kills to Win"), GameState->KillsToWin);
	Text_Objective->SetText(FText::FromString(Objective));
	
	if (!GameState->bMatchStarted)
	{
		const FString& WaitingForOthers = TEXT("Waiting for one more player to begin");
		Text_Header->SetText(FText::FromString(WaitingForOthers));
	}
	else if (!GameState->bMatchIsOver)
	{
		const float MatchTimeRemainingFloat = Cast<AAGFTPlayerController>(GetOwningPlayer())->GetMatchTimeRemaining();
		const int32 MatchTimeRemaining = FMath::RoundToInt32(MatchTimeRemainingFloat);

		const int32 Minutes = FMath::FloorToInt32(MatchTimeRemaining / 60.f);
		const int32 Seconds = MatchTimeRemaining - (Minutes * 60);

		FString SecondsInString = FString::FromInt(Seconds);
		if (Seconds < 10)
		{
			SecondsInString = TEXT("0") + SecondsInString;
		}

		const FString& TimeRemaining = FString::Printf(TEXT("Time Remaining: %i:%s"), Minutes, *SecondsInString);
		Text_Header->SetText(FText::FromString(TimeRemaining));
	}
	else //Match is over
	{
		const FString& GameOver = FString::Printf(TEXT("Game over. Winner: %s"), *FString::Printf(TEXT("Player %i"), GameState->WinnerID));
		Text_Header->SetText(FText::FromString(GameOver));
	}
}

void UAGFTLeaderboard::UpdateLeaderboardRows(AAGFTGameState* GameState)
{
	if (!LeaderboardRowClass)
	{
		//todo: Should probably change Log category from HUD
		UE_LOG(LogHUD, Error, TEXT("[UAGFTLeaderboard::UpdateLeaderboardRows] LeaderboardRowClass == nullptr"));
		return;
	}
	
	if (PlayerRows.IsEmpty())
	{
		CreateRows(GameState);
	}
	
	bool LeaderboardChanges = false;

	if (GameState->PlayerArray.Num() != PlayerRows.Num())
	{
		LeaderboardChanges = true;
	}

	if (!LeaderboardChanges)
	{
		for (TObjectPtr<APlayerState> Player : GameState->PlayerArray)
		{
			auto PlayerState = Cast<AAGFTPlayerState>(Player);
			FVector2D* KD = PlayerRows.Find(PlayerState);
			if (PlayerState->NumberOfKills != KD->X || PlayerState->NumberOfDeaths != KD->Y)
			{
				LeaderboardChanges = true;
				break;
			}
		}
	}

	if (LeaderboardChanges)
	{
		ClearRows();
		CreateRows(GameState);
	}
}

void UAGFTLeaderboard::CreateRows(AAGFTGameState* GameState)
{
	TArray<AAGFTPlayerState*> AAGFTPlayerStateArray;
	for (TObjectPtr<APlayerState> Player : GameState->PlayerArray)
	{
		AAGFTPlayerStateArray.Add(Cast<AAGFTPlayerState>(Player));
	}
	
	AAGFTPlayerStateArray.Sort([](const AAGFTPlayerState& A, const AAGFTPlayerState& B)
	{
		return A.NumberOfKills > B.NumberOfKills;
	});

	for (AAGFTPlayerState* PlayerState : AAGFTPlayerStateArray)
	{
		const auto CreatedRow = CreateWidget<UAGFTLeaderboard_Row>(VB_Leaderboard, LeaderboardRowClass);

		CreatedRow->GetText_PlayerName()->SetText(FText::FromString(PlayerState->GetPlayerName()));
		CreatedRow->SetKD(PlayerState->NumberOfKills, PlayerState->NumberOfDeaths);
		if (GetOwningPlayer() == PlayerState->GetPlayerController())
		{
			CreatedRow->bIsOwnPlayer = true;
		}
		
		VB_Leaderboard->AddChildToVerticalBox(CreatedRow);

		PlayerRows.Add(PlayerState, FVector2D(PlayerState->NumberOfKills, PlayerState->NumberOfDeaths));
	}
}

void UAGFTLeaderboard::ClearRows()
{
	VB_Leaderboard->ClearChildren();
}
