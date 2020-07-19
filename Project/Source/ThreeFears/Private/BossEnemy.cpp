// Fill out your copyright notice in the Description page of Project Settings.

#include "BossEnemy.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//Constructor
ABossEnemy::ABossEnemy()
{
	//Inicializa la capsula
	GetCapsuleComponent()->InitCapsuleSize(70.f, 200.0f);

	//Inicializa la esfera de colisión de la mano y la une al modelo
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(GetMesh());

	//Cambia el perfil de colisión para poder superponerse
	CollisionSphere->BodyInstance.SetCollisionProfileName("OverlapAll");

	//Configura el movimiento
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxStepHeight = 140.0f;
	GetCharacterMovement()->MaxWalkSpeed = 800.0f;
	GetCharacterMovement()->MaxAcceleration = 800.0f;

	//Inicializa las variables
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;
	IsLife = true;
	Life = 200.0f;
	MaxLife = 200.0f;
	IsNormalAttacking = false;
	IsStrongAttacking = false;
	HitsEnable = false;
}

//Empieza el juego
void ABossEnemy::BeginPlay()
{
	Super::BeginPlay();

	//Une la superposición a la función
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABossEnemy::OnBeginOverlap);
}

//Anima y mueve al actor según un valor del 0 al 1, siendo 1 hacia delante y 0 parado
void ABossEnemy::WalkForward(float Value)
{
	//Comprueba si no está parado, si no está realizando el ataque fuerte y si está vivo
	if (Value != 0.0f && !IsStrongAttacking && IsLife)
	{
		//Comprueba si no está en movimiento real para dejar de animar, ejemplo no animar si estás intentando caminar contra la pared
		if (GetVelocity().Size() >= 100.0f)
		{
			//Comprueba si hay un valor hacia delante
			if (Value > 0.0f)
			{
				//Realiza una función regresiva para aumentar la animación poco a poco
				Speed = FMath::FInterpTo(Speed, 50.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
			}
		}
		else
		{
			//Realiza una función regresiva para disminuir la animación poco a poco
			Speed = FMath::FInterpTo(Speed, 0.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
		}

		//Realiza el movimiento
		AddMovementInput(GetActorForwardVector(), Value * 0.3);

	}
	else
	{
		//Realiza una función regresiva para disminuir la animación poco a poco
		Speed = FMath::FInterpTo(Speed, 0.0f, GetWorld()->GetDeltaSeconds(), 2.0f);
	}
}

//Anima el ataque normal
void ABossEnemy::NormalAttacking()
{
	//Comprueba si no está atacando fuerte y si está vivo
	if (!IsStrongAttacking && IsLife)
	{
		//Modifica la variable a true para que la máquina de estados pueda realizar la animación
		IsNormalAttacking = true;
		//Manda a volver a cambiar para poder percibir el cambio
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &ABossEnemy::StopNormalAttacking, 0.1f, false);
	}
}

//Anima el ataque fuerte
void ABossEnemy::StrongAttacking()
{
	//Comprueba si está atacando normal y si está vivo
	if (!IsNormalAttacking && IsLife)
	{
		//Modifica la variable a true para que la máquina de estados pueda realizar la animación
		IsStrongAttacking = true;
		//Manda a volver a cambiar para poder percibir el cambio
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &ABossEnemy::StopStrongAttacking, 0.1f, false);
	}
}

//**** Esto se realiza para poder colisionar solo cuando este realizando el ataque normal ****
//Habilita la colisión de la mano
void ABossEnemy::EnableHits()
{
	HitsEnable = true;
}

//Deshabilita la colisión de la mano
void ABossEnemy::DisableHits()
{
	HitsEnable = false;
}
//********************************************************************************************

//Comprueba si la mano colisión con alguna Entity
void ABossEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Comprueba si no es un actor, si no es el propio actor y si está habilitado la colisión de la mano
	if ((OtherActor != NULL) && (OtherActor != this) && HitsEnable)
	{
		//Comprueba si el actor que ha superpuesto es una Entity
		AEntity* entity = Cast<AEntity>(OtherActor);
		if (entity)
		{
			//Realiza el daño a la Entity
			entity->UpdateLife(-20.0f);
			//Deshabilita la superposición para solo realizar la acción una vez
			DisableHits();
		}
	}
}

//Devuelve si está animando el ataque normal
bool ABossEnemy::GetIsNormalAttacking()
{
	return IsNormalAttacking;
}

//Devuelve si está animando el ataque fuerte
bool ABossEnemy::GetIsStrongAttacking()
{
	return IsStrongAttacking;
}

//Pausa la animación del ataque normal
void ABossEnemy::StopNormalAttacking()
{
	//Modifica la variable a false para tener preparada la animación
	IsNormalAttacking = false;
	//Reanuda el timer
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}

//Pausa la animación del ataque fuerte
void ABossEnemy::StopStrongAttacking()
{
	//Modifica la variable a false para tener preparada la animación
	IsStrongAttacking = false;
	//Reanuda el timer
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}
