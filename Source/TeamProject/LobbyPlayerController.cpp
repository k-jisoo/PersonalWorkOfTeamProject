// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "LobbyUserWidget.h"

void ALobbyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("%s"), *(this->GetName()));

    APlayerController* myPlayerController = GetWorld()->GetFirstPlayerController();

    if (!myPlayerController)
        return;
    
    if (!(myPlayerController->IsLocalPlayerController()))
        return;
    
    if (!LobbyWidgetClass)
        return;
    LobbyWidget = CreateWidget<UUserWidget>(GetWorld(), LobbyWidgetClass);
    LobbyWidget->AddToViewport();
    

    myPlayerController->SetInputMode(FInputModeUIOnly());
    myPlayerController->bShowMouseCursor = true;

}

bool ALobbyPlayerController::C2S_SendMessage_Validate(FText const& Message)
{
    //메세지 검증
    return true;
}

void ALobbyPlayerController::C2S_SendMessage_Implementation(FText const& Message)
{
    UE_LOG(LogTemp, Warning, TEXT("server : %s"), *Message.ToString());
    //Find All PC
    for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
    {
        ALobbyPlayerController* PC = Cast<ALobbyPlayerController>(*Iter);
        if (PC)
        {
            PC->S2C_SendMessage(Message);
        }
    }

}

void ALobbyPlayerController::S2C_SendMessage_Implementation(FText const& Message)
{
    //UI 메세지 추가
    ULobbyUserWidget* Widget = Cast<ULobbyUserWidget>(LobbyWidget);
    if (Widget)
    {
        Widget->AddMessage(Message);
    }
}
