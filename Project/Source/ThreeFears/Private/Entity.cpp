// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity.h"

// Sets default values
AEntity::AEntity()
{
	Speed = 0.0f;
}

float AEntity::GetSpeed()
{
	return Speed;

}

void AEntity::SetSpeed(float nSpeed)
{
	Speed = nSpeed;

}
