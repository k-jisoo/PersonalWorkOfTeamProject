// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameInstance.h"

FST_Character* UTPGameInstance::GetCharacterRowData(FName name)
{
	return CharacterData->FindRow<FST_Character>(name, TEXT(""));
}
