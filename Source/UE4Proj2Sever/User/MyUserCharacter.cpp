// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserCharacter.h"


AMyUserCharacter::AMyUserCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AuroraAsset(TEXT("SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));
	if (AuroraAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(AuroraAsset.Object);
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
