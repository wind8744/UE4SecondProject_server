// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "UE4Proj2GameInstance.generated.h"

/**
 * 게임 실행시 한번만 만들어짐
 */
UCLASS()
class UE4PROJ2SEVER_API UUE4Proj2GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UUE4Proj2GameInstance();
	~UUE4Proj2GameInstance();

private:

public:
	virtual void Init();

};
