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

	if (m_RunnableThread)
	{
		m_RunnableThread->Kill();
		m_RunnableThread->WaitForCompletion();
		m_RunnableThread = nullptr;
	}

	if (m_Thread)
	{
		m_Thread->Exit();

		delete m_Thread;
		m_Thread = nullptr;
	}


	if (m_Session)
		delete m_Session;
}

bool NetworkManager::Init()
{
	if (m_Run)
		return true;

	m_Run = true;

	// 세션을 하나 만듦.
	m_Session = new NetworkSession; 
	
	// 127.0.0.1 은 로컬. 현재 이 컴의 ip 주소, 서버에 접속요청 할 것임
	bool Connect = m_Session->Connect(TEXT("192.168.0.8"), 6000);
	
	// 접속이 되면
	if(Connect)
	{
		// 스레드를 만든다. RecvThread 에서 계속 while로 패킷을 받을 것임.
		m_Thread = new RecvThread;

		//  스레드에서 사용할 세션을 넘겨줌
		m_Thread->SetSession(m_Session);

		// 스레드를 생성한다.
		m_RunnableThread = FRunnableThread::Create(m_Thread, TEXT("RecvThread"));
	}

	// ** 메모리 동시 참조에서 문제가 될 수 있다.


	return true;
}