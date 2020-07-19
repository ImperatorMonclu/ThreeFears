// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "MyUserWidget.h"
#include "MyUserWidgetHUD.h"
#include "MyPlayerController.h"

AMyHUD::AMyHUD()
{
    WidgetHUDClass = NULL;
    WidgetHUD = nullptr;

    WidgetMenuClass = NULL;
    WidgetMenu = nullptr;
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetHUDClass) {
        AMyPlayerController* controller = Cast<AMyPlayerController>(GetOwningPlayerController());
        if (controller)
        {
            WidgetHUD = CreateWidget<UMyUserWidgetHUD>(controller, WidgetHUDClass);
            WidgetHUD->SetPlayerController(controller);
            WidgetHUD->AddToViewport();
        }
	}
}

void AMyHUD::MenuPause()
{
    if (WidgetMenuClass) {
        AMyPlayerController* controller = Cast<AMyPlayerController>(GetOwningPlayerController());
        if (controller)
        {
            WidgetMenu = CreateWidget<UMyUserWidget>(controller, WidgetMenuClass);
            WidgetMenu->SetPlayerController(controller);
            WidgetMenu->AddToViewport();
        }
    }
}

void AMyHUD::Restart()
{
    WidgetMenu->RemoveFromParent();
}
