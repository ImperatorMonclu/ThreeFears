// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InventoryComponent.h"
#include "MyPlayerController.h"
#include "Activatable.h"
#include "KeyObject.h"
#include "Door.h"
#include "Torch.h"
#include "Mosquete.h"
#include "Item.h"
#include "Ammo.h"

AMyCharacter::AMyCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(70.f, 200.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh());
	Camera->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxStepHeight = 140.0f;
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->MaxAcceleration = 800.0f;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	MaxUseDistance = 800;
	HasNewFocus = false;

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;
	Turn = 0.0f;
	AccelerationRun = 0.0f;

	IsLife = true;
	IsRunning = false;
	IsCrouching = false;
	IsPunching = false;
	IsPicking = false;
	IsReloadingMosquete = false;
	IsShootingMosquete = false;
	IsHoldingMosquete = false;
	IsHoldingTorch = false;
	IsPunching = false;
	RotationView = FRotator(0.0f, 0.0f, 0.0f);
	FocusedUsableActor = NULL;
	Life = 100.0f;
	MaxLife = 100.0f;
	Bullets = 0;
	HaveTorch = false;
	HaveMosquete = false;
	HaveKey = false;
	Mosquete = NULL;
}

void AMyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetController())
	{
		FVector camLoc;
		FRotator camRot;

		GetController()->GetPlayerViewPoint(camLoc, camRot);
		const FVector startTrace = camLoc;
		const FVector endTrace = camLoc + (camRot.Vector() * MaxUseDistance);

		FCollisionObjectQueryParams collisionParams;
		collisionParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
		FHitResult Hit(ForceInit);

		GetWorld()->LineTraceSingleByObjectType(Hit, camLoc, endTrace, collisionParams);
		
		AActor* usable = Hit.GetActor();
		if (FocusedUsableActor != usable)
		{
			IActivatable* activatable = Cast<IActivatable>(FocusedUsableActor);
			if (activatable)
			{
				activatable->EndFocusItem();
				HasNewFocus = false;
			}
		}
		FocusedUsableActor = usable;

		if (usable)
		{
			if (HasNewFocus)
			{
				IActivatable* activatable = Cast<IActivatable>(usable);
				if (activatable)
				{
					activatable->StartFocusItem();
					HasNewFocus = true;
				}
			}
		}
	}
}

void AMyCharacter::AttachToMesh(AItem* Item)
{
	if (Item)
	{
		Item->SetActorHiddenInGame(false);
		Item->GetStaticMeshComponent()->SetSimulatePhysics(false);
		Item->SetActorEnableCollision(false);
		SearchAndAttachToComponent(Item);
	}
}

void AMyCharacter::DetachFromMesh(AItem* Item)
{
	Item->SetActorHiddenInGame(true);
	Item->GetStaticMeshComponent()->SetSimulatePhysics(true);
	Item->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepRelative, EDetachmentRule::KeepRelative, false));
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMyCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AMyCharacter::StopRun);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::Crouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::StopCrouching);

	PlayerInputComponent->BindAction("Torch", IE_Pressed, this, &AMyCharacter::Torch);
	PlayerInputComponent->BindAction("Picking", IE_Pressed, this, &AMyCharacter::PickingObject);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyCharacter::Shooting);
	//PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AMyCharacter::Aiming);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyCharacter::ReloadingMosquete);
	PlayerInputComponent->BindAction("Weapon1", IE_Pressed, this, &AMyCharacter::HoldingMosquete);
	PlayerInputComponent->BindAction("Weapon2", IE_Pressed, this, &AMyCharacter::StopHoldingMosquete);

	PlayerInputComponent->BindAction("Pause", IE_Pressed, Cast<AMyPlayerController>(GetController()), &AMyPlayerController::PauseGame).bExecuteWhenPaused = true;

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("WalkForward", this, &AMyCharacter::WalkForward);
	PlayerInputComponent->BindAxis("WalkRight", this, &AMyCharacter::WalkRight);

	PlayerInputComponent->BindAxis("TurnXAxis", this, &AMyCharacter::TurnXAxis);
	PlayerInputComponent->BindAxis("TurnYAxis", this, &AMyCharacter::TurnYAxis);

}

void AMyCharacter::TurnYAxis(float Rate)
{
	if (Rate != 0.0f)
	{
		RotationView = FRotator(GetControlRotation().Pitch, 0.0f, 0.0f);
		AddControllerPitchInput(-Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMyCharacter::TurnXAxis(float Rate)
{
	if (Rate != 0.0f)
	{
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}

}

void AMyCharacter::WalkForward(float Value)
{
	if (Value != 0.0f && !IsPicking && !IsReloadingMosquete && IsLife)
	{
		if (GetVelocity().Size() >= 64.0f)
		{
			if (Value > 0.0f)
			{
				if (IsRunning && !IsPunching && !IsShootingMosquete && !IsCrouching)
				{
					Speed = FMath::FInterpTo(Speed, 50.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
					AccelerationRun = FMath::FInterpTo(AccelerationRun, 1.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
				}
				else
				{
					Speed = FMath::FInterpTo(Speed, 25.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
					if (IsCrouching)
					{
						AccelerationRun = FMath::FInterpTo(AccelerationRun, 0.375f, GetWorld()->GetDeltaSeconds(), 2.0f);
					}
					else
					{
						AccelerationRun = FMath::FInterpTo(AccelerationRun, 0.5f, GetWorld()->GetDeltaSeconds(), 2.0f);
					}
				}
			}
			else
			{
				Speed = FMath::FInterpTo(Speed, -50.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
				if (IsCrouching)
				{
					AccelerationRun = FMath::FInterpTo(AccelerationRun, 0.375f, GetWorld()->GetDeltaSeconds(), 2.0f);
				}
				else
				{
					AccelerationRun = FMath::FInterpTo(AccelerationRun, 0.5f, GetWorld()->GetDeltaSeconds(), 2.0f);
				}
			}
		}
		else
		{
			Speed = FMath::FInterpTo(Speed, 0.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
			AccelerationRun = FMath::FInterpTo(AccelerationRun, 0.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
		}

		AddMovementInput(GetActorForwardVector(), Value * AccelerationRun);

	}
	else
	{
		Speed = FMath::FInterpTo(Speed, 0.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
		AccelerationRun = FMath::FInterpTo(AccelerationRun, 0.5f, GetWorld()->GetDeltaSeconds(), 2.0f);
	}

}
void AMyCharacter::WalkRight(float Value)
{
	if (Value != 0.0f && !IsPicking && !IsReloadingMosquete && IsLife)
	{
		if (GetVelocity().Size() >= 64.0f)
		{
			if (Value < 0.0f)
			{
				Turn = FMath::FInterpTo(Turn, 50.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
			}
			else
			{
				Turn = FMath::FInterpTo(Turn, -50.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
			}
		}
		else
		{
			Turn = FMath::FInterpTo(Turn, 0.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
		}

		AddMovementInput(GetActorRightVector(), Value * 0.375f);

	}
	else
	{
		Turn = FMath::FInterpTo(Turn, 0.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
	}

}

void AMyCharacter::Run()
{
	if (IsLife)
	{
		IsRunning = true;

	}

}

void AMyCharacter::StopRun()
{
	IsRunning = false;

}

void AMyCharacter::Crouching()
{
	if (!IsRunning && IsLife)
	{
		IsCrouching = true;

	}

}

void AMyCharacter::StopCrouching()
{
	IsCrouching = false;

}

void AMyCharacter::PickingObject()
{
	if (!IsPunching && !IsReloadingMosquete && !IsShootingMosquete && !IsPicking && IsLife)
	{
		AActor* usable = FocusedUsableActor;
		if (usable)
		{
			AItem* item = Cast<AItem>(usable);
			if (item)
			{
				AAmmo* ammo = Cast<AAmmo>(item);
				AMosquete* mosquete = Cast<AMosquete>(item);
				ATorch* torch = Cast<ATorch>(item);
				if (mosquete)
				{
					mosquete->TryPick();
					Mosquete = mosquete;
					HaveMosquete = true;
				}
				else if (torch)
				{
					HaveTorch = true;
				}
				else if (ammo)
				{
					Bullets += ammo->GetBullets();
				}
				else
				{
					HaveKey = true;
				}
				InventoryComponent->AddItem(item, 1);
					
				IsPicking = true;
				GetWorld()->GetTimerManager().SetTimer(Handle, this, &AMyCharacter::StopPickingObject, 0.1f, false);
			}
			else
			{
				ADoor* door = Cast<ADoor>(usable);
				if (door)
				{
					if (!door->GetIsLock())
					{
						door->OpenOrClose(0.7f);
					}
					else
					{
						for (FItemStruct& i : InventoryComponent->GetInventory())
						{
							AKeyObject* key = Cast<AKeyObject>(i.Item);
							if (key)
							{
								if (door->UseKey(key))
								{
									HaveKey = false;
									return;
								}
							}
						}
						door->TryOpen();
					}
				}
			}
		}
	}
}

void AMyCharacter::StopPickingObject()
{
	IsPicking = false;
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}

void AMyCharacter::Torch()
{
	if (IsLife)
	{
		for (FItemStruct& i : InventoryComponent->GetInventory())
		{
			ATorch* torch = Cast<ATorch>(i.Item);
			if (torch)
			{
				if (IsHoldingTorch)
				{
					torch->Unequip(this);
					IsHoldingTorch = false;
				}
				else
				{
					if (IsHoldingMosquete)
					{
						StopHoldingMosquete();
					}
					torch->Equip(this);
					IsHoldingTorch = true;
				}
				return;
			}
		}
	}
}

void AMyCharacter::HoldingMosquete()
{
	if (IsLife)
	{
		if (Mosquete != NULL)
		{
			if (IsHoldingTorch)
			{
				Torch();
			}
			Mosquete->Equip(this);
			IsHoldingMosquete = true;
			return;
		}
	}
}

void AMyCharacter::StopHoldingMosquete()
{
	if (IsLife)
	{
		if (Mosquete != NULL)
		{
			Mosquete->Unequip(this);
			IsHoldingMosquete = false;
			return;
		}
	}
}

void AMyCharacter::Shooting()
{
	if (!IsPicking && !IsReloadingMosquete && !IsShootingMosquete && IsHoldingMosquete && IsLife && Mosquete != NULL)
	{
		if (Mosquete->GetIsReloading())
		{
			IsShootingMosquete = true;
			GetWorld()->GetTimerManager().SetTimer(Handle, this, &AMyCharacter::StopShootingMosquete, 0.5f, false);
			return;
		}
	}
	else if (!IsPicking && !IsHoldingMosquete && IsLife)
	{
		//IsPunching = true;
		//GetWorld()->GetTimerManager().SetTimer(Handle, this, &AMyCharacter::StopPunching, 0.1f, false);
	}
}

void AMyCharacter::StopShootingMosquete()
{
	if (Mosquete != NULL)
	{
		Mosquete->Shoot(GetControlRotation());
		IsShootingMosquete = false;
		GetWorld()->GetTimerManager().ClearTimer(Handle);
		return;
	}
}

void AMyCharacter::StopPunching()
{
	IsPunching = false;
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}

void AMyCharacter::ReloadingMosquete()
{
	if (!IsPicking && !IsReloadingMosquete && !IsShootingMosquete && IsHoldingMosquete && IsLife)
	{
		if (Bullets > 0)
		{
			if (Mosquete != NULL)
			{
				if (!Mosquete->GetIsReloading())
				{
					Mosquete->Reload();
					Bullets -= 1;
					IsReloadingMosquete = true;
					GetWorld()->GetTimerManager().SetTimer(Handle, this, &AMyCharacter::StopReloadingMosquete, 2.0f, false);
					return;
				}
			}
		}
	}
}

void AMyCharacter::Pause()
{
	AMyPlayerController* playerController = Cast<AMyPlayerController>(GetController());
	if (playerController)
	{
		playerController->PauseGame();
	}
}

void AMyCharacter::StopReloadingMosquete()
{
	IsReloadingMosquete = false;
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}

float AMyCharacter::GetTurn()
{
	return Turn;

}

bool AMyCharacter::GetIsCrouching()
{
	return IsCrouching;

}

bool AMyCharacter::GetIsHoldingMosquete()
{
	return IsHoldingMosquete;

}

bool AMyCharacter::GetIsHoldingTorch()
{
	return IsHoldingTorch;

}

bool AMyCharacter::GetIsPickingObject()
{
	return IsPicking;

}

bool AMyCharacter::GetIsShootingMosquete()
{
	return IsShootingMosquete;

}

bool AMyCharacter::GetIsPunching()
{
	return IsPunching;

}

bool AMyCharacter::GetIsReloadingMosquete()
{
	return IsReloadingMosquete;

}

float AMyCharacter::GetMaxUseDistance()
{
	return MaxUseDistance;
}

FRotator AMyCharacter::GetRotationView()
{
	return RotationView;

}

bool AMyCharacter::GetIsFocusedUsableActor()
{
	IActivatable* activatable = Cast<IActivatable>(FocusedUsableActor);
	if (activatable)
	{
		return true;
	}
	else
	{
		return false;
	}
}

TArray<FItemStruct> AMyCharacter::GetInventory()
{
	return InventoryComponent->GetInventory();
}

int32 AMyCharacter::GetBullets()
{
	return Bullets;
}

bool AMyCharacter::GetHaveTorch()
{
	return HaveTorch;

}

bool AMyCharacter::GetHaveMosquete()
{
	return HaveMosquete;

}

bool AMyCharacter::GetHaveKey()
{
	return HaveKey;

}