// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameCharacter.h"
#include "CharacterKwang.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROJ2SEVER_API ACharacterKwang : public AGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterKwang();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*>	m_AttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*>	m_SkillMontageArray;

	int			m_AttackIdx;

public:
	virtual void AttackEnd();

protected:
	virtual void Attack();
	virtual void Dash();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
