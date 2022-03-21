// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkSession.h"
#include "PacketStream.h"

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
	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
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
		//m_Socket = nullptr;
		delete m_Socket;
	}

}


bool NetworkSession::Read(int32& Protocol, int32& Length, uint8* Packet)
{
	bool Result = m_Socket->Recv(m_RecvPacket, PACKET_SIZE, Length, ESocketReceiveFlags::None);
	
	if (!Result || Length <= 0)
		return false;
	
	// 읽어온 패킷으로부터 "프로토콜"과 실제 "패킷부분의 길이" "패킷의 내용"을 분리한다.
	PacketStream stream;
	stream.SetBuffer(m_RecvPacket);

	stream.Read(&Protocol, sizeof(int32));
	stream.Read(&Length, sizeof(int32));
	stream.Read(Packet, Length);

	return true;
}

bool NetworkSession::Write(int32 Protocol, int32 Length, uint8* Packet)
{
	// 보내고자 하는 프로토콜, 길이, 패킷 내용을 하나의 버퍼에 넣어서 보내주도록 한다.
	PacketStream stream;
	stream.SetBuffer(m_SendPacket);

	stream.Write(&Protocol, sizeof(int32));
	stream.Write(&Length, sizeof(int32));
	stream.Write(Packet, Length);

	// 다 써준 후 +8(byte)만큼 , Length에 보낸 크기를 받아오기
	return m_Socket->Send(m_SendPacket, Length + 8, Length);
}