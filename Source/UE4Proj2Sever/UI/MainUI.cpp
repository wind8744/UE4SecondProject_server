// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"


void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	//m_CharacterHUD = Cast<UCharacterHUD>(GetWidgetFromName(TEXT("UI_CharacterHUD")));
}

void UMainUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
