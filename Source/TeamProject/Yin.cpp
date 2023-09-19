// Fill out your copyright notice in the Description page of Project Settings.


#include "Yin.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimBlueprint.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Weapon.h"
#include "TPGameInstance.h"

AYin::AYin()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -88.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SocketOffset = FVector(0.0, 0.0, 30.0);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

void AYin::BeginPlay()
{
	Super::BeginPlay();

	IsAttacking = false;
	IsSaveAttack = false;
	AttackCount = 0;
	IsInputPossible = true;

	Weapon = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), FVector(0, 0, 0), FRotator::ZeroRotator);

	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weaponCollision"));

	Weapon->OwnChar = this;

	UTPGameInstance* GI = Cast<UTPGameInstance>(GetWorld()->GetGameInstance());

	if (!GI || !GI->MyCharacter)
		return;

	UE_LOG(LogTemp, Warning, TEXT("animinstance : %s"), *this->GetMesh()->GetAnimInstance()->GetName());

	GetMesh()->SetSkeletalMesh(GI->MyCharacter->SkeletalMesh);
	//GetMesh()->SetAnimClass(GI->MyCharacter->AnimBP->StaticClass());
	GetMesh()->SetAnimInstanceClass(GI->MyCharacter->AnimBP->GetClass());
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, GI->MyCharacter->AnimBP->GetClass()->GetName(), true);
	FirstAttackMontage = GI->MyCharacter->FirstAttackMontage;
	SecondAttackMontage = GI->MyCharacter->SecondAttackMontage;
	ThirdAttackMontage = GI->MyCharacter->ThirdAttackMontage;
	FourthAttackMontage = GI->MyCharacter->FourthAttackMontage;
	
}

void AYin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AYin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AYin::Look);

		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AYin::Move);

		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AYin::Jump);

		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AYin::StopJump);

		EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Started, this, &AYin::Attack);
	}
}



float AYin::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	return 0.0f;
}

void AYin::Look(const FInputActionValue& Value)
{
	if (!IsInputPossible)
		return;

	FVector2D v = Value.Get<FVector2D>();
	AddControllerYawInput(v.X);
	AddControllerPitchInput(v.Y);
}

void AYin::Move(const FInputActionValue& Value)
{
	if (!IsInputPossible)
		return;

	FVector2D MoveVector = Value.Get<FVector2D>();

	FRotator controlRot = GetControlRotation();
	FRotator controlYawRot = FRotator(0, controlRot.Yaw, 0);

	FVector PawnForwardVector = UKismetMathLibrary::GetForwardVector(controlYawRot);
	FVector PawnRightVector = UKismetMathLibrary::GetRightVector(controlYawRot);

	AddMovementInput(PawnForwardVector, MoveVector.Y);
	AddMovementInput(PawnRightVector, MoveVector.X);
}

void AYin::Jump(const FInputActionValue& Value)
{
	if (!IsInputPossible)
		return;

	ACharacter::Jump();
}

void AYin::StopJump(const FInputActionValue& Value)
{
	ACharacter::StopJumping();
}

void AYin::Attack(const FInputActionValue& Value)
{
	ReqAttack();
}

void AYin::ReqAttack_Implementation()
{
	if (!IsInputPossible)
		return;

	if (IsAttacking)
	{
		IsSaveAttack = true;
		return;
	}

	IsAttacking = true;

	AttackSwitch();
}

void AYin::AttackSwitch_Implementation()
{
	switch (AttackCount)
	{
	case 0:
		AttackCount = 1;
		PlayAnimMontage(FirstAttackMontage);
		break;
	case 1:
		AttackCount = 2;
		PlayAnimMontage(SecondAttackMontage);
		break;
	case 2:
		AttackCount = 3;
		PlayAnimMontage(ThirdAttackMontage);
		break;
	case 3:
		AttackCount = 0;
		PlayAnimMontage(FourthAttackMontage);
		break;
	}
}

void AYin::ComboAttackSave()
{
	if (!IsSaveAttack)
		return;

	IsSaveAttack = false;
	
	AttackSwitch();
}

void AYin::ResetCombo()
{
	AttackCount = 0;
	IsSaveAttack = false;
	IsAttacking = false;
}

void AYin::SetInputPossible()
{
	IsInputPossible = true;
}






