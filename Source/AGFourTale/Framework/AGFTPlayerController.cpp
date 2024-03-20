#include "AGFTPlayerController.h"

#include "AGFTCharacter.h"
#include "AGFTGameMode.h"
#include "AGFourTale/DamageSystem/AGFTHealthSystem.h"
#include "AGFourTale/Interfaces/AGFTPawnInterface.h"
#include "GameFramework/PlayerState.h"

void AAGFTPlayerController::Server_DamageOtherActor_Implementation(AActor* OtherActor, int32 Damage)
{
	if (OtherActor->GetComponentByClass(UAGFTHealthComponent::StaticClass()))
	{
		if (const auto OtherCharacter = Cast<AAGFTCharacter>(OtherActor))
		{
			OtherCharacter->Client_ReceiveDamage(Damage, GetPlayerState<APlayerState>());
		}
	}
}

void AAGFTPlayerController::Server_RequestMatchTime_Implementation()
{
	const auto GameMode = Cast<AAGFTGameMode>(GetWorld()->GetAuthGameMode());
	Client_CurrentMatchTime(GameMode->GetMatchTime());
}

void AAGFTPlayerController::Client_CurrentMatchTime_Implementation(const float CurrentTime)
{
	MatchTimeRemaining = CurrentTime + GetPlayerState<APlayerState>()->ExactPing;
}

AAGFTPlayerController::AAGFTPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAGFTPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MatchTimeRemaining = FMath::Max(0.f, MatchTimeRemaining - DeltaSeconds);
}

void AAGFTPlayerController::EndPlayingState()
{
	Super::EndPlayingState();

	if (const auto PawnInterface = Cast<IAGFTPawnInterface>(GetPawn()))
	{
		PawnInterface->SetRemoteViewYaw(0.f);
	}
}
