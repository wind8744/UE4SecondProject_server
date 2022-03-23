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

	class UAssetPathMain* m_MainAssetPath;
	class UMainUI* m_MainWidget;

public:
	UMainUI* GetMainUI() { return m_MainWidget; }

public:

	/**
	 * Initialize the game.
	 * The GameMode's InitGame() event is called before any other functions (including PreInitializeComponents() )
	 * and is used by the GameMode to initialize parameters and spawn its helper classes.
	 * @warning: this is called before actors' PreInitializeComponents.
	 */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
