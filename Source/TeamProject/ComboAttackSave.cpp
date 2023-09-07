// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboAttackSave.h"
#include "Yin.h"

void UComboAttackSave::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AYin* pChar = Cast<AYin>(MeshComp->GetOwner());

	if (IsValid(pChar) == false)
		return;

	pChar->ComboAttackSave();
}