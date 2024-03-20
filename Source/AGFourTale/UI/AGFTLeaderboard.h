#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGFTLeaderboard.generated.h"


class AAGFTGameState;
class UTextBlock;

UCLASS()
class AGFOURTALE_API UAGFTLeaderboard : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void CloseLeaderboard();

private:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateLeaderboardHeader(AAGFTGameState* GameState, const float DeltaTime);

	void UpdateLeaderboardRows(AAGFTGameState* GameState);


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Text_Header;
};
