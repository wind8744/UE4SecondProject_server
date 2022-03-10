// Fill out your copyright notice in the Description page of Project Settings.


#include "PacketStream.h"

PacketStream::PacketStream() :
	m_Length(0),
	m_Buffer(nullptr)
{
}

PacketStream::~PacketStream()
{
}

void PacketStream::Read(void* Data, int32 Size)
{
	// 버퍼를 바이트단위로 쪼개어 쓰고 읽어오는 작업(포인터에 길이만큼)
	FMemory::Memcpy(Data, m_Buffer + m_Length, Size);
	m_Length += Size;

}

void PacketStream::Write(void* Data, int32 Size)
{
	FMemory::Memcpy(m_Buffer + m_Length, Data, Size);
	m_Length += Size;

}