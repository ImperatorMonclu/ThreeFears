// Fill out your copyright notice in the Description page of Project Settings.

#include "KeyObject.h"

AKeyObject::AKeyObject()
{
	BreakWhenUse = false;
	Code = 0;
}

void AKeyObject::Use()
{
	if (BreakWhenUse)
	{
		Destroy();
	}
}

int32 AKeyObject::GetCode()
{
	return Code;
}