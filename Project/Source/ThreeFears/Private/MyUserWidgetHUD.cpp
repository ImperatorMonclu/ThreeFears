// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidgetHUD.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "Mosquete.h"
#include "Torch.h"
#include "KeyObject.h"
#include "Ammo.h"
#include "InventoryComponent.h"

FLinearColor UMyUserWidgetHUD::GetActivatable()
{
	AMyCharacter* character = Cast<AMyCharacter>(GetPlayerController()->GetPawn());
	if (character)
	{
		if (character->GetIsFocusedUsableActor())
		{
			return FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}
	return FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

FText UMyUserWidgetHUD::GetBullets()
{
	AMyCharacter* character = Cast<AMyCharacter>(GetPlayerController()->GetPawn());
	if (character)
	{
		if (character->GetBullets())
		{
			return FText::FromString(FString::FromInt(character->GetBullets()));
		}
	}
	return FText::FromString("");
}

FLinearColor UMyUserWidgetHUD::GetMosquete()
{
	AMyCharacter* character = Cast<AMyCharacter>(GetPlayerController()->GetPawn());
	if (character)
	{
		if (character->GetIsHoldingMosquete())
		{
			return FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (character->GetHaveMosquete())
		{
			return FLinearColor(1.0f, 1.0f, 1.0f, 0.5f);
		}
	}
	return FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

FLinearColor UMyUserWidgetHUD::GetTorch()
{
	AMyCharacter* character = Cast<AMyCharacter>(GetPlayerController()->GetPawn());
	if (character)
	{
		if (character->GetIsHoldingTorch())
		{
			return FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else if (character->GetHaveTorch())
		{
			return FLinearColor(1.0f, 1.0f, 1.0f, 0.5f);
		}
	}
	return FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

FLinearColor UMyUserWidgetHUD::GetKey()
{
	AMyCharacter* character = Cast<AMyCharacter>(GetPlayerController()->GetPawn());
	if (character)
	{
		if (character->GetHaveKey())
		{
			return FLinearColor(1.0f, 1.0f, 1.0f, 0.5f);
		}
	}
	return FLinearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

float UMyUserWidgetHUD::GetLife()
{
	AMyCharacter* character = Cast<AMyCharacter>(GetPlayerController()->GetPawn());
	if (character)
	{
		return character->GetLife();
	}
	return 0.0f;
}
