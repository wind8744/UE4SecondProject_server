// Fill out your copyright notice in the Description page of Project Settings.

// ���� ���
#pragma once

#include "EngineMinimal.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "EngineGlobals.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

#include "GameInfo.generated.h"

#define PACKET_SIZE	1024

DECLARE_LOG_CATEGORY_EXTERN(UE4Proj2Server, Log, All);
#define	LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("{") + FString::FromInt(__LINE__) + TEXT("}"))
#define	LOG(Format, ...)	UE_LOG(UE4Proj2Server, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
#define	LOGSTRING(Str)		UE_LOG(UE4Proj2Server, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *Str)

void PrintViewport(float Time, const FColor& Color, const FString& Text);

UENUM(BlueprintType)
enum class ECharAnimType : uint8
{
	GROUND,
	IDLE,
	RUN,
	JUMP,
	FALL,
	ATTACK,
	SKILL,
	DEATH,
};