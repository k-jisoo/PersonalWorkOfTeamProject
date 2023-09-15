// Fill out your copyright notice in the Description page of Project Settings.


#include "EntryHUD.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AEntryHUD::BeginPlay()
{
	Super::BeginPlay();

	check(HudWidgetClass);

	HudWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
	HudWidget->AddToViewport();

	APlayerController* player0 = GetWorld()->GetFirstPlayerController();
	if (IsValid(player0) == false)
		return;

	player0->SetInputMode(FInputModeUIOnly());
	player0->bShowMouseCursor = true;
}
