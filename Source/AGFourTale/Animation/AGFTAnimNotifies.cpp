#include "AGFTAnimNotifies.h"

#include "AGFTAnimInterface.h"


void UAGFTNotify_SwitchedWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (const auto AnimInterface = Cast<IAGFTAnimInterface>(MeshComp->GetAnimInstance()))
	{
		AnimInterface->WeaponSwitched();
	}
}

void UAGFTNotify_ReloadedWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (const auto AnimInterface = Cast<IAGFTAnimInterface>(MeshComp->GetAnimInstance()))
	{
		AnimInterface->WeaponReloaded();
	}
}
