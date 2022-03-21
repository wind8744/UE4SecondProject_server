// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatUI.h"
#include "../Network/NetworkManager.h"
#include "../Network/NetworkSession.h"
#include "ChatDataObj.h"

void UChatUI::NativeConstruct()
{
	Super::NativeConstruct();

	m_ChatList = Cast<UListView>(GetWidgetFromName(TEXT("ChatList")));
	m_SendBtn = Cast<UButton>(GetWidgetFromName(TEXT("SendButton")));
	m_Input = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("TextInput")));

	m_SendBtn->OnClicked.AddDynamic(this, &UChatUI::SendBtnClick);
}

void UChatUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UChatUI::SendBtnClick()
{
	// send message to server
	FString InputChat = m_Input->GetText().ToString();

	// Print my message ** 수정
	AddMyMessage(InputChat);

	//PrintViewport(1.f,FColor::Red,InputChat);

	// make packet
	uint8 Packet[PACKET_SIZE] = {};
	int32 Length = InputChat.Len() * sizeof(TCHAR);
	FMemory::Memcpy(Packet, *InputChat, Length);

	NetworkSession* Session = NetworkManager::GetInst()->GetSession();
	Session->Write((int)NetworkProtocol::Chat,Length,Packet);

}

void UChatUI::AddMessage(const FString& Msg)
{
	UChatDataObj* Data = NewObject<UChatDataObj>(this, UChatDataObj::StaticClass());
	Data->SetMessage(Msg);

	m_ChatList->AddItem(Data);
	m_ChatList->ScrollToBottom(); // 자동으로 스크롤 
}

void UChatUI::AddMyMessage(const FString& Mgr)
{
	UChatDataObj* Data = NewObject<UChatDataObj>(this, UChatDataObj::StaticClass());
	Data->SetMessage(Mgr);
	Data->SetFlag(true);

	m_ChatList->AddItem(Data);
	m_ChatList->ScrollToBottom(); // 자동으로 스크롤 
}