// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyUserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "LobbyPlayerController.h"
#include "TPGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "TPGameInstance.h"

void ULobbyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	{
		InputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ChatInputBox")));
		if (!InputBox)
			return;
		InputBox->OnTextChanged.AddDynamic(this, &ULobbyUserWidget::OnChangedText);
		InputBox->OnTextCommitted.AddDynamic(this, &ULobbyUserWidget::OnCommitedText);
	}

	{
		StartGameButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonStartGame")));
		if (!StartGameButton)
			return;
		StartGameButton->OnClicked.AddDynamic(this, &ULobbyUserWidget::StartGame);

		ReadyButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonReady")));
		if (!ReadyButton)
			return;
		ReadyButton->OnClicked.AddDynamic(this, &ULobbyUserWidget::Ready);

		CancelReadyButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonReadyCancel")));
		if (!CancelReadyButton)
			return;
		CancelReadyButton->OnClicked.AddDynamic(this, &ULobbyUserWidget::CancelReady);
	}

	ChatScroll = Cast<UScrollBox>(GetWidgetFromName(TEXT("ScrollChat")));

	if (GetWorld()->GetFirstPlayerController()->HasAuthority())
	{
		StartGameButton->SetVisibility(ESlateVisibility::Visible);
		ReadyButton->SetVisibility(ESlateVisibility::Collapsed);
		CancelReadyButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		StartGameButton->SetVisibility(ESlateVisibility::Collapsed);
		ReadyButton->SetVisibility(ESlateVisibility::Visible);
		CancelReadyButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	YinButton = Cast<UButton>(GetWidgetFromName(TEXT("Yin")));
	TerraButton = Cast<UButton>(GetWidgetFromName(TEXT("Terra")));
	Temp1Button = Cast<UButton>(GetWidgetFromName(TEXT("Temp1")));
	Temp2Button = Cast<UButton>(GetWidgetFromName(TEXT("Temp2")));


	if (!YinButton || !TerraButton || !Temp1Button || !Temp2Button)
	{
		return;
	}

	YinButton->OnClicked.AddDynamic(this, &ULobbyUserWidget::OnYinButtonClicked);
	TerraButton->OnClicked.AddDynamic(this, &ULobbyUserWidget::OnTerraButtonClicked); 
	Temp1Button->OnClicked.AddDynamic(this, &ULobbyUserWidget::OnTemp1ButtonClicked);
	Temp2Button->OnClicked.AddDynamic(this, &ULobbyUserWidget::OnTemp2ButtonClicked);
		
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

			if (!PC)
				return;

			UTPGameInstance* GI = Cast<UTPGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

			if (!GI)
				return;

			{
				FString Temp = FString::Printf(TEXT("%s : %s"), *GI->Username, *Text.ToString());
				//Client -> Server로 전송
				PC->C2S_SendMessage(FText::FromString(Temp)); 
			}
		}
	}
}

void ULobbyUserWidget::StartGame()
{
	GetWorld()->GetNumPlayerControllers();
	GetWorld()->ServerTravel(TEXT("Main"));
}

void ULobbyUserWidget::Ready()
{
	ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(GetOwningPlayer());

	if (!PC)
		return;

	ReadyButton->SetVisibility(ESlateVisibility::Collapsed);
	CancelReadyButton->SetVisibility(ESlateVisibility::Visible);
}

void ULobbyUserWidget::CancelReady()
{
	ReadyButton->SetVisibility(ESlateVisibility::Visible);
	CancelReadyButton->SetVisibility(ESlateVisibility::Collapsed);
}

void ULobbyUserWidget::OnButtonClicked(int num)
{


	UTPGameInstance* GI = Cast<UTPGameInstance>(GetWorld()->GetGameInstance());
	if (!GI)
		return;

	switch (num)
	{
	case 0:
		GI->GetCharacterRowData(FName("Yin"));
		break;

	case 1:
		GI->GetCharacterRowData(FName("Terra"));
		break;

	case 2:
		GI->GetCharacterRowData(FName("Temp1"));
		break;

	case 3:
		GI->GetCharacterRowData(FName("Temp1"));
		break;
	}
}

void ULobbyUserWidget::OnYinButtonClicked()
{
	OnButtonClicked(0);
}

void ULobbyUserWidget::OnTerraButtonClicked()
{
	OnButtonClicked(1);
}

void ULobbyUserWidget::OnTemp1ButtonClicked()
{
	OnButtonClicked(2);
}

void ULobbyUserWidget::OnTemp2ButtonClicked()
{
	OnButtonClicked(3);
}

void ULobbyUserWidget::AddMessage(FText const& Message)
{
	UTextBlock* NewChat = NewObject<UTextBlock>();
	if (!NewChat)
		return;

	NewChat->SetText(Message);
	NewChat->Font.Size = 18;

	if (!ChatScroll)
		return;

	ChatScroll->AddChild(NewChat);
	ChatScroll->ScrollToEnd();
}
