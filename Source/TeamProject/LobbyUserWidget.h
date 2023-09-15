// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEAMPROJECT_API ULobbyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UScrollBox* ChatScroll;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UEditableTextBox* InputBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UButton* StartGameButton;

	UFUNCTION()
	void OnChangedText(const FText& Text);

	UFUNCTION()
	void OnCommitedText(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void StartGame();


	void AddMessage(FText const& Message);

};
