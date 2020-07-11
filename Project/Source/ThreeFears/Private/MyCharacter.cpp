// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(60.f, 200.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());

	Camera->SetRelativeLocation(FVector(70.0f, 0.0f, 135.0f));
	Camera->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f));
	Camera->FieldOfView = 100.0f;

	Camera->bUsePawnControlRotation = true;

	Camera->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false), "HeadTop_EndSocketCamera");

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxStepHeight = 200.0f;
	GetCharacterMovement()->MaxWalkSpeed = 700.0f;
	GetCharacterMovement()->MaxAcceleration = 700.0f;

	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;
	Crouch = false;
	Turn = 0.0f;
	AccelerationRun = 0.5f;
	IsLife = true;
	IsRun = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AEntity::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AEntity::StopRun);

	PlayerInputComponent->BindAction("Punch", IE_Pressed, this, &AMyCharacter::MeleeOrShoot);*/

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
	if (Value != 0.0f && !IsPicking && IsLife)
	{
		if (Value > 0.0f)
		{
			if (IsRun)
			{
				if (Speed < 50.0f)
				{
					Speed += 1.0f;
				}
				if (AccelerationRun < 1.0f)
				{
					AccelerationRun += 0.25f;
				}
			}
			else
			{
				if (Speed < 25.0f)
				{
					Speed += 1.0f;
				}
				else if (Speed > 25.0f)
				{
					Speed -= 1.0f;
				}
				if (AccelerationRun > 0.5f)
				{
					AccelerationRun -= 0.01f;
				}
			}
		}
		else
		{
			if (Speed > -50.0f)
			{
				Speed -= 1.0f;
			}
			if (AccelerationRun > 0.5f)
			{
				AccelerationRun = 0.5f;
			}
		}

		AddMovementInput(GetActorForwardVector(), Value * AccelerationRun);

	}
	else
	{
		if (Speed > 0.0f)
		{
			Speed -= 1.0f;
		}
		else if (Speed < 0.0f)
		{
			Speed += 1.0f;
		}
		if (AccelerationRun > 0.5f)
		{
			AccelerationRun = 0.5f;
		}
	}

}
void AMyCharacter::WalkRight(float Value)
{
	if (Value != 0.0f && !IsPicking && IsLife)
	{
		if (Value < 0.0f)
		{
			if (Turn < 25.0f)
			{
				Turn += 0.5f;
			}
		}
		else
		{
			if (Turn > -25.0f)
			{
				Turn -= 0.5f;
			}
		}

		AddMovementInput(GetActorRightVector(), Value * 0.375f);

	}
	else
	{
		if (Turn > 0.0f)
		{
			Turn -= 1.0f;
		}
		else if (Turn < 0.0f)
		{
			Turn += 1.0f;
		}
	}

}

void AMyCharacter::Run()
{
	if (!IsPicking && IsLife)
	{
		IsRun = true;

	}

}

void AMyCharacter::StopRun()
{
	IsRun = false;

}

bool AMyCharacter::GetCrouch()
{
	return Crouch;

}
float AMyCharacter::GetTurn()
{
	return Turn;

}

void AMyCharacter::SetCrouch(bool nCrouch)
{
	Crouch = nCrouch;

}

void AMyCharacter::SetTurn(float nTurn)
{
	Turn = nTurn;

}
