// Copyright Neoxyne. All Rights Reserved.

#include "GCDemoGameMode.h"
#include "GCDemoPlayerController.h"
#include "GCDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGCDemoGameMode::AGCDemoGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGCDemoPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}