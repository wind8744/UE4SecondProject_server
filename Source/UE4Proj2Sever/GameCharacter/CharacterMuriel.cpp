// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMuriel.h"

// Sets default values
ACharacterMuriel::ACharacterMuriel()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MurielAsset(TEXT("SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Skins/Tier_1/Muriel_Black/Meshes/MurielBlack.MurielBlack'"));
	
	if (MurielAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MurielAsset.Object);

	// Anim Asset
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Player/Muriel/BPMurielAnim.BPMurielAnim_C'")); 
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	
	// Info
	m_CharInfo.Name = TEXT("Test1");
	m_CharInfo.Job = ECharJob::Wizard;
	m_CharInfo.HP = 120;
	m_CharInfo.MP = 20;
}

// Called when the game starts or when spawned
void ACharacterMuriel::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACharacterMuriel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterMuriel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

