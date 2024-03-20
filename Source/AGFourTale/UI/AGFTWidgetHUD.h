#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AGFTWidgetHUD.generated.h"

class UProgressBar;
class AAGFTWeapon;
class IAGFTPawnInterface;
class UTextBlock;
class UCanvasPanel;


UCLASS()
class AGFOURTALE_API UAGFTWidgetHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayShowDynamicCrosshairAnim(const bool bPlayForwardAnimation);
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayWeaponFiredAnim();

private:
	virtual void NativeConstruct() override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void MoveCrosshair(const IAGFTPawnInterface* PawnInterface);
	
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> DynamicCrosshair;

	void TryPlayingDynamicCrosshairAnim(const IAGFTPawnInterface* PawnInterface);

	
	void UpdateCurrentWeapon(const IAGFTPawnInterface* PawnInterface);
	
	TWeakObjectPtr<AAGFTWeapon> CurrentWeaponWeakPtr;
	

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Text_WeaponName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Text_AmmoCount;

	void UpdateWeaponNameAndCount(const IAGFTPawnInterface* PawnInterface, const AAGFTWeapon* CurrentWeapon);


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UProgressBar> PB_Health;
	
	void UpdateHealth(const IAGFTPawnInterface* PawnInterface);


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget = "true", AllowPrivateAccess = "true"))
	TObjectPtr<UTextBlock> Text_RespawnTimer;

	UFUNCTION()
	void ShowRespawnTimer(AActor* DeadActor, APlayerState* DamageInstigator);

	void UpdateRespawnTimer(float DeltaTime);

	float TimeUntilRespawn;
};
