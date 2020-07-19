// Fill out your copyright notice in the Description page of Project Settings.


#include "Mosquete.h"
#include "Bullet.h"

AMosquete::AMosquete()
{
	BulletLocation = CreateDefaultSubobject<USceneComponent>(TEXT("BulletLocation"));
	BulletLocation->SetupAttachment(Mesh);

	IsReloading = false;
	CurrentBullet = nullptr;
}

void AMosquete::Shoot(FRotator velocity)
{
	if (IsReloading && BulletClass != NULL)
	{
		UWorld* const World = GetWorld();

		if (World != NULL)
		{
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			CurrentBullet = World->SpawnActor<ABullet>(BulletClass, BulletLocation->GetComponentLocation(), velocity, ActorSpawnParams);
			if (CurrentBullet != nullptr)
			{
				CurrentBullet->SetOwner(GetOwner());
				CurrentBullet->Fire(Streng);
				IsReloading = false;
			}
		}
	}
}

void AMosquete::Reload()
{
	if (BulletClass != NULL)
	{
		IsReloading = true;
	}

}

bool AMosquete::GetIsReloading()
{
	return IsReloading;
}