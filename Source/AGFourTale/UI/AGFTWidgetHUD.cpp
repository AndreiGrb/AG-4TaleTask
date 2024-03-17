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
#include "Components/TextBlock.h"


void UAGFTWidgetHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	MoveCrosshair();
}

void UAGFTWidgetHUD::MoveCrosshair()
{
	if (!DynamicCrosshair)
	{
		UE_LOG(LogHUD, Error, TEXT("[UAGFTWidgetHUD::MoveCrosshair] DynamicCrosshair == nullptr"));
		return;
	}

	const auto PanelSlot = Cast<UCanvasPanelSlot>(DynamicCrosshair->Slot);
	if (!PanelSlot)
	{
		UE_LOG(LogHUD, Error, TEXT("[UAGFTWidgetHUD::MoveCrosshair] DynamicCrosshair is not a child of Canvas"));
		return;
	}

	const auto PawnInterface = Cast<IAGFTPawnInterface>(GetOwningPlayerPawn());
	if (!PawnInterface)
	{
		UE_LOG(LogHUD, Error, TEXT("[UAGFTWidgetHUD::MoveCrosshair] OwningPlayer's Pawn is not inherited by PawnInterface"));
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

	if (bSuccess)
	{
		PanelSlot->SetPosition(ScreenPosition);
	}

	DynamicCrosshair->SetVisibility(bSuccess ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
}
