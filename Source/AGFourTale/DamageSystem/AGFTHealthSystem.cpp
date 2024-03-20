#include "AGFTHealthSystem.h"

void UAGFTHealthComponent::Revive()
{
	bIsDead = false;

	Health = DefaultHealthValue;
}

void UAGFTHealthComponent::ReceiveDamage(const float Damage)
{
	Health -= Damage;

	if (Health < 1)
	{
		bIsDead = true;
		OnDeath.Broadcast();
	}
}

void UAGFTHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	DefaultHealthValue = Health;
}
