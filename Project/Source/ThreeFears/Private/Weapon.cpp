// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "MyCharacter.h"

void AWeapon::Equip(AMyCharacter* Character)
{
	if (!OnEquip())
	{
		IEquippable::Equip(Character);
		Character->AttachToMesh(this);
	}
}

void AWeapon::Unequip(AMyCharacter* Character)
{
	if (OnEquip())
	{
		IEquippable::Unequip(Character);
		Character->DetachFromMesh(this);
	}
}

bool AWeapon::OnEquip()
{
	return IEquippable::OnEquip();
}