// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class THREEFEARS_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMyHUD();

	void MenuPause();

	void Restart();

	class UMyUserWidgetHUD* GetWidgetHUD();

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMyUserWidgetHUD> WidgetHUDClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMyUserWidget> WidgetMenuClass;

	virtual void BeginPlay() override;

private:

	class UMyUserWidgetHUD* WidgetHUD;

	class UMyUserWidget* WidgetMenu;
};
