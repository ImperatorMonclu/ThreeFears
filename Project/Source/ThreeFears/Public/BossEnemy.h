// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "BossEnemy.generated.h"

//Enemigo
UCLASS()
class THREEFEARS_API ABossEnemy : public AEnemy
{
	GENERATED_BODY()

	//Esfera situada en la mano para poder comprobar si acierta al jugador
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CollisionSphere;

public:
	//Constructor
	ABossEnemy();

	//Anima y mueve al actor según un valor del 0 al 1, siendo 1 hacia delante y 0 parado
	UFUNCTION(BlueprintCallable) //Para poder llamarlo en Blueprints
		void WalkForward(float Value);

	//Anima el ataque normal
	UFUNCTION(BlueprintCallable) //Para poder llamarlo en Blueprints
		void NormalAttacking();

	//Anima el ataque fuerte
	UFUNCTION(BlueprintCallable) //Para poder llamarlo en Blueprints
		void StrongAttacking();

	//**** Esto se realiza para poder colisionar solo cuando este realizando el ataque normal ****
	//Habilita la colisión de la mano
	UFUNCTION(BlueprintCallable) //Para poder llamarlo en Blueprints
		void EnableHits();

	//Deshabilita la colisión de la mano
	UFUNCTION(BlueprintCallable) //Para poder llamarlo en Blueprints
		void DisableHits();
	//********************************************************************************************

	//Comprueba si la mano colisión con alguna entidad
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Devuelve si está animando el ataque normal
	UFUNCTION(BlueprintPure) //Para poder usar su valor en Blueprints
		bool GetIsNormalAttacking();

	//Devuelve si está animando el ataque fuerte
	UFUNCTION(BlueprintPure) //Para poder usar su valor en Blueprints
		bool GetIsStrongAttacking();

protected:

	//Empieza el juego
	virtual void BeginPlay() override;

private:

	//Pausa la animación del ataque normal
	void StopNormalAttacking();

	//Pausa la animación del ataque fuerte
	void StopStrongAttacking();

	//Si está atacando normal
	bool IsNormalAttacking;

	//Si está atacando fuerte
	bool IsStrongAttacking;

	//Hits habilitados
	bool HitsEnable;
};
