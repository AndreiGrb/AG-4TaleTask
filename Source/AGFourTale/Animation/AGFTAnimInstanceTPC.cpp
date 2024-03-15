#include "AGFTAnimInstanceTPC.h"

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
}
