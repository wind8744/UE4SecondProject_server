// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraSkill.h"
#include "Effect.h"


// Sets default values
AAuroraSkill::AAuroraSkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	m_Trail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));

	m_Particle->SetupAttachment(m_Body); //�޽� �ٵ� ����
	m_Trail->SetupAttachment(m_Body);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>	Asset(TEXT("ParticleSystem'/Game/AdvancedMagicFX13/Particles/P_ky_cutter3.P_ky_cutter3'"));

	if (Asset.Succeeded())
		m_Particle->SetTemplate(Asset.Object);
}

// Called when the game starts or when spawned
void AAuroraSkill::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAuroraSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_DestroyEnable)
		m_Mesh->AddRelativeRotation(FRotator(0.f, 1080.f * DeltaTime, 0.f));
}

void AAuroraSkill::StopEvent(const FHitResult& result)
{
	Super::StopEvent(result);

	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// �ּ��� �ε��Ѵ�.

	// effect 1
	AEffect* Effect = GetWorld()->SpawnActor<AEffect>(AEffect::StaticClass(),
		result.ImpactPoint, result.ImpactNormal.Rotation(), param);
	Effect->LoadParticleAsync(TEXT("AuroraSkill1A"));
	//Effect->LoadParticle(TEXT("ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Ultimate/FX/P_Aurora_Ultimate_Explode_Cheap.P_Aurora_Ultimate_Explode_Cheap'"));

	// effect 2
	AEffect* Effect1 = GetWorld()->SpawnActor<AEffect>(AEffect::StaticClass(),
		result.ImpactPoint, result.ImpactNormal.Rotation(), param);
	Effect1->LoadParticleAsync(TEXT("AuroraSkill1B"));
	//Effect1->LoadParticle(TEXT("ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Freeze/FX/P_Aurora_Freeze_Segment.P_Aurora_Freeze_Segment'"));

	m_Particle->DestroyComponent(); //�ε����� �� ���ֱ�

	// ���� ��ġ���� �Ʒ��� ���� üũ�� �Ѵ�.
	FCollisionQueryParams	params(NAME_None, false, this);

	FHitResult	LineResult;
	bool Collision = GetWorld()->LineTraceSingleByChannel(LineResult, GetActorLocation(), //���� ��ġ
		GetActorLocation() + GetActorUpVector() * -300.f, //������ġ�� �ݴ�������� 3m������ ó��
		ECollisionChannel::ECC_GameTraceChannel7, //�ݸ����� DefaultEngine.ini���� RayLandScapeã�Ƽ� ä�� �����ֱ�
		params);

	if (Collision)
	{
		FActorSpawnParameters	param1;
		param1.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	}
}



