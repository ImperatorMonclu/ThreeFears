// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

//Constructor
AEnemy::AEnemy()
{
	//Inicializa variables
	Life = 200.0f;
	MaxLife = 200.0f;
	BehaviorTree = nullptr;
}

//Devuelve el árbol de comportamiento por defecto
UBehaviorTree* AEnemy::GetBehaviorTree()
{
	return BehaviorTree;
}
