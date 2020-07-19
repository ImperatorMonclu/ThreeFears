// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Equippable.h"
#include "Weapon.generated.h"

UCLASS()
class THREEFEARS_API AWeapon : public AItem, public IEquippable
{
	GENERATED_BODY()
public:
	virtual void Equip(class AMyCharacter* Character) override;

	virtual void Unequip(class AMyCharacter* Character) override;

	UFUNCTION(BlueprintPure)
		virtual bool OnEquip() override;
};
