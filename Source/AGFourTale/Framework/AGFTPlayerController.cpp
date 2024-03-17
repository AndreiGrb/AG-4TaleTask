#include "AGFTPlayerController.h"

#include "AGFourTale/Interfaces/AGFTPawnInterface.h"

void AAGFTPlayerController::EndPlayingState()
{
	Super::EndPlayingState();

	if (const auto PawnInterface = Cast<IAGFTPawnInterface>(GetPawn()))
	{
		PawnInterface->SetRemoteViewYaw(0.f);
	}
}
