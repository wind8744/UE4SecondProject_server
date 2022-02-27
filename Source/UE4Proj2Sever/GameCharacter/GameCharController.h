// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "GameCharController.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROJ2SEVER_API AGameCharController : public APlayerController
{
	GENERATED_BODY()

public:
	AGameCharController();

protected:
	bool m_bLClicked;
	bool m_bRClicked;


protected:
	virtual void SetupInputComponent() override;

	void PressedRClick();
	void ReleasedRClick();
	
	void PressedLClick();
	void ReleasedLClick();
	
	void SetNewDestination(const FVector DestLocation);
	void MoveToMouseCursor();

	virtual void PlayerTick(float DeltaTime) override;


};
