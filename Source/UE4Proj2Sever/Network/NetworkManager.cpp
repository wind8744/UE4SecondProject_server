// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"
#include "NetworkSession.h"
#include "RecvQueue.h"
#include "RecvThread.h"

NetworkManager* NetworkManager::m_Inst = nullptr;

NetworkManager::NetworkManager():
	m_Session(nullptr)
	, m_Run(false)
	, m_Thread(nullptr)
	, m_RunnableThread(nullptr)
{
}

NetworkManager::~NetworkManager()
{
	if (m_Session)
		m_Session->Close();

	if (m_Session)
		delete m_Session;
}

bool NetworkManager::Init()
{
	if (m_Run)
		return true;

	m_Run = true;

	// ������ �ϳ� ����.
	m_Session = new NetworkSession; 
	
	// 127.0.0.1 �� ����. ���� �� ���� ip �ּ�, ������ ���ӿ�û �� ����
	bool Connect = m_Session->Connect(TEXT("127.0.0.1"), 6000);
	
	// ������ �Ǹ�
	if(Connect)
	{
		// �����带 �����. RecvThread ���� ��� while�� ��Ŷ�� ���� ����.
		m_Thread = new RecvThread;

		//  �����忡�� ����� ������ �Ѱ���
		m_Thread->SetSession(m_Session);

		// �����带 �����Ѵ�.
		m_RunnableThread = FRunnableThread::Create(m_Thread, TEXT("RecvThread"));
	}

	// ** �޸� ���� �������� ������ �� �� �ִ�.


	return true;
}