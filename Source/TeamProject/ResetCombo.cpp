// Fill out your copyright notice in the Description page of Project Settings.

#include "ResetCombo.h"
#include "Yin.h"

void UResetCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	AYin* pChar = Cast<AYin>(MeshComp->GetOwner()); \

		if (IsValid(pChar) == false)
			return;

	pChar->ResetCombo();
}
