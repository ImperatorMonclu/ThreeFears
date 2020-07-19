// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BossEnemyAIController.generated.h"

//Controlador de la inteligencia artificial del BossEnemy
UCLASS()
class THREEFEARS_API ABossEnemyAIController : public AAIController
{
	GENERATED_BODY()

	//Componente para adjuntar un árbol de comportamiento
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Behavior, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* Behavior;

public:
	//Constructor
	ABossEnemyAIController();

	//Cuando adjunta a un Pawn
	virtual void OnPossess(class APawn* inPawn) override;

	//Percibe los actores que entran y salen de su campo de detección
	UFUNCTION(BlueprintCallable) //Para poder llamarlo en Blueprints
		void OnTargetPerceptionUpdated(class AActor* Actor, FAIStimulus Stimulus);

	//Devuelve la distancia para que un actor esté cerca
	UFUNCTION(BlueprintPure) //Para poder usar su valor en Blueprints
		float GetDistanceNear();

protected:

	//Distancia para que un actor esté cerca
	UPROPERTY(EditAnywhere) //Para poder editar su valor en Blueprints
		float DistanceNear;
};
