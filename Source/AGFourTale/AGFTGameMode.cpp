// Copyright Epic Games, Inc. All Rights Reserved.

#include "AGFTGameMode.h"
#include "AGFTCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAGFTGameMode::AAGFTGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
