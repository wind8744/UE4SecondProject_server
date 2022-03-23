// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "MinimapUI.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROJ2SEVER_API UMinimapUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UImage* m_PlayerPoint;

	TArray<UImage*>	m_MonsterArray;
	int			m_AddCnt;

private:
	void CreateMonsterArray();

public:
	void RotPoint(float Z);
	void ClearMonster();
	void AddMonster(const FVector& MonPos);

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

};
