#include "AGFTHealthSystem.h"

void UAGFTHealthSystem::ReceiveDamage(const float Damage)
{
	Health -= Damage;

	if (Health < 1)
	{
		OnDeath.Broadcast();
	}
}
