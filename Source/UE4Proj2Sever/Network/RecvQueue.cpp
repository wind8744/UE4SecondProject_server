// Fill out your copyright notice in the Description page of Project Settings.


#include "RecvQueue.h"

// ť�� ��Ŭ ť ���. �Ϲ� ť�� �� ���� �� �����ϱ�
// ����Ÿ�� �޾Ƽ� ť�� ���� �� !!����ȭ!!
// ť���� ����Ÿ�� �� ��(����Ÿ �޴°��� ������ ��ٷȴٰ�) !!����ȭ!!
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

	FMemory::Memset(m_Queue[tail].Packet, 0, PACKET_SIZE); // 0 �ʱ�ȭ
	FMemory::Memset(m_Queue[tail].Packet, *Packet, Length); // queue�� packet ����

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

		FMemory::Memcpy(Packet, m_Queue[head].Packet, Length); // ��Ŷ�� ť���� ���� ���� ����Ÿ ����

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
