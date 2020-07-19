// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Item.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(BlueprintReadWrite)
		AItem* Item;

	UPROPERTY(BlueprintReadWrite)
		int32 ItemCount;

	FItemStruct()
	{
		this->Item = NULL;
		this->ItemCount = 1;
	}

	FItemStruct(AItem* Item, int32 ItemCount)
	{
		this->Item = Item;
		this->ItemCount = ItemCount;
	}
};

UCLASS()
class THREEFEARS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void AddItem(AItem* Item, int32 ItemCount);

	void DropItem(AItem* DroppedItem);

	void RemoveItem(AItem* RemovedItem, int32 ItemCount);

	UFUNCTION(BlueprintPure)
		TArray<FItemStruct>& GetInventory();

private:

	TArray<FItemStruct> Inventory;

	void Internal_AddItemToArray(FItemStruct NewItem);

	bool Internal_RemoveItemFromArray(int32 Index, int32 ItemCount);
};
