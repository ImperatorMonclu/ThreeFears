// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "Equippable.h"
#include "MyCharacter.h"

void UInventoryComponent::AddItem(AItem* Item, int32 ItemCount)
{
	if (Item)
	{
		Item->SetActorEnableCollision(false);
		Item->GetStaticMeshComponent()->SetSimulatePhysics(false);
		Item->SetActorHiddenInGame(true);
		Internal_AddItemToArray(FItemStruct(Item, ItemCount));
	}
}

void UInventoryComponent::Internal_AddItemToArray(FItemStruct NewItem)
{
	Inventory.Add(NewItem);
}

void UInventoryComponent::DropItem(AItem* DroppedItem)
{
	int32 Index = -1;
	int32 ItemCount = 0;
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].Item == DroppedItem)
		{
			IEquippable* equippable = Cast<IEquippable>(Inventory[i].Item);
			if (equippable)
			{
				AMyCharacter* character = Cast<AMyCharacter>(GetOwner());
				if (character)
				{
					equippable->Unequip(character);
				}
			}
			else
			{
				Inventory[i].Item->GetStaticMeshComponent()->SetSimulatePhysics(true);
			}
			Inventory[i].Item->SetActorEnableCollision(true);
			Inventory[i].Item->SetActorHiddenInGame(false);
			Inventory[i].Item->SetActorLocation(GetOwner()->GetActorLocation() + FVector(200.0f, 0.0f, 0.0f));
			ItemCount = Inventory[i].ItemCount;
			Index = i;
		}
	}
	if (Index != -1)
	{
		Internal_RemoveItemFromArray(Index, ItemCount);
	}
}

void UInventoryComponent::RemoveItem(AItem* RemovedItem, int32 ItemCount)
{
	int32 Index = -1;
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i].Item == RemovedItem)
		{
			IEquippable* equippable = Cast<IEquippable>(Inventory[i].Item);
			if (equippable)
			{
				AMyCharacter* character = Cast<AMyCharacter>(GetOwner());
				if (character)
				{
					equippable->Unequip(character);
				}
			}
			Index = i;
		}
	}
	if (Index != -1)
	{
		if (Internal_RemoveItemFromArray(Index, ItemCount))
		{
			RemovedItem->Destroy();
		}
	}
}

bool UInventoryComponent::Internal_RemoveItemFromArray(int32 Index, int32 ItemCount)
{
	FItemStruct DroppedItem = Inventory[Index];
	int32 Remaining = DroppedItem.ItemCount - ItemCount;
	Inventory.RemoveAtSwap(Index, 1, true);
	if (Remaining > 0)
	{
		Internal_AddItemToArray(FItemStruct(DroppedItem.Item, Remaining));
		return false;
	}
	return true;
}

TArray<FItemStruct>& UInventoryComponent::GetInventory()
{
	return Inventory;
}