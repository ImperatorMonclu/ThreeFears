// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Components/BoxComponent.h"
#include "KeyObject.h"

//Constructor
ADoor::ADoor()
{
	//Inicializa la posici�n de las bisagras y las hace componente ra�z para poder abrir y cerrar con la rotaci�n del actor
	HingeLocation = CreateDefaultSubobject<USceneComponent>(TEXT("HingeLocation"));
	RootComponent = HingeLocation;

	//Inicializa el modelo y lo une a la bisagra
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	//Configuraci�n para que no sea posible caminar sobre el modelo
	Mesh->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	Mesh->CanCharacterStepUpOn = ECB_No;

	//Inicializa la caja interactiva y lo une al modelo
	Interactive = CreateDefaultSubobject<UBoxComponent>(TEXT("Interactive"));
	Interactive->SetupAttachment(Mesh);

	//Modifica su perfil de colisi�n a OverlapOnlyPawn para poder interactuar
	Interactive->BodyInstance.SetCollisionProfileName("OverlapOnlyPawn");

	//Inicializa el modelo de la cerradura y lo une al modelo
	LockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LockMesh"));
	LockMesh->SetupAttachment(Mesh);

	//Configuraci�n para que no sea posible caminar sobre el modelo
	LockMesh->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	LockMesh->CanCharacterStepUpOn = ECB_No;

	//Inicializa la caja interactiva de la cerradura y lo une al modelo de la cerradura
	InteractiveLock = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractiveLock"));
	InteractiveLock->SetupAttachment(LockMesh);

	//Modifica su perfil de colisi�n a OverlapOnlyPawn para poder interactuar
	InteractiveLock->BodyInstance.SetCollisionProfileName("OverlapOnlyPawn");

	//Inicializa variables
	IsLock = false;
	Code = 0;
	Angle = FRotator(0.0f, 0.0f, 0.0f);
	IsOpen = false;
	Velocity = 0.1f;
	AngleOpened = FRotator(0.0f, 0.0f, 0.0f);
	AngleClosed = FRotator(0.0f, 0.0f, 0.0f);
}

//Empieza a interactuar al actor
void ADoor::StartFocusItem()
{
	//Interactua con las zonas interactuables
	Interactive->SetRenderCustomDepth(true);
	InteractiveLock->SetRenderCustomDepth(true);
}

//Termina de interactuar al actor
void ADoor::EndFocusItem()
{
	//Interactua con las zonas interactuables
	Interactive->SetRenderCustomDepth(false);
	InteractiveLock->SetRenderCustomDepth(false);
}

//Usa la llave con el mismo c�digo para desbloquear o bloquear que se pueda abrir
bool ADoor::UseKey(AKeyObject* key)
{
	//Comprueba si es igual el c�digo de la llave y si est� abierta
	if (key->GetCode() == Code && !IsOpen)
	{
		//Usa la llave
		key->Use();
		//Comprueba si est� bloqueada o no
		if (IsLock)
		{
			//Bloquea si no lo est�
			IsLock = false;
		}
		else
		{
			//Desbloquea si est� bloqueada
			IsLock = true;
		}
		return true;
	}
	else
	{
		//Si est� cerrada y usa la llave correcta mandar� el evento a Blueprints
		TryOpen();
		return false;
	}
}

//Abre o cierra con una cierta velocidad
void ADoor::OpenOrClose(int32 velocity)
{
	//Comprueba si utiliza una velocidad para poder abrir o cerrar la puerta si no se utilizar� la de por defecto 0.1
	if (velocity > 0.0f)
	{
		Velocity = velocity;
	}

	//Comprueba si no est� abierta
	if (!IsOpen)
	{
		//Comprueba si no est� bloqueada
		if (!IsLock)
		{
			//Abre si esta cerrada y no bloqueada
			IsOpen = true;
			//Manda animar la apertura
			OpenAnim();
		}
	}
	else
	{
		//Cierra si est� abierta
		IsOpen = false;
		//Manda animar el cierre
		CloseAnim();
	}
}

//Devuelve si est� abierta
bool ADoor::GetIsOpen()
{
	return IsOpen;
}

//Devuelve si est� bloqueada
bool ADoor::GetIsLock()
{
	return IsLock;
}

//Empieza el juego
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	//Comprueba el valor por defecto de si est� abierta o no
	if (IsOpen)
	{
		//Calcula los �ngulos de cierre y apertura seg�n el �ngulo
		AngleOpened = GetActorRotation();
		AngleClosed = GetActorRotation() + Angle;
	}
	else
	{
		//Calcula los �ngulos de cierre y apertura seg�n el �ngulo
		AngleClosed = GetActorRotation();
		AngleOpened = GetActorRotation() + Angle;
	}
}

//Anima la apertura
void ADoor::OpenAnim()
{
	//Comprueba si est� en el �ngulo de apertura y si no se manda cerrar
	if (!AngleOpened.Equals(GetActorRotation(), Velocity * 64.0f) && IsOpen)
	{
		//Rota con una velocidad regresivamente hasta el �ngulo de apertura
		SetActorRotation(FRotator(FMath::RInterpTo(GetActorRotation(), AngleOpened, GetWorld()->GetDeltaSeconds(), Velocity)));
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &ADoor::OpenAnim, 0.01f, false);
	}
	else
	{
		//Reinicia el timer
		GetWorld()->GetTimerManager().ClearTimer(Handle);
	}
}

//Anima el cierre
void ADoor::CloseAnim()
{
	//Comprueba si est� en el �ngulo de cierre y si no se manda abrir
	if (!AngleClosed.Equals(GetActorRotation(), Velocity * 64.0f) && !IsOpen)
	{
		//Rota con una velocidad regresivamente hasta el �ngulo de cierre
		SetActorRotation(FRotator(FMath::RInterpTo(GetActorRotation(), AngleClosed, GetWorld()->GetDeltaSeconds(), Velocity)));
		GetWorld()->GetTimerManager().SetTimer(Handle, this, &ADoor::CloseAnim, 0.01f, false);
	}
	else
	{
		//Reinicia el timer
		GetWorld()->GetTimerManager().ClearTimer(Handle);
	}
}
