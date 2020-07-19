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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
		class UInventoryComponent* InventoryComponent;

public:
	AMyCharacter();

	virtual void Tick(float DeltaSeconds) override;

	void AttachToMesh(class AItem* Item);

	void DetachFromMesh(class AItem* Item);

	UFUNCTION(BlueprintImplementableEvent)
		void SearchAndAttachToComponent(class AItem* Item);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
		float GetTurn();

	UFUNCTION(BlueprintPure)
		bool GetIsCrouching();

	UFUNCTION(BlueprintPure)
		bool GetIsHoldingMosquete();

	UFUNCTION(BlueprintPure)
		bool GetIsHoldingTorch();

	UFUNCTION(BlueprintPure)
		bool GetIsPickingObject();

	UFUNCTION(BlueprintPure)
		bool GetIsShootingMosquete();

	UFUNCTION(BlueprintPure)
		bool GetIsPunching();

	UFUNCTION(BlueprintPure)
		bool GetIsReloadingMosquete();

	UFUNCTION(BlueprintPure)
		FRotator GetRotationView();

	UFUNCTION(BlueprintPure)
		bool GetIsFocusedUsableActor();

	float GetMaxUseDistance();

	int32 GetBullets();

	bool GetHaveTorch();

	bool GetHaveMosquete();

	bool GetHaveKey();

	TArray<struct FItemStruct> GetInventory();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MaxUseDistance;

private:

	void TurnXAxis(float Value);

	void TurnYAxis(float Value);

	void WalkForward(float Value);

	void WalkRight(float Value);

	void Run();

	void StopRun();

	void Crouching();

	void StopCrouching();

	void HoldingMosquete();

	void StopHoldingMosquete();

	void Torch();

	void PickingObject();

	void StopPickingObject();

	void Shooting();

	void StopShootingMosquete();

	void StopPunching();

	void ReloadingMosquete();

	void StopReloadingMosquete();

	void Pause();

	class AActor* FocusedUsableActor;

	float Turn;

	float AccelerationRun;

	bool IsRunning;

	bool IsCrouching;

	bool IsPicking;
	
	bool IsReloadingMosquete;

	bool IsShootingMosquete;

	bool IsHoldingMosquete;

	bool IsHoldingTorch;

	bool IsPunching;

	FRotator RotationView;

	bool HasNewFocus;

	int32 Bullets;

	bool HaveTorch;

	bool HaveMosquete;

	bool HaveKey;

	class AMosquete* Mosquete;
};