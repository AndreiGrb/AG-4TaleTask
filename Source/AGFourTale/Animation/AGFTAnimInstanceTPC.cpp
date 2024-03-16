#include "AGFTAnimInstanceTPC.h"

#include "KismetAnimationLibrary.h"
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

	CharacterPitch = FAGFTUtils::GetReplicatedPitchValue(InAnimInstance->CharacterOwner);
	const float BaseAimYaw = FAGFTUtils::GetReplicatedYawValue(InAnimInstance->CharacterOwner);
	BaseAimRotation = FRotator(CharacterPitch, BaseAimYaw, 0.f);
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

#pragma region CharacterYaw calculation
	const FVector AimForwardVector = FRotator(0.f, BaseAimRotation.Yaw, 0.f).Vector();
	const FVector CharacterForwardVector = BaseActorRotation.Vector();
	const FVector CharacterRightVector = FRotationMatrix(BaseActorRotation).GetScaledAxis(EAxis::Y);

	const float AimCharacterDot = FVector::DotProduct(AimForwardVector, CharacterForwardVector);
	const float CharacterYawNoSign = FMath::GetMappedRangeValueClamped(FVector2d(1.f, 0.f),
																		FVector2d(0.f, 90.f),
																		AimCharacterDot);
	
	const bool bNegativeSign = FVector::DotProduct(AimForwardVector, CharacterRightVector) < 0.f;
	CharacterYaw = CharacterYawNoSign * (bNegativeSign ? -1.f : 1.f);
#pragma endregion
}
