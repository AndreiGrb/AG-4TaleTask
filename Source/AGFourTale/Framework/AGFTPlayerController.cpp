#include "AGFTPlayerController.h"

#include "AGFTCharacter.h"
#include "AGFourTale/DamageSystem/AGFTHealthSystem.h"
#include "AGFourTale/Interfaces/AGFTPawnInterface.h"

void AAGFTPlayerController::Server_DamageOtherActor_Implementation(AActor* OtherActor, int32 Damage)
{
	if (OtherActor->GetComponentByClass(UAGFTHealthComponent::StaticClass()))
	{
		if (const auto OtherCharacter = Cast<AAGFTCharacter>(OtherActor))
		{
			OtherCharacter->Client_ReceiveDamage(Damage);
		}
	}
}

void AAGFTPlayerController::EndPlayingState()
{
	Super::EndPlayingState();

	if (const auto PawnInterface = Cast<IAGFTPawnInterface>(GetPawn()))
	{
		PawnInterface->SetRemoteViewYaw(0.f);
	}
}
