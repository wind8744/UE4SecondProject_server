// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "ChatUI.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROJ2SEVER_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UChatUI* m_ChatWidget;


public:
	UChatUI* GetChatWidget()
	{
		return m_ChatWidget;
	}

protected:
	virtual void NativeConstruct(); 
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

};
