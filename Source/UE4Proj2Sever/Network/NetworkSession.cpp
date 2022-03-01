// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkSession.h"


NetworkSession::NetworkSession()
{
}

NetworkSession::~NetworkSession()
{
}


bool NetworkSession::Connect(const FString& IPAddr, int32 Port)
{
	// Create socket
	// 플랫폼(윈도우, 맥, 유닉스..) 별로 처리될 수 있도록 엔진에서 예외 처리되어 있음
	m_Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(
		NAME_Stream, TEXT("default")); 	//Stream 세션 사용


	FIPv4Address ip;
	FIPv4Address::Parse(IPAddr, ip); //ip주소 들어온 것을 여기에

	//실제 주소정보를 받아서 넘겨줌
	TSharedRef<FInternetAddr>	addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(Port);

	//접속이 되었는지 안되었는지 의 여부를 bool변수에 담음
	m_Connect = m_Socket->Connect(*addr);

	return true;
}

void NetworkSession::Close()
{
	if (m_Socket)
	{
		m_Socket->Close();
		m_Socket = nullptr;
	}

}