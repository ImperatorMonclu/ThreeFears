// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Entity.generated.h"

//Personaje base de cada entidad
UCLASS()
class THREEFEARS_API AEntity : public ACharacter
{
	GENERATED_BODY()

public:
	//Constructor
	AEntity();

	//Devuelve la velocidad de animaci�n
	UFUNCTION(BlueprintPure) //Para poder usar su valor en Blueprints
		float GetSpeed();

	//Devuelve la vida
	UFUNCTION(BlueprintPure) //Para poder usar su valor en Blueprints
		float GetLife();

	//Actualiza la vida seg�n un valor
	virtual void UpdateLife(float updateLife);

protected:

	//Modifica la velocidad de animaci�n
	void SetSpeed(float Speed);

	//Velocidad de animaci�n
	float Speed;

	//Cantidad de vida
	float Life;

	//M�xima cantidad de vida
	float MaxLife;

	//Timer
	FTimerHandle Handle;

	//Si est� vivo
	bool IsLife;

	float BaseTurnRate;

	float BaseLookUpRate;
};
