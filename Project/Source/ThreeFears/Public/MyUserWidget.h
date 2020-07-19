// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

UCLASS()
class THREEFEARS_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetPlayerController(class AMyPlayerController* nPlayerController);

protected:

	UFUNCTION(BlueprintPure)
		class AMyPlayerController* GetPlayerController();

private:

	class AMyPlayerController* PlayerController;

};
