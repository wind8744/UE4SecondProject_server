// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Blueprint/UserWidget.h"
#include "ChatUI.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROJ2SEVER_API UChatUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UButton* m_SendBtn;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UListView* m_ChatList;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UEditableTextBox* m_Input;

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	UFUNCTION()
		void SendBtnClick();

	void AddMessage(const FString& Msg);

};
