// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "MyCharacter.generated.h"

UCLASS()
class THREEFEARS_API AMyCharacter : public AEntity
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float BaseTurnRate;

	float BaseLookUpRate;

	void SetCrouch(bool Crouch);

	void SetTurn(float Turn);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TurnXAxis(float Value);

	void TurnYAxis(float Value);

	UFUNCTION(BlueprintPure)
		bool GetCrouch();

	UFUNCTION(BlueprintPure)
		float GetTurn();


private:

	void WalkForward(float Value);

	void WalkRight(float Value);

	void Run();

	void StopRun();

	float Turn;

	bool Crouch;

	float AccelerationRun;

	bool IsLife;

	bool IsPicking;
	
	bool IsRun;
};
