// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyAttackFinished.h"
#include "Yin.h"
#include "Weapon.h"

void UAnimNotifyAttackFinished::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AYin* pChar = Cast<AYin>(MeshComp->GetOwner());
	if (!IsValid(pChar))
		return;

	AWeapon* weapon = pChar->Weapon;
	if (!IsValid(weapon))
		return;

	weapon->SetSphereCollisionState(false);
}