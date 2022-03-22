// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAurora.h"
#include "GameAnimInstance.h"

// Sets default values
ACharacterAurora::ACharacterAurora()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AuroraAsset(TEXT("SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));
	if (AuroraAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(AuroraAsset.Object);

	// Anim Asset
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Player/Aurora/BPAuroraAnim.BPAuroraAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	// Montage Asset (Combo Attack)
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack1Asset(TEXT("AnimMontage'/Game/Player/Aurora/AMAttack1.AMAttack1'"));
	if (Attack1Asset.Succeeded())
		m_AttackMontageArray.Add(Attack1Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack2Asset(TEXT("AnimMontage'/Game/Player/Aurora/AMAttack2.AMAttack2'"));
	if (Attack2Asset.Succeeded())
		m_AttackMontageArray.Add(Attack2Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack3Asset(TEXT("AnimMontage'/Game/Player/Aurora/AMAttack3.AMAttack3'"));
	if (Attack3Asset.Succeeded())
		m_AttackMontageArray.Add(Attack3Asset.Object);
	
	m_AttackIdx = 0;

	// Info
	m_CharInfo.Name = TEXT("aurora");
	m_CharInfo.Job = ECharJob::Wizard;
	m_CharInfo.HP = 120;
	m_CharInfo.MP = 20;
}

// Called when the game starts or when spawned
void ACharacterAurora::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACharacterAurora::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterAurora::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ACharacterAurora::Attack()
{
	if (!m_AnimInst->Montage_IsPlaying(m_AttackMontageArray[m_AttackIdx]))
	{
		m_AnimInst->Montage_SetPosition(m_AttackMontageArray[m_AttackIdx], 0.f);
		m_AnimInst->Montage_Play(m_AttackMontageArray[m_AttackIdx]);
		m_AnimInst->SetAttackEnable(true);

		m_AttackIdx = (m_AttackIdx + 1) % m_AttackMontageArray.Num();
	}
}

void ACharacterAurora::Dash()
{

}

void ACharacterAurora::AttackEnd()
{
	Super::AttackEnd();
	
	m_AttackIdx = 0;
}