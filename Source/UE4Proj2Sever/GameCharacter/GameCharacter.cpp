// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	// Arm �θ�Component -> Mesh
	m_SpringArm->SetupAttachment(RootComponent);//GetMesh());

	// Camera �θ�Component -> Arm
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

	//ȸ���� ���� ����
	//m_SpringArm->SetRelativeRotation(FMath::RInterpTo(m_SpringArm->GetRelativeRotation(),
	//	m_rArmRotationTo, DeltaTime, m_fArmRotationSpeed));

	//if (m_vDirectionToMove.SizeSquared() > 0.f)
	//{
	//	//���� ���͸� ȸ�������� �Ͽ� ĳ���� ȸ��
	//	GetController()->SetControlRotation(m_vDirectionToMove.ToOrientationRotator());
	//	//���Ͱ� �������� �̵�
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
	m_SpringArm->TargetArmLength -= AxisValue * 20.f;
	
	if (m_SpringArm->TargetArmLength < 700.f)
		m_SpringArm->TargetArmLength = 700.f;
	
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

	//��Ʈ�� ȸ���� ����Ű�� �������� ĳ���Ͱ� �ε巴�� ȸ�� , ĳ������ ȸ�� ����
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	//ȸ�� �ε巴�� ������ ���� ����
	//bUseControllerRotationYaw = false; 
	//GetCharacterMovement()->bOrientRotationToMovement = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationYaw = false;
}