#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AGFTHUD.generated.h"


class UAGFTWidgetHUD;

DECLARE_LOG_CATEGORY_EXTERN(LogHUD, Log, All);

UCLASS()
class AGFOURTALE_API AAGFTHUD : public AHUD
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	void CreateWidgetHUD();


	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<UAGFTWidgetHUD> WidgetHUDClass;
};
