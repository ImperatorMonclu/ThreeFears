// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Ammo.generated.h"

//Item para almacenar balas y poder recogerlas
UCLASS()
class THREEFEARS_API AAmmo : public AItem
{
	GENERATED_BODY()

public:

	//Devuelve las balas que contiene este item
	int32 GetBullets();

	//Balas del item
	UPROPERTY(EditInstanceOnly) //Para variar su valor según la instancia en el nivel
		int32 Bullets;
};
