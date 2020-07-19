// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity.h"
#include "MyCharacter.h"

//Constructor
AEntity::AEntity()
{
	//Inicializa variables
	Speed = 0.0f;
	Life = 1.0f;
	MaxLife = 1.0f;
}

//Devuelve la velocidad de animación
float AEntity::GetSpeed()
{
	return Speed;
}

//Devuelve la vida
float AEntity::GetLife()
{
	return Life / MaxLife;
}

//Actualiza la vida según un valor
void AEntity::UpdateLife(float updateLife)
{
	Life += updateLife;

	//Comprueba si tiene vida después de actualizarla
	if (Life <= 0)
	{
		//Compureba si es el jugador
		AMyCharacter* character = Cast<AMyCharacter>(this);
		if (character)
		{
			//Comprueba si tiene controlador
			APlayerController* playerController = Cast<APlayerController>(GetController());
			if (playerController)
			{
				//Reinicia el nivel
				playerController->RestartLevel();
			}
		}
		//Se destruye
		Destroy();
	}
}

//Modifica la velocidad de animación
void AEntity::SetSpeed(float nSpeed)
{
	Speed = nSpeed;
}
