// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Activatable.h"
#include "Item.generated.h"

UCLASS()
class THREEFEARS_API AItem : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:
	AItem();

	virtual void StartFocusItem();

	virtual void EndFocusItem();

	class UStaticMeshComponent* GetStaticMeshComponent();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* Interactive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

};
