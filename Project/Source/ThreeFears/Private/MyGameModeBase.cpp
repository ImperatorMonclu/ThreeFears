// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> playerPawnClassFinder(TEXT("/Game/Blueprints/Meshes/MyCharacterBP"));
	DefaultPawnClass = playerPawnClassFinder.Class;
}
