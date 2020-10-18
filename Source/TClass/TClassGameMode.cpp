// Copyright Epic Games, Inc. All Rights Reserved.

#include "TClassGameMode.h"
#include "TClassCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATClassGameMode::ATClassGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
