// Fill out your copyright notice in the Description page of Project Settings.


#include "Equippable.h"
#include "MyCharacter.h"

IEquippable::IEquippable()
{
	IsEquip = false;
}

void IEquippable::Equip(AMyCharacter* Character)
{
	IsEquip = true;
}

void IEquippable::Unequip(AMyCharacter* Character)
{
	IsEquip = false;
}

bool IEquippable::OnEquip()
{
	return IsEquip;
}