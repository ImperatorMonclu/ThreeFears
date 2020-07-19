// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Components/SphereComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCanEverAffectNavigation(false);
	RootComponent = Mesh;

	Interactive = CreateDefaultSubobject<USphereComponent>(TEXT("Interactive"));
	Interactive->SetupAttachment(RootComponent);
	Interactive->BodyInstance.SetCollisionProfileName("OverlapOnlyPawn");

}

void AItem::StartFocusItem()
{
	Interactive->SetRenderCustomDepth(true);
}

void AItem::EndFocusItem()
{
	Interactive->SetRenderCustomDepth(false);
}

UStaticMeshComponent* AItem::GetStaticMeshComponent()
{
	return Mesh;
}
