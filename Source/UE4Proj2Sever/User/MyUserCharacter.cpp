// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserCharacter.h"


AMyUserCharacter::AMyUserCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MurdockAsset(TEXT("SkeletalMesh'/Game/ParagonMurdock/Characters/Heroes/Murdock/Skins/CS_Magma/Mesh/Murdock_Magma.Murdock_Magma'"));
	if (MurdockAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MurdockAsset.Object);
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
