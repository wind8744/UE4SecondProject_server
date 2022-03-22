// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAnimInstance.h"
#include "GameCharacter.h"

UGameAnimInstance::UGameAnimInstance()
{
	m_Direction = 0.f;
	m_Speed = 0.f;
	m_OnGround = true;
	m_AnimType = ECharAnimType::IDLE;
}

void UGameAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UGameAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AGameCharacter* Player = Cast<AGameCharacter>(TryGetPawnOwner());

	if (Player)
	{
		UCharacterMovementComponent* Movement = Player->GetCharacterMovement();
		if (Movement)
		{
			m_Speed = Movement->Velocity.Size();

			bool OnGround = Movement->IsMovingOnGround();
			m_OnGround = OnGround;

			if (m_OnGround && m_AnimType == ECharAnimType::FALL)
				m_AnimType = ECharAnimType::IDLE;
			
			if (!m_OnGround && m_AnimType != ECharAnimType::JUMP && m_AnimType != ECharAnimType::SKILL)
				m_AnimType = ECharAnimType::FALL;
		
		}
	}
}

void UGameAnimInstance::AnimNotify_AttackEnd()
{
	m_Attack = false;

	AGameCharacter* Player = Cast<AGameCharacter>(TryGetPawnOwner());
	if (Player)
		Player->AttackEnd();
}

void UGameAnimInstance::AnimNotify_AttackCombo()
{
	AGameCharacter* Player = Cast<AGameCharacter>(TryGetPawnOwner());

	if (Player)
		Player->EnableAttack(true);
}