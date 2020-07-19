// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Equippable.generated.h"

UINTERFACE(MinimalAPI)
class UEquippable : public UInterface
{
	GENERATED_BODY()
};

class THREEFEARS_API IEquippable
{
	GENERATED_BODY()

public:
	IEquippable();

	virtual void Equip(class AMyCharacter* Character);

	virtual void Unequip(class AMyCharacter* Character);

	UFUNCTION()
	virtual bool OnEquip();

private:
	bool IsEquip;
};
