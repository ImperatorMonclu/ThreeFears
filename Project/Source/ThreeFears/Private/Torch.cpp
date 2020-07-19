// Fill out your copyright notice in the Description page of Project Settings.


#include "Torch.h"
#include "Components/PointLightComponent.h"
#include "MyCharacter.h"

ATorch::ATorch() 
{
	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Mesh);
}

void ATorch::Equip(AMyCharacter* Character)
{
	if (!OnEquip())
	{
		IEquippable::Equip(Character);
		Character->AttachToMesh(this);
	}
}

void ATorch::Unequip(AMyCharacter* Character)
{
	if (OnEquip())
	{
		IEquippable::Unequip(Character);
		Character->DetachFromMesh(this);
	}
}

bool ATorch::OnEquip()
{
	return IEquippable::OnEquip();
}