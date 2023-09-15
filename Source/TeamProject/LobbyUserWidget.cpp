// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyUserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "LobbyPlayerController.h"
#include "TPGameInstance.h"
#include "Kismet/GameplayStatics.h"

void ULobbyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();


	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));

	InputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ChatInputBox")));
	if (InputBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputBox init"));

		InputBox->OnTextChanged.AddDynamic(this, &ULobbyUserWidget::OnChangedText);
		InputBox->OnTextCommitted.AddDynamic(this, &ULobbyUserWidget::OnCommitedText);
	}

	StartGameButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonStartGame")));
	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &ULobbyUserWidget::StartGame);
	}

	ChatScroll = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollChat")));
}

void ULobbyUserWidget::OnChangedText(const FText& Text)
{
}

void ULobbyUserWidget::OnCommitedText(const FText& Text, ETextCommit::Type CommitMethod)
{
	switch (CommitMethod)
	{
		case ETextCommit::OnEnter:
		{
			//메세지 만들어서 서버로 전송
			ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(GetOwningPlayer());
			if (PC)
			{
				UTPGameInstance* GI = Cast<UTPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
				if (GI)
				{
					UE_LOG(LogTemp, Warning, TEXT("Send Message"));

					FString Temp = FString::Printf(TEXT("%s : %s"), *GI->Username, *Text.ToString());
					//Client -> Server로 전송
					PC->C2S_SendMessage(FText::FromString(Temp));
				}
			}
		}
	}
}

void ULobbyUserWidget::StartGame()
{
	//다함께 맵 이동
	GetWorld()->ServerTravel(TEXT("Main"));
}

void ULobbyUserWidget::AddMessage(FText const& Message)
{
	UTextBlock* NewChat = NewObject<UTextBlock>();
	if (NewChat)
	{
		NewChat->SetText(Message);
		NewChat->Font.Size = 18;
		if (!ChatScroll)
		{
			UE_LOG(LogTemp, Warning, TEXT("ChatScroll Not Found"));
			return;
		}
		ChatScroll->AddChild(NewChat);
		ChatScroll->ScrollToEnd();
	}
}
