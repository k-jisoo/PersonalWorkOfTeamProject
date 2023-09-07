// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackCollisionComponent.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UAttackCollisionComponent::UAttackCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetRelativeLocation(FVector(140.0, 0.0, 0.0));
	Sphere->SetSphereRadius(90.0f);
	Sphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}


// Called when the game starts
void UAttackCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

