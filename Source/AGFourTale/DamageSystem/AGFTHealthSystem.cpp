#include "AGFTHealthSystem.h"

#include "GameFramework/PlayerState.h"

void UAGFTHealthComponent::Revive()
{
	bIsDead = false;

	Health = DefaultHealthValue;
}

void UAGFTHealthComponent::ReceiveDamage(const float Damage, APlayerState* Instigator)
{
	Health -= Damage;

	if (Health < 1)
	{
		bIsDead = true;
		Killer = Instigator;
		
		OnDeath.Broadcast(Cast<AActor>(GetOuter()), Instigator);
	}
}

void UAGFTHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	DefaultHealthValue = Health;
}
