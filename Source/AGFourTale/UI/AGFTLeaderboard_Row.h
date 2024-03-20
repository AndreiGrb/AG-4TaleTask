#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGFTLeaderboard_Row.generated.h"


class UTextBlock;
class UBorder;

UCLASS()
class AGFOURTALE_API UAGFTLeaderboard_Row : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UTextBlock* GetText_PlayerName() const { return Text_PlayerName; }

	void SetKD(const int32 Kills, const int32 Deaths);

	bool bIsOwnPlayer;

private:
	virtual void NativeConstruct() override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FLinearColor Border_OwnPlayerColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	FLinearColor Border_OtherPlayersColor;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UBorder> Border_RowColor;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Text_PlayerName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Text_KD;
};
