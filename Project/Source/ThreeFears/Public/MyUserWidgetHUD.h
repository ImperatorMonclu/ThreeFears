// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyUserWidget.h"
#include "MyUserWidgetHUD.generated.h"

UCLASS()
class THREEFEARS_API UMyUserWidgetHUD : public UMyUserWidget
{
	GENERATED_BODY()

protected:	

	UFUNCTION(BlueprintPure)
		FLinearColor GetActivatable();

	UFUNCTION(BlueprintPure)
		FText GetBullets();

	UFUNCTION(BlueprintPure)
		FLinearColor GetMosquete();

	UFUNCTION(BlueprintPure)
		FLinearColor GetTorch();

	UFUNCTION(BlueprintPure)
		FLinearColor GetKey();

	UFUNCTION(BlueprintPure)
		float GetLife();

};
