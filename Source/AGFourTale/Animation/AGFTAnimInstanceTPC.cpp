#include "AGFTAnimInstanceTPC.h"

#include "GameFramework/Character.h"


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
}
