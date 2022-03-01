// Fill out your copyright notice in the Description page of Project Settings.


#include "RecvThread.h"
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
		uint8 Packet[PACKET_SIZE] = {};
		//bool Result = m_Session;
	}

	return 0;
}

void RecvThread::Exit() 
{
	m_Loop = false;
}