// Fill out your copyright notice in the Description page of Project Settings.

#include "BossEnemyAIController.h"
#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyCharacter.h"

//Constructor
ABossEnemyAIController::ABossEnemyAIController()
{
	//Inicializar componentes y variables
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	Behavior = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior"));
	DistanceNear = 0.0f;
}

//Cuando adjunta a un Pawn
void ABossEnemyAIController::OnPossess(class APawn* inPawn)
{
	Super::OnPossess(inPawn);

	//Comprueba si el propietario es un Enemy
	if (AEnemy* possessedCharacter = Cast<AEnemy>(inPawn))
	{
		//Comprueba si el Enemy tiene el �rbol de conocimiento asociado
		if (UBehaviorTree* BehaviorTree = possessedCharacter->GetBehaviorTree())
		{
			//Inicializa la pizarra de variables del �rbol de conocimiento
			Blackboard->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
			//Empieza el �rbol de conocimiento
			Behavior->StartTree(*(BehaviorTree));
		}
		//Modifica el movimiento del Enemy para poder usarlo con el controlador
		UCharacterMovementComponent* Movement = possessedCharacter->GetCharacterMovement();
		Movement->bUseControllerDesiredRotation = true;
		possessedCharacter->bUseControllerRotationYaw = false;
	}
}

//Percibe los actores que entran y salen de su campo de detecci�n
void ABossEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//Comprueba si el actor percibido es MyCharacter (el propio jugador)
	if (Cast<AMyCharacter>(Actor))
	{
		//Comprueba si la acci�n ha sido de entrada o salida de su campo de detecci�n
		if (Stimulus.WasSuccessfullySensed()) //Entrada
		{
			//Modifica el actor objetivo de la pizarra
			Blackboard->SetValueAsObject("TargetActor", Actor);
		}
		else //Salida
		{
			//Modifica la localizaci�n objetivo de la pizarra a la �ltima localizaci�n percibida del actor objetivo
			Blackboard->SetValueAsVector("TargetLocation", Actor->GetActorLocation());
			//Modifica el actor objetivo a nulo
			Blackboard->SetValueAsObject("TargetActor", nullptr);
		}
	}
	/* Para poder realizar una inteligencia artificial que detectase varios actores y fuera a por el m�s cercano
	se necesitar�a una lista de actores que se fuera a�adiendo o eliminado seg�n compruebe est� funci�n y la
	funci�n Tick que vaya comprobando que actor de la lista es el m�s cercano */
}

//Distancia para que un actor est� cerca
float ABossEnemyAIController::GetDistanceNear()
{
	return DistanceNear;
}
