#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGFTLeaderboard.generated.h"


class UAGFTLeaderboard_Row;
class AAGFTPlayerState;
class UVerticalBox;
class AAGFTGameState;
class UTextBlock;

UCLASS()
class AGFOURTALE_API UAGFTLeaderboard : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void CloseLeaderboard();

	UFUNCTION(BlueprintImplementableEvent)
	void AbortClosing();

private:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateLeaderboardHeaderAndObjective(const AAGFTGameState* GameState, const float DeltaTime);
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Text_Header;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Text_Objective;

	
	void UpdateLeaderboardRows(AAGFTGameState* GameState);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UVerticalBox> VB_Leaderboard;

	TMap<TWeakObjectPtr<AAGFTPlayerState>, FVector2D> PlayerRows;
	
	void CreateRows(AAGFTGameState* GameState);

	void ClearRows();

	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<UAGFTLeaderboard_Row> LeaderboardRowClass;
};
