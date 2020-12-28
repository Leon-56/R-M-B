// Copyright Epic Games, Inc. All Rights Reserved.

#include "RMBGameMode.h"
#include "RMBCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARMBGameMode::ARMBGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/02_Blueprint/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
