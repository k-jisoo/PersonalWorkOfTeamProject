// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Yin.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UAnimMontage;
class USphereComponent;
class UStaticMeshComponent;
class AWeapon;

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

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

public:
	void Look(const FInputActionValue& Value);

	void Move(const FInputActionValue& Value);

	void Jump(const FInputActionValue& Value);

	void StopJump(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	void AttackSwitch();

	void ComboAttackSave();

	void ResetCombo();

	void SetInputPossible();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* Camera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Move;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Look;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* IA_Jump;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UAnimMontage* FirstAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UAnimMontage* SecondAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UAnimMontage* ThirdAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UAnimMontage* FourthAttackMontage;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AWeapon* Weapon;

public:
	bool IsAttacking;
	bool IsSaveAttack;
	bool IsInputPossible;
	int AttackCount;
	float Damage;
};
