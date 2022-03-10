// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

/**
 * 동기화 처리를 위해서 
 * circle Queue를 통해서 recv thread와 main thread 간에 데이터를 주고받을 수 있도록 작업
 */
class UE4PROJ2SEVER_API RecvQueue
{
public:
	RecvQueue();
	~RecvQueue();

private:
	FCriticalSection	m_Crt;
	RecvQueueData		m_Queue[200];
	int32				m_Head;
	int32				m_Tail;
	int32				m_Size;

public:
	void Push(int32 Protocol, int32 Length, uint8* Packet);
	bool Pop(int32& Protocol, int32& Length, uint8* Packet);
	bool Empty();
	int32 Size();

};
