// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameInstance.h"
#include "BaseCharacter.h"
#include "Engine/DataTable.h"

FST_Character* UTPGameInstance::GetCharacterRowData(FName name)
{
	if (!CharacterData)
		return nullptr;

	MyCharacter = CharacterData->FindRow<FST_Character>(name, TEXT("")) ? CharacterData->FindRow<FST_Character>(name, TEXT("")) : nullptr;

	return MyCharacter;
}
