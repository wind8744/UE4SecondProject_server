// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "AssetPathMain.generated.h"

/**
 *
 */
UCLASS(config = MainAsset) //confing�� MainAsset.ini ������ ����� ��
class UE4PROJ2SEVER_API UAssetPathMain : public UObject
{
	GENERATED_BODY()

public:
	UAssetPathMain();

private:
	UPROPERTY(config)
		TArray<FAssetPathInfo>	ParticlePathArray;

	TMap<FString, FSoftObjectPath>	m_mapParticlePath;

public:
	void ConvertPath();
	const FSoftObjectPath* FindParticlePath(const FString& Name);

};
