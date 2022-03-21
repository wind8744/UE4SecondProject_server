// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameInfo.h"
#include "UI/MainUI.h"
#include "GameFramework/GameModeBase.h"
#include "UE4Proj2SeverGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROJ2SEVER_API AUE4Proj2SeverGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUE4Proj2SeverGameModeBase();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UMainUI>	m_MainUIClass;

	UMainUI* m_MainWidget;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
