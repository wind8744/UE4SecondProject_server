// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

UCLASS()
class UE4PROJ2SEVER_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* m_Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	USpringArmComponent* m_SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"));
	FCharInfo		m_CharInfo;

	bool			m_bIsDead;
	bool			m_bMoveKey;
	float			m_fSideValue;
	float			m_fFrontValue;

	float			m_fArmLengthTo = 0.0f;
	FRotator		m_rArmRotationTo = FRotator::ZeroRotator;
	float			m_fArmLengthSpeed = 0.0f;
	float			m_fArmRotationSpeed = 0.0f;
	FVector			m_vDirectionToMove = FVector::ZeroVector;


private:
	void ViewInit();

public:
	void CameraUpKey(float AxisValue);
	void CameraZoomKey(float AxisValue);
	
	void JumpKey();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
