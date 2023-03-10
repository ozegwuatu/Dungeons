// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonsCharacterBase.h"
#include "InputActionValue.h"
#include "DungeonsPlayer.generated.h"

//Forward declarations.
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class DUNGEONS_API ADungeonsPlayer : public ADungeonsCharacterBase
{
	GENERATED_BODY()

public:
	//Constructor.
	ADungeonsPlayer(const FObjectInitializer& ObjectInitializer);

	//Executed every frame.
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Required for Enhanced Input plugin.
	virtual void PawnClientRestart() override;
	
protected:
	//Executed when spawned.
	virtual void BeginPlay() override;

	/* Actor and Scene Components */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DungeonsPlayer")
		TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DungeonsPlayer")
		TObjectPtr<UCameraComponent> PlayerCamera;

	/* Enhanced Input Actions and Mapping Contexts */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Enhanced Input|Input Actions|Movement")
		TObjectPtr<UInputAction> MoveForwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Enhanced Input|Input Actions|Movement")
		TObjectPtr<UInputAction> MoveBackwardAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Enhanced Input|Input Actions|Movement")
		TObjectPtr<UInputAction> MoveLeftAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Enhanced Input|Input Actions|Movement")
		TObjectPtr<UInputAction> MoveRightAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Enhanced Input|Input Actions|Movement")
		TObjectPtr<UInputAction> GamepadMoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Enhanced Input|Input Actions|Looking")
		TObjectPtr<UInputAction> MouseLookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Enhanced Input|Input Actions|Looking")
		TObjectPtr<UInputAction> GamepadLookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Enhanced Input|Input Actions|Attacks")
		TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Enhanced Input")
		TObjectPtr<UInputMappingContext> CharacterContext;

	/* Animation Montages */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Animation Montages|Attacks")
		TObjectPtr<UAnimMontage> AttackOneMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Animation Montages|Attacks")
		TObjectPtr<UAnimMontage> AttackTwoMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Animation Montages|Attacks")
		TObjectPtr<UAnimMontage> AttackThreeMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DungeonsPlayer|Animation Montages|Attacks")
		TObjectPtr<UAnimMontage> AttackFourMontage;

	/* Look sensitivity */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DungeonsPlayer|Look Sensitivity")
		float MouseLookSensitivity = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DungeonsPlayer|Look Sensitivity")
	float GamepadLookSensitivity = 50.f;

	//The number of attacks that have been performed, during the player's current combo.
	UPROPERTY(BlueprintReadWrite)
		int32 AttackCount;

	void MoveForward(const FInputActionValue& Value);
	void MoveBackward(const FInputActionValue& Value);
	void MoveLeft(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void GamepadMove(const FInputActionValue& Value);

	void MouseLook(const FInputActionValue& Value);
	void GamepadLook(const FInputActionValue& Value);
	
	void Attack();
	
};