// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Yin.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetSphereRadius(90.0f);
	Sphere->SetCollisionProfileName(TEXT("Custom"));
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//AttachToComponent(targetChar->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("weaponCollision"));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AWeapon::OnSphereComponentBeginOverlap);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::SetSphereCollisionState(bool state)
{
	if (state)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeapon::SetOwnChar(AYin* Char)
{
	OwnChar = Char;
}

void AWeapon::OnSphereComponentBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//Interface�� �����ϸ� �� ����
	//������ Yin������ EnemyŬ������ �ٲ����.

	AEnemy* HitChar = Cast<AEnemy>(OtherActor);
	
	////ApplyDamage�� �������� �ѱ��
	////���� TakeDamage�� override�ߴٸ� �������� �޴´�.
	UGameplayStatics::ApplyDamage(HitChar, OwnChar->Damage, OwnChar->GetController(), this, UDamageType::StaticClass());
	if (OtherActor == nullptr)
		return;

	FString ActorName1 = OtherActor->GetName();
	UE_LOG(LogTemp, Warning, TEXT("ApplyDamageActor = %s"), *ActorName1);
}

