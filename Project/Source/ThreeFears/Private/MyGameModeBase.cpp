// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "MyHUD.h"

AMyGameModeBase::AMyGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> playerPawnClassFinder(TEXT("/Game/Blueprints/Meshes/Pawn/MyCharacterBP"));
    if (playerPawnClassFinder.Succeeded())
	{
        DefaultPawnClass = playerPawnClassFinder.Class;
    }

	static ConstructorHelpers::FClassFinder<AHUD> HUDClassFinder(TEXT("/Game/Blueprints/HUD/MyHUDBP"));
	if (HUDClassFinder.Succeeded())
	{
		HUDClass = HUDClassFinder.Class;
	}
}
