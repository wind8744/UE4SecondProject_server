// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE4Proj2SeverGameModeBase.h"

AUE4Proj2SeverGameModeBase::AUE4Proj2SeverGameModeBase()
{
	// Set main UI
	static ConstructorHelpers::FClassFinder<UMainUI> MainUIClass(TEXT("WidgetBlueprint'/Game/UI/MainUI.MainUI_C'"));
	if (MainUIClass.Succeeded())
		m_MainUIClass = MainUIClass.Class;

	// Set default pawn
	static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("Blueprint'/Game/Player/Muriel/BPMuriel.BPMuriel_C'"));
	if (PawnClass.Succeeded())
		DefaultPawnClass = PawnClass.Class;
	
	// Set default Controller
	static ConstructorHelpers::FClassFinder<AController> ControllClass(TEXT("Blueprint'/Game/Player/BPCharController.BPCharController_C'"));
	if (ControllClass.Succeeded())
	PlayerControllerClass = ControllClass.Class;
}


void AUE4Proj2SeverGameModeBase::BeginPlay()
{
	Super::BeginPlay();


	if (IsValid(m_MainUIClass))
	{
		m_MainWidget = Cast<UMainUI>(CreateWidget(GetWorld(), m_MainUIClass));

		if (m_MainWidget)
			m_MainWidget->AddToViewport();
	}

}

