// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Activatable.h"
#include "Door.generated.h"

//Actor interactuable que realiza la acción de puerta con o sin cerrojo
UCLASS()
class THREEFEARS_API ADoor : public AActor, public IActivatable
{
	GENERATED_BODY()

	//Componente para localizar las bisagras
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Location, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* HingeLocation;

	//Componente interactuable
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* Interactive;

	//Componente del modelo
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;

	//Componente interactuable de la cerradura
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interactive, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* InteractiveLock;

	//Componente del modelo de la cerradura
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* LockMesh;

public:	
	//Constructor
	ADoor();

	//Empieza a interactuar al actor
	virtual void StartFocusItem();

	//Termina de interactuar al actor
	virtual void EndFocusItem();

	//Usa la llave con el mismo código para desbloquear o bloquear que se pueda abrir
	bool UseKey(class AKeyObject* key);

	//Abre o cierra con una cierta velocidad
	void OpenOrClose(int32 velocity);

	//Devuelve si está abierta
	UFUNCTION(BlueprintPure) //Para poder usar su valor en Blueprints
		bool GetIsOpen();

	//Devuelve si está bloqueada
	bool GetIsLock();

	//Avisa al Blueprint de que sea intentado abrir la puerta
	UFUNCTION(BlueprintImplementableEvent) //Para implementar el evento en Blueprint
		void TryOpen();

	//Ángulo de apertura
	UPROPERTY(EditInstanceOnly) //Para variar su valor según la instancia en el nivel
		FRotator Angle;

	//Código para el desbloqueo o bloqueo
	UPROPERTY(EditInstanceOnly) //Para variar su valor según la instancia en el nivel
		int32 Code;

	//Si está cerrada
	UPROPERTY(EditInstanceOnly) //Para variar su valor según la instancia en el nivel
		bool IsLock;

	//Si está abierta
	UPROPERTY(EditInstanceOnly) //Para variar su valor según la instancia en el nivel
		bool IsOpen;

protected:

	//Empieza el juego
	virtual void BeginPlay() override;

private:

	//Anima la apertura
	void OpenAnim();

	//Anima el cierre
	void CloseAnim();

	//Ángulo cuando está abierta
	FRotator AngleOpened;

	//Ángulo cuando está cerrada
	FRotator AngleClosed;

	//Velocidad de rotación
	float Velocity;

	//Timer
	FTimerHandle Handle;

};
