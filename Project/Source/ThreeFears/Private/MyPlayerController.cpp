// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "MyHUD.h"

//Constructor
AMyPlayerController::AMyPlayerController()
{
    //Se inicia el juego con el cursor oculto y desactivado en pantalla
	bShowMouseCursor = false;
	bEnableClickEvents = false;
	bEnableTouchEvents = false;
}

//Pausa o reanuda el juego
void AMyPlayerController::PauseGame()
{
    //Comprueba si est� pausado o no
    if (IsPaused())
    {
        //Comprueba si est� usando la HUD
        AMyHUD* hud = Cast<AMyHUD>(GetHUD());
        if (hud)
        {
            //Notifica a la HUD para reanudar el juego
            hud->Restart();
            //Oculta y desactiva el cursor
            bShowMouseCursor = false;
            bEnableClickEvents = false;
            bEnableTouchEvents = false;
        }
        //Acci�n de pausar
        SetPause(false);
    }
    else
    {
        //Comprueba si est� usando la HUD
        AMyHUD* hud = Cast<AMyHUD>(GetHUD());
        if (hud)
        {
            //Notifica a la HUD para reanudar el juego
            hud->MenuPause();
            //Muestra y activa el cursor
            bShowMouseCursor = true;
            bEnableClickEvents = true;
            bEnableTouchEvents = true;
        }
        //Acci�n de reanudar
        SetPause(true);
    }
}

//Funci�n para usarse en Blueprints y Widgets
void AMyPlayerController::RestartGame()
{
    //Reinicia el nivel en el que se encuentra
    RestartLevel();
}