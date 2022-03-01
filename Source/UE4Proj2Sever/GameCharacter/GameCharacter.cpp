// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	// Arm 부모Component -> Mesh
	m_SpringArm->SetupAttachment(RootComponent);//GetMesh());

	// Camera 부모Component -> Arm
	m_Camera->SetupAttachment(m_SpringArm);

	ViewInit();

	m_bIsDead = false;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bIsDead)
		return;

	//m_SpringArm->TargetArmLength = FMath::FInterpTo(m_SpringArm->TargetArmLength,
	//	ArmLengthTo, DeltaTime, ArmLengthSpeed);

	//회전값 방향 보간
	//m_SpringArm->SetRelativeRotation(FMath::RInterpTo(m_SpringArm->GetRelativeRotation(),
	//	m_rArmRotationTo, DeltaTime, m_fArmRotationSpeed));

	//if (m_vDirectionToMove.SizeSquared() > 0.f)
	//{
	//	//방향 벡터를 회전값으로 하여 캐릭터 회전
	//	GetController()->SetControlRotation(m_vDirectionToMove.ToOrientationRotator());
	//	//벡터값 방향으로 이동
	//	AddMovementInput(m_vDirectionToMove);
	//}
}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Axis
	PlayerInputComponent->BindAxis(TEXT("CameraUp"), this, &AGameCharacter::CameraUpKey);
	PlayerInputComponent->BindAxis(TEXT("CameraZoom"), this, &AGameCharacter::CameraZoomKey);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AGameCharacter::AddControllerYawInput);

	//Action
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AGameCharacter::JumpKey);

}

void AGameCharacter::CameraUpKey(float AxisValue)
{ 
	FRotator Rot = m_SpringArm->GetRelativeRotation();
	Rot.Pitch += AxisValue * 100.f * GetWorld()->GetDeltaSeconds();

	if (Rot.Pitch > 90.f)
		Rot.Pitch = 90.f;

	else if (Rot.Pitch < -45.f)
		Rot.Pitch = -45.f;

	m_SpringArm->SetRelativeRotation(Rot);
}

void AGameCharacter::CameraZoomKey(float AxisValue)
{
	m_SpringArm->TargetArmLength -= AxisValue * 50.f;
	
	if (m_SpringArm->TargetArmLength < 300.f)
		m_SpringArm->TargetArmLength = 300.f;
	
	else if (m_SpringArm->TargetArmLength > 1700.f)
		m_SpringArm->TargetArmLength = 1700.f;

}

void AGameCharacter::JumpKey()
{
	Jump();
}


void AGameCharacter::ViewInit()
{
	m_fArmLengthTo = 800.0f;
	m_rArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);

	//ArmLengthSpeed = 3.f;
	m_fArmRotationSpeed = 5.f;

	m_SpringArm->TargetArmLength = 1300.f;
	m_SpringArm->bUsePawnControlRotation = false;
	m_SpringArm->bInheritPitch = false;
	m_SpringArm->bInheritRoll = false;
	m_SpringArm->bInheritYaw = false;
	m_SpringArm->bDoCollisionTest = false;

	//컨트롤 회전이 가리키는 방향으로 캐릭터가 부드럽게 회전 , 캐릭터의 회전 보완
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	//회전 부드럽게 보완을 위한 해제
	//bUseControllerRotationYaw = false; 
	//GetCharacterMovement()->bOrientRotationToMovement = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationYaw = false;
}