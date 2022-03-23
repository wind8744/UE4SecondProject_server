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

	m_Particle->SetupAttachment(m_Body); //메쉬 바디에 붙임
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

	// 애셋을 로딩한다.

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

	m_Particle->DestroyComponent(); //부딪혔을 때 없애기

	// 현재 위치에서 아래로 레이 체크를 한다.
	FCollisionQueryParams	params(NAME_None, false, this);

	FHitResult	LineResult;
	bool Collision = GetWorld()->LineTraceSingleByChannel(LineResult, GetActorLocation(), //액터 위치
		GetActorLocation() + GetActorUpVector() * -300.f, //액터위치의 반대방향으로 3m까지만 처리
		ECollisionChannel::ECC_GameTraceChannel7, //콜리젼은 DefaultEngine.ini가면 RayLandScape찾아서 채널 적어주기
		params);

	if (Collision)
	{
		FActorSpawnParameters	param1;
		param1.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	}
}



