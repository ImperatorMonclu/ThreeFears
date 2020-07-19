// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

//Controla las acciones fuera del nivel de jugador
UCLASS()
class THREEFEARS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//Constructor
	AMyPlayerController();

	//Pausa o reanuda el juego
	UFUNCTION(BlueprintCallable) //Para poder llamarlo en Blueprints
	void PauseGame();

	//Función para usarse en Blueprints y Widgets
	UFUNCTION(BlueprintCallable) //Para poder llamarlo en Blueprints
	void RestartGame();
};
