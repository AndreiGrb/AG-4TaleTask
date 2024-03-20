#include "AGFTLeaderboard_Row.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"

void UAGFTLeaderboard_Row::SetKD(const int32 Kills, const int32 Deaths)
{
	const FString& KD = FString::Printf(TEXT("K:%i   D:%i"), Kills, Deaths);
	Text_KD->SetText(FText::FromString(KD));
}

void UAGFTLeaderboard_Row::NativeConstruct()
{
	Super::NativeConstruct();

	Border_RowColor->SetBrushColor(bIsOwnPlayer ? Border_OwnPlayerColor : Border_OtherPlayersColor);
}
