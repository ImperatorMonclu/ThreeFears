// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "KeyObject.generated.h"

UCLASS()
class THREEFEARS_API AKeyObject : public AItem
{
	GENERATED_BODY()
	
public:
	AKeyObject();

	void Use();

	UPROPERTY(EditInstanceOnly)
	int32 Code;

	UPROPERTY(EditInstanceOnly)
	bool BreakWhenUse;

	int32 GetCode();
};
