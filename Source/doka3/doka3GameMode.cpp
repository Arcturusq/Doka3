// Copyright Epic Games, Inc. All Rights Reserved.

#include "doka3GameMode.h"
#include "doka3PlayerController.h"
#include "doka3Character.h"
#include "UObject/ConstructorHelpers.h"

Adoka3GameMode::Adoka3GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = Adoka3PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}