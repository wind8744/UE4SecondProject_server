// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserCharacter.h"


AMyUserCharacter::AMyUserCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MurielAsset(TEXT("SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Skins/Tier_1/Muriel_Black/Meshes/MurielBlack.MurielBlack'"));
	if (MurielAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MurielAsset.Object);

}


// Called when the game starts or when spawned
void AMyUserCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyUserCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
