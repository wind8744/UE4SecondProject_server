// Fill out your copyright notice in the Description page of Project Settings.


#include "RecvQueue.h"

// 큐는 써클 큐 사용. 일반 큐는 다 쓰면 또 못쓰니까
// 데이타를 받아서 큐에 넣을 때 !!동기화!!
// 큐에서 데이타를 뺄 때(데이타 받는것이 있을때 기다렸다가) !!동기화!!
RecvQueue::RecvQueue():
	m_Head(0),
	m_Tail(0)
{
}

RecvQueue::~RecvQueue()
{
}

void RecvQueue::Push(int32 Protocol, int32 Length, uint8* Packet)
{
	FScopeLock  lock(&m_Crt);
	int32 tail = (m_Tail + 1) % 200;
	
	if (m_Head == tail)
		return;

	m_Queue[tail].Protocol = Protocol;
	m_Queue[tail].Length = Length;

	FMemory::Memset(m_Queue[tail].Packet, 0, PACKET_SIZE); // 0 초기화
	FMemory::Memset(m_Queue[tail].Packet, *Packet, Length); // queue에 packet 복사

	m_Tail = tail;

}

bool RecvQueue::Pop(int32& Protocol, int32& Length, uint8* Packet)
{
	FScopeLock  lock(&m_Crt);

	if (!Empty())
	{
		int32 head = (m_Head + 1) % 200;

		Protocol = m_Queue[head].Protocol;
		Length = m_Queue[head].Length;

		FMemory::Memcpy(Packet, m_Queue[head].Packet, Length); // 패킷에 큐에서 현재 꺼낼 데이타 복붙

		m_Head = head;

		return true;
	}

	return false;
}

bool RecvQueue::Empty()
{
	return m_Size == 0;
}

int32 RecvQueue::Size()
{
	return m_Size;
}
