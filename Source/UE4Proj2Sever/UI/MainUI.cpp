// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"


void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();

	m_ChatWidget = Cast<UChatUI>(GetWidgetFromName(TEXT("ChatUI")));
}

void UMainUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
