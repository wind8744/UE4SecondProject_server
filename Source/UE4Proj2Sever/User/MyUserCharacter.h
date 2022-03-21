// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UserCharacter.h"
#include "MyUserCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROJ2SEVER_API AMyUserCharacter : public AUserCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyUserCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
