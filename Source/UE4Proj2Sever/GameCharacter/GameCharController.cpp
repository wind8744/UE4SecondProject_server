// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


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

	InputComponent->BindAction(TEXT("LClick"), EInputEvent::IE_Pressed, this, &AGameCharController::PressedLClick);
	InputComponent->BindAction(TEXT("LClick"), EInputEvent::IE_Released, this, &AGameCharController::ReleasedLClick);
}

void AGameCharController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		//SetControlRotation(Hit.ImpactPoint.ToOrientationRotator());
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
			SetControlRotation(DestLocation.ToOrientationRotator());
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
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
