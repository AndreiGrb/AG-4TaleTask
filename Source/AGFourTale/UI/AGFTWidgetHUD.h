#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AGFTWidgetHUD.generated.h"

class UTextBlock;
class UCanvasPanel;

DECLARE_LOG_CATEGORY_EXTERN(LogWidgetHUD, Log, All);

UCLASS()
class AGFOURTALE_API UAGFTWidgetHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void MoveCrosshair();
	
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> DynamicCrosshair;


	//Determines distance for trace, that is responsible for DynamicCrosshair position
	UPROPERTY(EditAnywhere, Category = "Settings")
	float CrosshairTraceDistance = 10000.f;
};
