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
	// �÷���(������, ��, ���н�..) ���� ó���� �� �ֵ��� �������� ���� ó���Ǿ� ����
	m_Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(
		NAME_Stream, TEXT("default")); 	//Stream ���� ���


	FIPv4Address ip;
	FIPv4Address::Parse(IPAddr, ip); //ip�ּ� ���� ���� ���⿡

	//���� �ּ������� �޾Ƽ� �Ѱ���
	TSharedRef<FInternetAddr>	addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(Port);

	//������ �Ǿ����� �ȵǾ����� �� ���θ� bool������ ����
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


bool NetworkSession::Read(int32& Protocol, int32& Length, uint8* Packet)
{
	bool Result = m_Socket->Recv(m_RecvPacket, PACKET_SIZE, Length, ESocketReceiveFlags::None);
	
	if (!Result || Length <= 0)
		return false;
	
	// �о�� ��Ŷ���κ��� �������ݰ� ���� ��Ŷ�κ��� ����, ��Ŷ�� ������ �и��Ѵ�.


	return true;
}

bool NetworkSession::Write(int32 Protocol, int32 Length, uint8* Packet)
{
	// �������� �ϴ� ��������, ����, ��Ŷ ������ �ϳ��� ���ۿ� �־ �����ֵ��� �Ѵ�.

	return true;
}