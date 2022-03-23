// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "../UE4Proj2SeverGameModeBase.h"
#include "../UI/MinimapUI.h"

AGameCharController::AGameCharController()
{
	//APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	//FInputModeGameAndUI	Mode;
	//SetInputMode(Mode);
	bShowMouseCursor = true;
}

void AGameCharController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (m_bRClicked)
	{
		MoveToMouseCursor();
	}
}

void AGameCharController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("RClick"), EInputEvent::IE_Pressed, this, &AGameCharController::PressedRClick);
	InputComponent->BindAction(TEXT("RClick"), EInputEvent::IE_Released, this, &AGameCharController::ReleasedRClick);

	//InputComponent->BindAction(TEXT("LClick"), EInputEvent::IE_Pressed, this, &AGameCharController::PressedLClick);
	//InputComponent->BindAction(TEXT("LClick"), EInputEvent::IE_Released, this, &AGameCharController::ReleasedLClick);
}

void AGameCharController::MoveToMouseCursor()
{
	FHitResult Hit;
	
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		SetNewDestination(Hit.ImpactPoint);
	}
}

void AGameCharController::SetNewDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		if (Distance > 120.0f)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
	
			AUE4Proj2SeverGameModeBase* GameMode = Cast<AUE4Proj2SeverGameModeBase>(GetWorld()->GetAuthGameMode());
			if (GameMode)
			{
				FRotator Rot = MyPawn->GetActorRotation();
				GameMode->GetMainUI()->GetMinimapWidget()->RotPoint(Rot.Yaw);
			}
			
		}
	}
}

void AGameCharController::PressedRClick()
{
	m_bRClicked = true;
}

void AGameCharController::ReleasedRClick()
{
	m_bRClicked = false;
}

void AGameCharController::PressedLClick()
{
	m_bLClicked = true;
}

void AGameCharController::ReleasedLClick()
{
	m_bLClicked = false;
}
