// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"
#include "NetworkSession.h"
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
	m_Session = new NetworkSession;
	
	// 127.0.0.1 은 로컬. 현재 이 컴의 ip 주소
	bool Connect = m_Session->Connect(TEXT("127.0.0.1"), 6000);
	if(Connect)
	{
		// 스레드가 동작시켜줄 객체를 생성한다.
		m_Thread = new RecvThread;

		//  스레드에서 사용할 세션을 넘겨줌
		m_Thread->SetSession(m_Session);

		// 스레드를 생성한다.
		m_RunnableThread = FRunnableThread::Create(m_Thread, TEXT("RecvThread"));
	}


	return true;
}