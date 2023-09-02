// Fill out your copyright notice in the Description page of Project Settings.


#include "Yin.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

AYin::AYin()
{
 	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	WeaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollision"));
	//WeaponCollsiion->ParentSocket
}

void AYin::BeginPlay()
{
	Super::BeginPlay();
	IsAttacking = false;
	IsSaveAttack = false;
}

void AYin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AYin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AYin::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AYin::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AYin::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AYin::MoveRight);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AYin::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AYin::StopJump);
	PlayerInputComponent->BindAction(TEXT("Attack"), IE_Pressed, this, &AYin::Attack);

}

void AYin::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AYin::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AYin::MoveForward(float Value)
{
	FRotator controlRot = GetControlRotation();
	FVector worldDirection = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, 0.0f, controlRot.Yaw));
	AddMovementInput(worldDirection, Value);
}

void AYin::MoveRight(float Value)
{
	FRotator controlRot = GetControlRotation();
	FVector worldDirection = UKismetMathLibrary::GetRightVector(FRotator(0.0f, 0.0f, controlRot.Yaw));
	AddMovementInput(worldDirection, Value);
}

void AYin::Jump()
{
	Jump();
}

void AYin::StopJump()
{
	StopJumping();
}

void AYin::Attack()
{
	if (IsAttacking)
	{
		IsSaveAttack = true;
		return;
	}

	IsAttacking = true;

	switch (AttackCount) 
	{
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	}
}




