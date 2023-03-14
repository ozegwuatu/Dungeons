// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonsPlayerController.h"

void ADungeonsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CustomGameOnlyInputMode(false);
}

void ADungeonsPlayerController::CustomGameOnlyInputMode(bool bInConsumeCaptureMouseDown)
{
	FInputModeGameOnly InputMode;

	InputMode.SetConsumeCaptureMouseDown(bInConsumeCaptureMouseDown);

	SetInputMode(InputMode);
}