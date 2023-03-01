// Copyright Epic Games, Inc. All Rights Reserved.

#include "MeshLoadTestGameMode.h"
#include "MeshLoadTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMeshLoadTestGameMode::AMeshLoadTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
