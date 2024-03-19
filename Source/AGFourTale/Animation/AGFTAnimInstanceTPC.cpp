#include "AGFTAnimInstanceTPC.h"

#include "KismetAnimationLibrary.h"
#include "AGFourTale/Interfaces/AGFTPawnInterface.h"
#include "AGFourTale/Utils/AGFTFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UAGFTAnimInstanceTPC::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	if (auto Character = Cast<ACharacter>(GetOwningActor()))
	{
		CharacterOwner = Character;
		MovementComponent = Character->GetCharacterMovement();
	}

	OnMontageEnded.AddDynamic(this, &UAGFTAnimInstanceTPC::MontageEnded);
}

void UAGFTAnimInstanceTPC::PlaySwitchWeaponAnimation()
{
	if (!SwitchWeaponMontage)
	{
		UE_LOG(LogAnimation, Error, TEXT("SwitchWeaponMontage == nullptr"));
	}
	
	if (Montage_IsPlaying(SwitchWeaponMontage) && !bIsWeaponSwitched)
	{
		Montage_Stop(0.1f, SwitchWeaponMontage);

		if (const auto PawnInterface = Cast<IAGFTPawnInterface>(CharacterOwner))
		{
			PawnInterface->WeaponSwitchAnimComplete();
		}
	}
	else
	{
		bIsWeaponSwitched = false;
		Montage_Play(SwitchWeaponMontage);
	}
}

void UAGFTAnimInstanceTPC::WeaponSwitched()
{
	bIsWeaponSwitched = true;
	if (const auto PawnInterface = Cast<IAGFTPawnInterface>(CharacterOwner))
	{
		PawnInterface->SwitchWeapons();
	}
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UAGFTAnimInstanceTPC::MontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == SwitchWeaponMontage && !bInterrupted)
	{
		if (const auto PawnInterface = Cast<IAGFTPawnInterface>(CharacterOwner))
		{
			PawnInterface->WeaponSwitchAnimComplete();
		}
	}
}

void FAGFTAnimInstanceTPC_Proxy::PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds)
{
	FAnimInstanceProxy::PreUpdate(InAnimInstance, DeltaSeconds);

	const auto AnimInstance = Cast<UAGFTAnimInstanceTPC>(InAnimInstance);
	if (IsValid(AnimInstance->CharacterOwner))
	{
		UpdateValuesFromAnimInstance(AnimInstance);
	}
	else
	{
		bShouldUpdate = false;
	}
	
	FAnimInstanceProxy::PreUpdate(InAnimInstance, DeltaSeconds);
}

void FAGFTAnimInstanceTPC_Proxy::UpdateValuesFromAnimInstance(const UAGFTAnimInstanceTPC* InAnimInstance)
{
	Velocity = InAnimInstance->MovementComponent->Velocity;
	CurrentAcceleration = InAnimInstance->MovementComponent->GetCurrentAcceleration();
	MoveThreshold = InAnimInstance->MoveThreshold;
	bIsFalling = InAnimInstance->MovementComponent->IsFalling();

	FallVelocityThreshold = InAnimInstance->FallVelocityThreshold;

	BaseActorRotation = InAnimInstance->CharacterOwner->GetActorRotation();

	PitchAim = FAGFTUtils::GetReplicatedPitchValue(InAnimInstance->CharacterOwner);
	BaseYawAim = FAGFTUtils::GetReplicatedYawValue(InAnimInstance->CharacterOwner);

	if (const auto PawnInterface = Cast<IAGFTPawnInterface>(InAnimInstance->CharacterOwner))
	{
		bIsAiming = PawnInterface->IsAiming();
	}
}

void FAGFTAnimInstanceTPC_Proxy::Update(float DeltaSeconds)
{
	CalculateValuesInProxy(DeltaSeconds);
	
	FAnimInstanceProxy::Update(DeltaSeconds);
}

void FAGFTAnimInstanceTPC_Proxy::CalculateValuesInProxy(const float DeltaSeconds)
{
	if (!bShouldUpdate)
	{
		return;
	}

	GroundSpeed = Velocity.Size2D();
	bShouldMove = GroundSpeed > MoveThreshold && !CurrentAcceleration.Equals(FVector::ZeroVector, 0.f);

	bCanEnterJumpFromFalling = bIsFalling && Velocity.Z > FallVelocityThreshold;
	
	MoveDirection = UKismetAnimationLibrary::CalculateDirection(Velocity, BaseActorRotation);

#pragma region YawAim calculation
	const FVector AimForwardVector = FRotator(0.f, BaseYawAim, 0.f).Vector();
	const FVector CharacterForwardVector = BaseActorRotation.Vector();
	const FVector CharacterRightVector = FRotationMatrix(BaseActorRotation).GetScaledAxis(EAxis::Y);

	const float AimCharacterDot = FVector::DotProduct(AimForwardVector, CharacterForwardVector);
	const float CharacterYawNoSign = FMath::GetMappedRangeValueClamped(FVector2d(1.f, 0.f),
																		FVector2d(0.f, 90.f),
																		AimCharacterDot);
	
	const bool bNegativeSign = FVector::DotProduct(AimForwardVector, CharacterRightVector) < 0.f;
	const float YawAim = CharacterYawNoSign * (bNegativeSign ? -1.f : 1.f);
#pragma endregion

	AimRotation = FRotator(PitchAim, YawAim, 0.f);
}
