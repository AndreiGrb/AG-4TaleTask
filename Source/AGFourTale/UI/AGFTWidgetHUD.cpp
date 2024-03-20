#include "AGFTWidgetHUD.h"

#include "AGFourTale/DamageSystem/AGFTWeapon.h"
#include "AGFourTale/Design/AGFTGameSettings.h"
#include "AGFourTale/Interfaces/AGFTPawnInterface.h"
#include "AGFourTale/Utils/AGFTDebugLibrary.h"
#include "AGFourTale/Utils/AGFTLogCategories.h"
#include "AGFourTale/Utils/AGFTNames.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UAGFTWidgetHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (const auto PawnInterface = Cast<IAGFTPawnInterface>(GetOwningPlayerPawn()))
	{
		if (DynamicCrosshair)
		{
			MoveCrosshair(PawnInterface);
			TryPlayingDynamicCrosshairAnim(PawnInterface);

			UpdateCurrentWeapon(PawnInterface);

			UpdateHealth(PawnInterface);
		}
		else
		{
			UE_LOG(LogHUD, Error, TEXT("[UAGFTWidgetHUD::NativeTick] DynamicCrosshair == nullptr"));
		}
	}
	else
	{
		UE_LOG(LogHUD, Error, TEXT("[UAGFTWidgetHUD::NativeTick] OwningPlayer's Pawn is not inherited by PawnInterface"));
	}
}

void UAGFTWidgetHUD::MoveCrosshair(const IAGFTPawnInterface* PawnInterface)
{
	const auto PanelSlot = Cast<UCanvasPanelSlot>(DynamicCrosshair->Slot);
	if (!PanelSlot)
	{
		UE_LOG(LogHUD, Error, TEXT("[UAGFTWidgetHUD::MoveCrosshair] DynamicCrosshair is not a child of Canvas"));
		return;
	}

	const AAGFTWeapon* HoldingWeapon = PawnInterface->GetCurrentHoldingWeapon();
	if (!HoldingWeapon)
	{
		UE_LOG(LogHUD, Error, TEXT("[UAGFTWidgetHUD::MoveCrosshair] HoldingWeapon == nullptr"));
		return;
	}

	auto Settings = GetDefault<UAGFTGameSettings>();

	const FVector StartLocation = HoldingWeapon->GetRootComponent()->GetSocketLocation(SOCKETNAME_WEAPON_SHOOT);
	const FVector WeaponRightVector = HoldingWeapon->GetActorRightVector();
	const FVector TraceDistance = WeaponRightVector * Settings->CrosshairTraceDistance;
	FVector EndLocation = StartLocation + TraceDistance;

	FHitResult OutHit;
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Visibility);
	if (Settings->bShowCrosshairTrace)
	{
		FAGFTDebugTrace::DrawDebugLineTraceSingle(GetWorld(), StartLocation, EndLocation, bHit, OutHit);
	}

	FVector2D ScreenPosition;
	bool bSuccess = UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(),
																bHit ? OutHit.Location : EndLocation,
	                                                           ScreenPosition, false);

	if (!bSuccess)
	{
		return;
	}
	PanelSlot->SetPosition(ScreenPosition);
}

void UAGFTWidgetHUD::TryPlayingDynamicCrosshairAnim(const IAGFTPawnInterface* PawnInterface)
{
	if (PawnInterface->IsOrientationLockActive() && PawnInterface->CanShoot() && !DynamicCrosshair->IsVisible())
	{	//Orientation locked AND can shoot = show crosshair
		PlayShowDynamicCrosshairAnim(true);
	}
	else if ((!PawnInterface->IsOrientationLockActive() || !PawnInterface->CanShoot()) && DynamicCrosshair->IsVisible())
	{	//Orientation unlocked OR can't shoot = hide crosshair
		PlayShowDynamicCrosshairAnim(false);
	}
}

void UAGFTWidgetHUD::UpdateCurrentWeapon(const IAGFTPawnInterface* PawnInterface)
{
	AAGFTWeapon* Weapon = PawnInterface->GetCurrentHoldingWeapon();
	if (!IsValid(Weapon))
	{
		return;
	}
	
	if (CurrentWeaponWeakPtr != Weapon)
	{
		AAGFTWeapon* PreviousWeapon = CurrentWeaponWeakPtr.Get();
		if (IsValid(PreviousWeapon))
		{
			PreviousWeapon->OnWeaponFired.RemoveDynamic(this, &UAGFTWidgetHUD::PlayWeaponFiredAnim);
		}
		CurrentWeaponWeakPtr = Weapon;
		
		Weapon->OnWeaponFired.AddDynamic(this, &UAGFTWidgetHUD::PlayWeaponFiredAnim);
	}
	
	UpdateWeaponNameAndCount(PawnInterface, Weapon);
}

void UAGFTWidgetHUD::UpdateWeaponNameAndCount(const IAGFTPawnInterface* PawnInterface, const AAGFTWeapon* CurrentWeapon)
{
	if (!Text_WeaponName || !Text_AmmoCount)
	{
		UE_LOG(LogHUD, Error, TEXT("[UAGFTWidgetHUD::UpdateWeaponNameAndCount] Text is not bound to widgets!"));
		return;
	}

	AAGFTWeapon* Weapon = PawnInterface->GetCurrentHoldingWeapon();

	const FName& WeaponName = Weapon->GetWeaponConfigRowHandle().RowName;
	Text_WeaponName->SetText(FText::FromName(WeaponName));

	int32 MagAmmoCount, WeaponAmmoCount;
	Weapon->GetAmmoCount(MagAmmoCount, WeaponAmmoCount);

	const FString& AmmoCount = FString::Printf(TEXT("%i/%i"), MagAmmoCount, WeaponAmmoCount);
	Text_AmmoCount->SetText(FText::FromString(AmmoCount));
}

void UAGFTWidgetHUD::UpdateHealth(const IAGFTPawnInterface* PawnInterface)
{
	if (!PB_Health)
	{
		UE_LOG(LogHUD, Error, TEXT("[UAGFTWidgetHUD::UpdateHealth] PB_ProgressBar is not bound to widget!"));
		return;
	}

	const int32 Health = PawnInterface->GetCurrentHealth();
	PB_Health->SetPercent(Health / 100.f);
}
