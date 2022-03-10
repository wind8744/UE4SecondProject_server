// Fill out your copyright notice in the Description page of Project Settings.


#include "RecvThread.h"
#include "RecvQueue.h"
#include "NetworkManager.h"
#include "NetworkSession.h"

RecvThread::RecvThread():
	m_Session(nullptr)
	,m_Loop(false)
{
}

RecvThread::~RecvThread()
{
}

bool RecvThread::Init() 
{
	return true;
}

uint32 RecvThread:: Run() 
{
	while (m_Loop)
	{
		// 패킷 실제 데이타 (내가 받은 채팅 내용)
		uint8 Packet[PACKET_SIZE] = {};

		int32 Protocol = -1, Length = 0;

		bool Result = m_Session->Read(Protocol, Length, Packet);
		
		if (!Result) // 다시 받아라
			continue;
		
		// 데이터를 가지고 프로토콜이 뭐냐에 따라 따로 처리를 하는 system 만들기.

		// 큐를 받아옴
		RecvQueue* Que = NetworkManager::GetInst()->GetQueue();
		Que->Push(Protocol, Length, Packet);

	}

	return 0;
}

void RecvThread::Exit() 
{
	m_Loop = false;
}