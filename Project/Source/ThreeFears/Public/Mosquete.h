// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Mosquete.generated.h"

UCLASS()
class THREEFEARS_API AMosquete : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* BulletLocation;

public:
	AMosquete();

	void Shoot(FRotator Velocity);

	void Reload();

	bool GetIsReloading();

	UFUNCTION(BlueprintImplementableEvent)
		void TryPick();

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditAnywhere)
		float Streng;

private:
	bool IsReloading;

	class ABullet* CurrentBullet;
};
