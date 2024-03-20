#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AGFTHUD.generated.h"


class UAGFTLeaderboard;
class UAGFTWidgetHUD;

UCLASS()
class AGFOURTALE_API AAGFTHUD : public AHUD
{
	GENERATED_BODY()

public:
	void OpenLeaderboard();
	void CloseLeaderboard();

private:
	virtual void BeginPlay() override;
	
	void CreateWidgetHUD();
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<UAGFTWidgetHUD> WidgetHUDClass;

	UPROPERTY(EditAnywhere, Category = "Settings")
	TSubclassOf<UAGFTLeaderboard> LeaderboardClass;
};
