// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Yin.h"
#include "TPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API UTPGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* CharacterData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FST_Character* GetCharacterRowData(FName name);

};
