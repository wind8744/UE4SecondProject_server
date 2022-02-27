// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE4Proj2SeverGameModeBase.h"

AUE4Proj2SeverGameModeBase::AUE4Proj2SeverGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("Blueprint'/Game/Player/Muriel/BPMuriel.BPMuriel_C'"));
	
	// Set default pawn
	if (PawnClass.Succeeded())
		DefaultPawnClass = PawnClass.Class;
	
	static ConstructorHelpers::FClassFinder<AController> ControllClass(TEXT("Blueprint'/Game/Player/BPCharController.BPCharController_C'"));
	
	// Set default Controller
	if (ControllClass.Succeeded())
	PlayerControllerClass = ControllClass.Class;
}


void AUE4Proj2SeverGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}