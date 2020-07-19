// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

//Actor que realiza la acción de bala
UCLASS()
class THREEFEARS_API ABullet : public AActor
{
	GENERATED_BODY()

	//Componente de colisión
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		class USphereComponent* CollisionSphere;

	//Componente del modelo
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

	//Componente del movimiento de projectil
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* Movement;
	
public:
	//Constructor
	ABullet();

	//Realiza la acción de movimiento permitiendo variar la fuerza
	void Fire(float streng);

	//Comprueba si colisiona con otro actor
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	//Empieza el juego
	virtual void BeginPlay();
};
