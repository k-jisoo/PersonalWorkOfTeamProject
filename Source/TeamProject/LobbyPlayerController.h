// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	//UFUNCTION(Server, Unreliable)
	UFUNCTION(Server, Reliable, WithValidation)
	void C2S_SendMessage(FText const& Message); //ȣ��� -> Network -> RPC
	bool C2S_SendMessage_Validate(FText const& Message);
	void C2S_SendMessage_Implementation(FText const& Message);

	UFUNCTION(Client, Reliable)
	void S2C_SendMessage(FText const& Message);  //ȣ��� -> Network -> RPC
	void S2C_SendMessage_Implementation(FText const& Message);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> LobbyWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* LobbyWidget;
};
