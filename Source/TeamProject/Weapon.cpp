// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Yin.h"
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
	//Interface로 구현하면 더 좋음
	//지금은 Yin이지만 Enemy클래스로 바꿔야함.

	//AYin* HitChar;

	
	////ApplyDamage로 데미지를 넘기면
	////상대는 TakeDamage를 override했다면 데미지를 받는다.
	//UGameplayStatics::ApplyDamage(HitChar, OwnChar->Damage, OwnChar->GetController(), this, UDamageType::StaticClass());
	if (OtherActor == nullptr)
		return;

	if (OwnChar != OtherActor) 
	{
		FString ActorName1 = OtherActor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorName1);
	}
}

