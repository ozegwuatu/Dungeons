// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

ADungeonsPlayer::ADungeonsPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetMesh());

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(SpringArm);
}

void ADungeonsPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADungeonsPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

// Called to bind functionality to input
void ADungeonsPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Make sure that we are using a UEnhancedInputComponent; if not, the project is not configured correctly.
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IsValid(MoveForwardAction)) PlayerEnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ADungeonsPlayer::MoveForward);
		if (IsValid(MoveBackwardAction)) PlayerEnhancedInputComponent->BindAction(MoveBackwardAction, ETriggerEvent::Triggered, this, &ADungeonsPlayer::MoveBackward);
		if (IsValid(MoveLeftAction)) PlayerEnhancedInputComponent->BindAction(MoveLeftAction, ETriggerEvent::Triggered, this, &ADungeonsPlayer::MoveLeft);
		if (IsValid(MoveRightAction)) PlayerEnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ADungeonsPlayer::MoveRight);
		if (IsValid(GamepadMoveAction)) PlayerEnhancedInputComponent->BindAction(GamepadMoveAction, ETriggerEvent::Triggered, this, &ADungeonsPlayer::GamepadMove);

		if (IsValid(JumpAction)) PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ADungeonsPlayer::Jump);
		
		if (IsValid(MouseLookAction)) PlayerEnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ADungeonsPlayer::MouseLook);
		if (IsValid(GamepadLookAction)) PlayerEnhancedInputComponent->BindAction(GamepadLookAction, ETriggerEvent::Triggered, this, &ADungeonsPlayer::GamepadLook);

		if (IsValid(AttackAction)) PlayerEnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ADungeonsPlayer::Attack);
	}
}

void ADungeonsPlayer::PawnClientRestart()
{
	Super::PawnClientRestart();

	// Make sure that we have a valid PlayerController.
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values out-prioritize lower values.
			Subsystem->AddMappingContext(CharacterContext, 0);
		}
	}
}

void ADungeonsPlayer::MoveForward(const FInputActionValue& Value)
{
	FRotator YRotation(0.f, GetControlRotation().Yaw, 0.f);

	if (Value.GetMagnitude() != 0.f) AddMovementInput(UKismetMathLibrary::GetForwardVector(YRotation), Value[1]);
}

void ADungeonsPlayer::MoveBackward(const FInputActionValue& Value)
{
	FRotator YRotation(0.f, GetControlRotation().Yaw, 0.f);

	if (Value.GetMagnitude() != 0.f) AddMovementInput(UKismetMathLibrary::GetForwardVector(YRotation), Value[1]);
}

void ADungeonsPlayer::MoveLeft(const FInputActionValue& Value)
{
	FRotator XRotation(0.f, GetControlRotation().Yaw, GetControlRotation().Roll);

	if (Value.GetMagnitude() != 0.f) AddMovementInput(UKismetMathLibrary::GetRightVector(XRotation), Value[0]);
}

void ADungeonsPlayer::MoveRight(const FInputActionValue& Value)
{
	FRotator XRotation(0.f, GetControlRotation().Yaw, GetControlRotation().Roll);

	if (Value.GetMagnitude() != 0.f) AddMovementInput(UKismetMathLibrary::GetRightVector(XRotation), Value[0]);
}

void ADungeonsPlayer::GamepadMove(const FInputActionValue& Value)
{
	FRotator YRotation(0.f, GetControlRotation().Yaw, 0.f);
	FRotator XRotation(0.f, GetControlRotation().Yaw, GetControlRotation().Roll);

	if (Value.GetMagnitude() != 0.f)
	{
		AddMovementInput(UKismetMathLibrary::GetForwardVector(YRotation), Value[1]);
		AddMovementInput(UKismetMathLibrary::GetRightVector(XRotation), Value[0]);
	}
}

//I will eventually replace this with a Gameplay Ability.
void ADungeonsPlayer::Jump()
{
	StopAnimMontage();
	
	ACharacter::Jump();
}

void ADungeonsPlayer::MouseLook(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0)
	{
		AddControllerPitchInput(Value[1] * MouseLookSensitivity);
		AddControllerYawInput(Value[0] * MouseLookSensitivity);
	}
}

void ADungeonsPlayer::GamepadLook(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() != 0)
	{
		AddControllerPitchInput(Value[1] * GamepadLookSensitivity * GetWorld()->GetDeltaSeconds());
		AddControllerYawInput(Value[0] * GamepadLookSensitivity * GetWorld()->GetDeltaSeconds());
	}
}

//I will eventually replace this with a Gameplay Ability.
void ADungeonsPlayer::Attack()
{
	//The player performs a different attack, depending on how far along their combo is.
	switch(AttackCount)
	{
	case 0:
		if (IsValid(AttackOneMontage))
		{
			PlayAnimMontage(AttackOneMontage);

			AttackCount++;
		}
		break;
	case 1:
		if (IsValid(AttackTwoMontage))
		{
			PlayAnimMontage(AttackTwoMontage);

			AttackCount++;
		}
		break;
	case 2:
		if (IsValid(AttackThreeMontage))
		{
			PlayAnimMontage(AttackThreeMontage);

			AttackCount++;
		}
		break;
	case 3:
		if (IsValid(AttackFourMontage))
		{
			PlayAnimMontage(AttackFourMontage);

			AttackCount = 0;
		}
		break;
	default:
		break;
	}

	//Reset the combo, if the player does not attack again within a certain amount of time.
	GetWorldTimerManager().SetTimer(ComboHandle, this, &ADungeonsPlayer::ResetCombo, 1.f);
}

void ADungeonsPlayer::ResetCombo()
{
	AttackCount = 0;

	GetWorldTimerManager().ClearTimer(ComboHandle);
}