// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

/**
 * ���� ���ۿ� ���� ~ ���� ����
 */
class UE4PROJ2SEVER_API NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

private:
	class NetworkSession*	m_Session;
	bool					m_Run; //thread
	class RecvThread*		m_Thread;
	FRunnableThread*		m_RunnableThread;

public:
	bool Init();

private:
	static NetworkManager* m_Inst;

public:
	static NetworkManager* GetInst()
	{
		if (!m_Inst)
			m_Inst = new NetworkManager;

		return m_Inst;
	}

	static void DestoryInst()
	{
		if (m_Inst)
		{
			delete m_Inst;
			m_Inst = nullptr;
		}
	}
};
