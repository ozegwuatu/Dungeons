// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameplayActors/GSCModularPlayerController.h"
#include "DungeonsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONS_API ADungeonsPlayerController : public AGSCModularPlayerController
{
	GENERATED_BODY()

public:
	
protected:
	//Executed when spawned.
	virtual void BeginPlay() override;

	/* A custom version of UWidgetBlueprintLibrary::SetInputMode_GameOnly(), that doesn't change the viewport mouse capture mode.
	 @param	InConsumeCaptureMouseDown	Leave this "false" to avoid issues with mouse clicks.
	 */
	UFUNCTION(BlueprintCallable, Category = "DungeonsPlayerController")
		void CustomGameOnlyInputMode(bool bInConsumeCaptureMouseDown);
};