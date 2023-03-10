// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameplayActors/GSCModularCharacter.h"
#include "DungeonsCharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONS_API ADungeonsCharacterBase : public AGSCModularCharacter
{
	GENERATED_BODY()

public:
	//Constructor.
	ADungeonsCharacterBase(const FObjectInitializer& ObjectInitializer);

	//Executed every frame.
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	//Executed when spawned.
	virtual void BeginPlay() override;
	
};