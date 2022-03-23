// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameCharacter.h"
#include "../Effect/AuroraSkill.h"
#include "CharacterAurora.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROJ2SEVER_API ACharacterAurora : public AGameCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterAurora();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*>	m_AttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<UAnimMontage*>	m_SkillMontageArray;

	// 스킬이 사용될 때 스킬bp가 생성되어야 하므로 그것을 멤버변수로 가지고  있는것
	TSubclassOf<AAuroraSkill>	m_SkillClass; 
	
	//class AWeapon* m_Weapon;

	int			m_AttackIdx;

public:
	virtual void AttackEnd();
	virtual void NormalAttack();
	virtual void UseSkill();

protected:
	virtual void Attack();
	virtual void Dash();
	virtual void Skill1();
	virtual void Skill2();
	virtual void Skill3();

private:
	void AuroraSkill2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
