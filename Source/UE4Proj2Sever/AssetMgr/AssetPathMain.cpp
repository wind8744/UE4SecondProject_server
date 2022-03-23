// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetPathMain.h"

UAssetPathMain::UAssetPathMain()
{
}

void UAssetPathMain::ConvertPath()
{
	for (auto& result : ParticlePathArray)
	{
		m_mapParticlePath.Add(result.Name, result.Path);
		LOG(TEXT("Name : %s Path : %s"), *result.Name, *result.Path.ToString());
	}

}

const FSoftObjectPath* UAssetPathMain::FindParticlePath(const FString& Name)
{
	return m_mapParticlePath.Find(Name);
}
