// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Yin.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TEAMPROJECT_API AYin : public ACharacter
{
	GENERATED_BODY()

public:
	AYin();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void Turn(float Value);
	
	void LookUp(float Value);

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Jump();

	void StopJump();

	void Attack();


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UCapsuleComponent* WeaponCollision;

	bool IsAttacking;
	bool IsSaveAttack;
	int AttackCount;
};
