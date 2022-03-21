// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4Proj2GameInstance.h"
#include "Network/NetworkManager.h"

UUE4Proj2GameInstance::UUE4Proj2GameInstance()
{
	//static ConstructorHelpers::FObjectFinder<UDataTable> CharInfoTableAsset(TEXT(""));
	//if (CharInfoTableAsset.Succeeded())
	//	m_CharInfoTable = CharInfoTableAsset.Object;
}

UUE4Proj2GameInstance::~UUE4Proj2GameInstance()
{
	// Destory Network Manager 
	NetworkManager::DestoryInst(); 
}

void UUE4Proj2GameInstance::Init()
{
	Super::Init();

	// Init Network Mgr
	NetworkManager::GetInst()->Init();

}

const FCharInfoTable* UUE4Proj2GameInstance::FindCharInfo(const FString& name)
{
	return m_CharInfoTable->FindRow<FCharInfoTable>(*name, "");
}