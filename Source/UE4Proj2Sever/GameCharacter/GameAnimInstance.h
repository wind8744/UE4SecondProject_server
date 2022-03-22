// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "GameAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROJ2SEVER_API UGameAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UGameAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float	 m_Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float	 m_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))  
		bool	 m_Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool	m_OnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true")) 
		ECharAnimType		m_AnimType;

public:
	void SetDirection(float Direction) { m_Direction = Direction; }
	void SetAttackEnable(bool Attack) { m_Attack = Attack; }
	void SetAnimType(ECharAnimType Type) { m_AnimType = Type; }

	float GetDirection() { return m_Direction; }
	bool GetAttack() { return m_Attack; }
	ECharAnimType GetAnimType() { return m_AnimType; }

public:
	virtual void NativeInitializeAnimation();

	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeUpdateAnimation.
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	// Notify function
	UFUNCTION() 
		void AnimNotify_AttackEnd();
	
	UFUNCTION()
		void AnimNotify_AttackCombo();
};
