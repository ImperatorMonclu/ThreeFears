// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "Enemy.generated.h"

//Entity que actuará de enemigo frente al jugador
UCLASS()
class THREEFEARS_API AEnemy : public AEntity
{
	GENERATED_BODY()

public:
	//Constructor
	AEnemy();

	//Devuelve el árbol de comportamiento por defecto
	class UBehaviorTree* GetBehaviorTree();

protected:

	//Árbol por defecto
	UPROPERTY(EditAnywhere) //Para poder editar su valor en Blueprints
		class UBehaviorTree* BehaviorTree;
};
