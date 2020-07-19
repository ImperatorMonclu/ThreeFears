// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Equippable.h"
#include "Torch.generated.h"

UCLASS()
class THREEFEARS_API ATorch : public AItem, public IEquippable
{
	GENERATED_BODY()
	
public:
	ATorch();

	virtual void Equip(class AMyCharacter* Character) override;

	virtual void Unequip(class AMyCharacter* Character) override;

	UFUNCTION(BlueprintPure)
		virtual bool OnEquip() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
		class UPointLightComponent* Light;
};
