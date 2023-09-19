// Fill out your copyright notice in the Description page of Project Settings.


#include "TPGameInstance.h"
#include "Yin.h"

FST_Character* UTPGameInstance::GetCharacterRowData(FName name)
{
	if (!CharacterData)
		return nullptr;
	MyCharacter = CharacterData->FindRow<FST_Character>(name, TEXT("")) ? CharacterData->FindRow<FST_Character>(name, TEXT("")) : nullptr;

	UE_LOG(LogTemp, Warning, TEXT("CharacterData's Name: %s"), MyCharacter);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Black, MyCharacter->AnimBP->GetClass()->GetName(), true);
	return MyCharacter;
}
