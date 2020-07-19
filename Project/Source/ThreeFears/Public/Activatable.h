// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Activatable.generated.h"

//Interfaz para los actores que puedan interactuar
UINTERFACE(MinimalAPI)
class UActivatable : public UInterface
{
	GENERATED_BODY()
};

class THREEFEARS_API IActivatable
{
	GENERATED_BODY()

public:

	//Empieza a interactuar al actor
	virtual void StartFocusItem() = 0;

	//Termina de interactuar al actor
	virtual void EndFocusItem() = 0;
};
