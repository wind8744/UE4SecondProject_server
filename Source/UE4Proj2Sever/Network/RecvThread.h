// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

/**
 * 
 */
class UE4PROJ2SEVER_API RecvThread:
	public FRunnable //상속받아야 스레드 사용 가능
{
public:
	RecvThread();
	~RecvThread();

private:
	bool					m_Loop;
	class NetworkSession*	m_Session;

public:
	void SetSession(class NetworkSession* Session)
	{
		m_Session = Session;
	}

public:
	bool Init();
	uint32 Run();
	void Exit();

};
