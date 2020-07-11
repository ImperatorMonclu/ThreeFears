// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Entity.generated.h"

UCLASS()
class THREEFEARS_API AEntity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEntity();

	UFUNCTION(BlueprintPure)
		float GetSpeed();

protected:

	void SetSpeed(float Speed);

	float Speed;

};
