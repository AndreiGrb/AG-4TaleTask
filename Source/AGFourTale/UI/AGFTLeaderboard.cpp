#include "AGFTLeaderboard.h"

#include "AGFourTale/Framework/AGFTGameState.h"
#include "AGFourTale/Framework/AGFTPlayerController.h"
#include "Components/TextBlock.h"


void UAGFTLeaderboard::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	const auto GameState = Cast<AAGFTGameState>(GetWorld()->GetGameState());

	UpdateLeaderboardHeader(GameState, InDeltaTime);
	UpdateLeaderboardRows(GameState);
}

void UAGFTLeaderboard::UpdateLeaderboardHeader(AAGFTGameState* GameState, const float DeltaTime)
{
	if (!GameState->bMatchStarted)
	{
		const FString& WaitingForOthers = TEXT("Waiting for one more player to begin");
		Text_Header->SetText(FText::FromString(WaitingForOthers));
	}
	else if (GameState->bMatchStarted && !GameState->bMatchIsOver)
	{
		const float MatchTimeRemainingFloat = Cast<AAGFTPlayerController>(GetOwningPlayer())->GetMatchTimeRemaining();
		const int32 MatchTimeRemaining = FMath::RoundToInt32(MatchTimeRemainingFloat);

		const int32 Minutes = FMath::FloorToInt32(MatchTimeRemaining / 60.f);
		int32 Seconds = MatchTimeRemaining - (Minutes * 60);

		FString SecondsInString = FString::FromInt(Seconds);
		if (Seconds < 10)
		{
			SecondsInString = TEXT("0") + SecondsInString;
		}

		const FString& TimeRemaining = FString::Printf(TEXT("Time Remaining: %i:%s"), Minutes, *SecondsInString);
		Text_Header->SetText(FText::FromString(TimeRemaining));
	}
}

void UAGFTLeaderboard::UpdateLeaderboardRows(AAGFTGameState* GameState)
{
}
