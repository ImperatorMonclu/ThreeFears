// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Entity.h"

//Constructor
ABullet::ABullet()
{
	//Inicializa la esfera de colisi�n
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));

	//Modifica su perfil de colisi�n a un perfil personalizado que bloquear� por defecto
	CollisionSphere->BodyInstance.SetCollisionProfileName("Projectile");

	//Configuraci�n para que no sea posible caminar sobre la esfera de colisi�n y no afecte a la navegaci�n de la IA
	CollisionSphere->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionSphere->CanCharacterStepUpOn = ECB_No;
	CollisionSphere->SetCanEverAffectNavigation(false);

	//La esfera es el componente ra�z
	RootComponent = CollisionSphere;

	//Inicializa el modelo y une a la esfera de colisi�n
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	//Modifica su perfil de colisi�n a NoCollision para no interferir con la esfera
	Mesh->BodyInstance.SetCollisionProfileName("NoCollision");

	//Configura el movimiento de proyectil para que est� parado al principio
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->UpdatedComponent = CollisionSphere;
	Movement->InitialSpeed = 1.0f;
	Movement->MaxSpeed = 1.0f;
	Movement->bRotationFollowsVelocity = true;
	Movement->bShouldBounce = false;

	//Modifica su tiempo de vida
	InitialLifeSpan = 4.0f;
}

//Realiza la acci�n de movimiento permitiendo variar la fuerza
void ABullet::Fire(float streng)
{
	//Aumenta la m�xima velocidad y la propia velocidad
	Movement->MaxSpeed = streng;
	Movement->Velocity *= streng;
	//Vuelve a modificar su tiempo de vida por si existe alg�n retraso
	SetLifeSpan(4.0f);
}

//Comprueba si colisiona con otro actor
void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Comprueba si no es un actor y si no es �l mismo
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		//Comprueba si el actor es una Entity
		AEntity* entity = Cast<AEntity>(OtherActor);
		if (entity)
		{
			//Realiza el da�o a la Entity
			entity->UpdateLife(-50.0f);
			//Se destruye cuando golpea
			Destroy();
		}
	}
}

//Empieza el juego
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	//Une la colisi�n a la funci�n
	CollisionSphere->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
}