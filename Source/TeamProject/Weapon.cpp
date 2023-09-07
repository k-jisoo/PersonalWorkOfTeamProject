// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Yin.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);
	Sphere->SetRelativeLocation(FVector(140.0, 0.0, 0.0));
	Sphere->SetSphereRadius(90.0f);
	Sphere->SetCollisionProfileName(TEXT("Custom"));
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AWeapon::OnSphereComponentBeginOverlap);

	UE_LOG(LogTemp, Warning, TEXT("����"));
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

void AWeapon::OnSphereComponentBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	//Interface�� �����ϸ� �� ����
	//������ Yin������ EnemyŬ������ �ٲ����.
	AYin* ch = Cast<AYin>(OtherActor);
	ch->TakeDamage(10.0f, );

	
	FString ActorName = OtherActor->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorName);
}

