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
		//Comprueba si el Enemy tiene el árbol de conocimiento asociado
		if (UBehaviorTree* BehaviorTree = possessedCharacter->GetBehaviorTree())
		{
			//Inicializa la pizarra de variables del árbol de conocimiento
			Blackboard->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
			//Empieza el árbol de conocimiento
			Behavior->StartTree(*(BehaviorTree));
		}
		//Modifica el movimiento del Enemy para poder usarlo con el controlador
		UCharacterMovementComponent* Movement = possessedCharacter->GetCharacterMovement();
		Movement->bUseControllerDesiredRotation = true;
		possessedCharacter->bUseControllerRotationYaw = false;
	}
}

//Percibe los actores que entran y salen de su campo de detección
void ABossEnemyAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//Comprueba si el actor percibido es MyCharacter (el propio jugador)
	if (Cast<AMyCharacter>(Actor))
	{
		//Comprueba si la acción ha sido de entrada o salida de su campo de detección
		if (Stimulus.WasSuccessfullySensed()) //Entrada
		{
			//Modifica el actor objetivo de la pizarra
			Blackboard->SetValueAsObject("TargetActor", Actor);
		}
		else //Salida
		{
			//Modifica la localización objetivo de la pizarra a la última localización percibida del actor objetivo
			Blackboard->SetValueAsVector("TargetLocation", Actor->GetActorLocation());
			//Modifica el actor objetivo a nulo
			Blackboard->SetValueAsObject("TargetActor", nullptr);
		}
	}
	/* Para poder realizar una inteligencia artificial que detectase varios actores y fuera a por el más cercano
	se necesitaría una lista de actores que se fuera añadiendo o eliminado según compruebe está función y la
	función Tick que vaya comprobando que actor de la lista es el más cercano */
}

//Distancia para que un actor esté cerca
float ABossEnemyAIController::GetDistanceNear()
{
	return DistanceNear;
}
