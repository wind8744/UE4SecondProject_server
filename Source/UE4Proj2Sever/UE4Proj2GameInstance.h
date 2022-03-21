// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "UE4Proj2GameInstance.generated.h"

/**
 * 게임 실행시 한번만 만들어짐
 */

USTRUCT(BlueprintType)
struct FCharInfoTable:
	public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FString		Name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		ECharJob	Job;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32		HP;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32		MP;

};


UCLASS()
class UE4PROJ2SEVER_API UUE4Proj2GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UUE4Proj2GameInstance();
	~UUE4Proj2GameInstance();

private:
	UPROPERTY()
	UDataTable* m_CharInfoTable;

	FString		m_CharName;
	ECharJob	m_CharJob;
	
public:
	void SetCharName(const FString& name) { m_CharName = name; }
	void SetCharJob(ECharJob job) { m_CharJob = job; }

public:
	const FCharInfoTable* FindCharInfo(const FString& name);

public:
	virtual void Init();

};
