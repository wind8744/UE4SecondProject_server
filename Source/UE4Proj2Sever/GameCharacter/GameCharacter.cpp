// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCharacter.h"
#include "GameAnimInstance.h"
#include "../UE4Proj2SeverGameModeBase.h"
#include "../Network/NetworkManager.h"
#include "../Network/NetworkSession.h"
#include "../Network/PacketStream.h"
#include "../UI/MinimapUI.h"

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
	m_bAttackable = true;
	m_iUseSkillIdx = 0;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_AnimInst = Cast<UGameAnimInstance>(GetMesh()->GetAnimInstance());

	// �����Ŀ� �Ҹ���? = 0.5f, ��� �ݺ�? = true, �����Ŀ� ����? = �ٷ�(�⺻��)
	GetWorldTimerManager().SetTimer(m_MonDetectTimer, this, &AGameCharacter::MonsterDetect, 0.5f, true);
	
	// ������ ���� ĳ������ ��ġ �Ѱ���
	NetworkSession* Session = NetworkManager::GetInst()->GetSession();
	
	PacketStream Stream;
	uint8 Packet[PACKET_SIZE] = {};
	
	FVector charLoc = GetActorLocation();
	FRotator charRot = GetActorRotation();
	FVector charScale = GetActorScale();
	int32 job = (int32)m_CharInfo.Job;

	Stream.SetBuffer(Packet);

	Stream.Write(&job,sizeof(int32));
	Stream.Write(&charLoc, sizeof(FVector));
	Stream.Write(&charScale, sizeof(FVector));
	Stream.Write(&charRot, sizeof(FRotator));
	//Stream.Write(&m_CharInfo.Name, 12);
	
	Session->Write((int)NetworkProtocol::UserConnect, Stream.GetLength(), Packet);

}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bIsDead)
		return;

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
	PlayerInputComponent->BindAction(TEXT("LClick"), EInputEvent::IE_Pressed, this, &AGameCharacter::AttackKey);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AGameCharacter::JumpKey);
	PlayerInputComponent->BindAction(TEXT("Dash"), EInputEvent::IE_Pressed, this, &AGameCharacter::DashKey);

	PlayerInputComponent->BindAction(TEXT("Skill1"), EInputEvent::IE_Pressed, this, &AGameCharacter::Skill1Key);
	PlayerInputComponent->BindAction(TEXT("Skill2"), EInputEvent::IE_Pressed, this, &AGameCharacter::Skill2Key);
	PlayerInputComponent->BindAction(TEXT("Skill3"), EInputEvent::IE_Pressed, this, &AGameCharacter::Skill3Key);
}

void AGameCharacter::AttackKey()
{
	if (m_bAttackable)
	{
		m_bAttackable = false;
		Attack();
	}
}
void AGameCharacter::Skill1Key()
{
	Skill1(); 
}
void AGameCharacter::Skill2Key()
{
	Skill2();
}
void AGameCharacter::Skill3Key()
{
	Skill3();
}
void AGameCharacter::DashKey()
{
	if (m_bAttackable)
	{
		Dash();
	}
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

	//m_SpringArm->AddLocalRotation()
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

void AGameCharacter::MonsterDetect()
{
	// �÷��̾� Ž�� �ڽ� ���� ���� �����ؼ� �̴ϸ� ǥ��
	TArray<FHitResult> resultArray;
	
	FVector MyPos = GetActorLocation();
	FVector StartPos = MyPos - FVector(1500.f, 2000.f, 1000.f);
	FVector EndPos = StartPos + FVector(3000.f, 4000.f, 2000.f);

	FCollisionQueryParams param(NAME_None, false, this);

	bool Col = GetWorld()->SweepMultiByChannel(resultArray,StartPos,EndPos,FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel11, FCollisionShape::MakeBox(FVector(1500.f,2000.f,1000.f)), param);

	AUE4Proj2SeverGameModeBase* gamemode = Cast<AUE4Proj2SeverGameModeBase>(GetWorld()->GetAuthGameMode());
	UMinimapUI* minimap = nullptr;
	if (gamemode)
	{
		minimap = gamemode->GetMainUI()->GetMinimapWidget();
		minimap->ClearMonster();
	}

	if (Col)
	{
		for (auto& result : resultArray)
		{
			// ���� ���Ͱ��� �Ÿ�
			FVector RelativePos = result.GetActor()->GetActorLocation() - MyPos;
			//RelativePos *= 0.1f; //
			if (nullptr != minimap)
			{
				minimap->AddMonster(RelativePos);
			}
		}
	}

}

void AGameCharacter::UseSkill() {}
void AGameCharacter::NormalAttack() {}
void AGameCharacter::AttackEnd() { m_bAttackable = true; }

// virtual
void AGameCharacter::Dash() {} 
void AGameCharacter::Attack() {} 
void AGameCharacter::Skill1() {}
void AGameCharacter::Skill2() {}
void AGameCharacter::Skill3() {}