// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableTouchEvents = false;
	/*bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	*/

}

void AMyPlayerController::MainMap()
{
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableTouchEvents = false;

}
