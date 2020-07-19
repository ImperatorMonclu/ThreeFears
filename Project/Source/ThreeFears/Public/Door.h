// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Activatable.h"
#include "Door.generated.h"

//Actor interactuable que realiza la acci�n de puerta con o sin cerrojo
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

	//Usa la llave con el mismo c�digo para desbloquear o bloquear que se pueda abrir
	bool UseKey(class AKeyObject* key);

	//Abre o cierra con una cierta velocidad
	void OpenOrClose(int32 velocity);

	//Devuelve si est� abierta
	UFUNCTION(BlueprintPure) //Para poder usar su valor en Blueprints
		bool GetIsOpen();

	//Devuelve si est� bloqueada
	bool GetIsLock();

	//Avisa al Blueprint de que sea intentado abrir la puerta
	UFUNCTION(BlueprintImplementableEvent) //Para implementar el evento en Blueprint
		void TryOpen();

	//�ngulo de apertura
	UPROPERTY(EditInstanceOnly) //Para variar su valor seg�n la instancia en el nivel
		FRotator Angle;

	//C�digo para el desbloqueo o bloqueo
	UPROPERTY(EditInstanceOnly) //Para variar su valor seg�n la instancia en el nivel
		int32 Code;

	//Si est� cerrada
	UPROPERTY(EditInstanceOnly) //Para variar su valor seg�n la instancia en el nivel
		bool IsLock;

	//Si est� abierta
	UPROPERTY(EditInstanceOnly) //Para variar su valor seg�n la instancia en el nivel
		bool IsOpen;

protected:

	//Empieza el juego
	virtual void BeginPlay() override;

private:

	//Anima la apertura
	void OpenAnim();

	//Anima el cierre
	void CloseAnim();

	//�ngulo cuando est� abierta
	FRotator AngleOpened;

	//�ngulo cuando est� cerrada
	FRotator AngleClosed;

	//Velocidad de rotaci�n
	float Velocity;

	//Timer
	FTimerHandle Handle;

};
