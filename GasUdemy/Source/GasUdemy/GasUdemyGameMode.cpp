// Copyright Epic Games, Inc. All Rights Reserved.

#include "GasUdemyGameMode.h"
#include "GasUdemyHUD.h"
#include "GasUdemyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGasUdemyGameMode::AGasUdemyGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGasUdemyHUD::StaticClass();
}
