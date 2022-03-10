// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterMurdock.h"

// Sets default values
ACharacterMurdock::ACharacterMurdock()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MurdockAsset(TEXT("SkeletalMesh'/Game/ParagonMurdock/Characters/Heroes/Murdock/Skins/CS_Magma/Mesh/Murdock_Magma.Murdock_Magma'"));
	if (MurdockAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MurdockAsset.Object);

	// Anim Asset
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Player/Murdock/BPMurdockAnim.BPMurdockAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
}

// Called when the game starts or when spawned
void ACharacterMurdock::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACharacterMurdock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterMurdock::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

