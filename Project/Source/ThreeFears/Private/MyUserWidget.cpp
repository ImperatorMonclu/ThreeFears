// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "MyPlayerController.h"

void UMyUserWidget::SetPlayerController(AMyPlayerController* nPlayerController)
{
	PlayerController = nPlayerController;
}

class AMyPlayerController* UMyUserWidget::GetPlayerController()
{
	return PlayerController;
}