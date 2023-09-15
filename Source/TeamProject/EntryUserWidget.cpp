// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryUserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "LobbyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TPGameInstance.h"

void UEntryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));


	StartServerButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonStartServer")));
	if (StartServerButton)
	{
		StartServerButton->OnClicked.AddDynamic(this, &UEntryUserWidget::StartServer);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("StartServerButton not found"));
	}

	ConnectButton = Cast<UButton>(GetWidgetFromName(TEXT("ButtonConnect")));
	if (ConnectButton)
	{
		ConnectButton->OnClicked.AddDynamic(this, &UEntryUserWidget::ConnectClient);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ConnectButton not found"));
	}
}

void UEntryUserWidget::StartServer()
{
	SetUserName();

	UGameplayStatics::OpenLevel(GetWorld(), "Lobby", true, "listen");
}

void UEntryUserWidget::SetUserName()
{
	UTPGameInstance* gameInstance = Cast<UTPGameInstance>(
	UGameplayStatics::GetGameInstance(GetWorld()));

	if (!gameInstance) 
	{
		UE_LOG(LogTemp, Warning, TEXT("gameInstance not found"));
		return;
	}
	NameInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("InputBoxName")));

	if (!NameInputBox) 
	{
		UE_LOG(LogTemp, Warning, TEXT("NameInputBox not found"));
		return;
	}

	gameInstance->Username = NameInputBox->GetText().ToString();
}

void UEntryUserWidget::ConnectClient()
{
	SetUserName();

	AddressInputBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("InputBoxAddress")));
	
	if (!AddressInputBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("AddressInputBox not found"));
		return;
	}

	FText InputText = AddressInputBox->GetText();

	UGameplayStatics::OpenLevel(GetWorld(), FName(InputText.ToString()));
}
