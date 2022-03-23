// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleProj.h"

// Sets default values
ADestructibleProj::ADestructibleProj()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Body = CreateDefaultSubobject<UBoxComponent>(TEXT("Body"));
	m_Mesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Mesh"));
	m_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	SetRootComponent(m_Body);
	m_Mesh->SetupAttachment(m_Body);

	m_Movement->SetUpdatedComponent(m_Body);
	m_Movement->InitialSpeed = 1000.f;

	m_DestroyEnable = false;
	m_DestroyTime = 0.f;
	m_DestroyTimeMax = 5.f;

	m_Distance = 2000.f;
	m_Mesh->SetReceivesDecals(false);
}

// Called when the game starts or when spawned
void ADestructibleProj::BeginPlay()
{
	Super::BeginPlay();

	m_Movement->OnProjectileStop.AddDynamic(this, &ADestructibleProj::ProjectileStop);
}

// Called every frame
void ADestructibleProj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_Distance -= m_Movement->Velocity.Size() * DeltaTime;

	if (m_Distance <= 0.f)
		Destroy();

	if (m_DestroyEnable)
	{
		m_DestroyTime += DeltaTime;
		if (m_DestroyTimeMax <= m_DestroyTime)
		{
			Destroy();
		}
	}
}

void ADestructibleProj::ProjectileStop(const FHitResult& result)
{
	StopEvent(result);
}

void ADestructibleProj::StopEvent(const FHitResult& result)
{
	//PrintViewport(1.f, FColor::Blue, TEXT("projectile stop"));
	// ¸Þ½¬ »Ñ½Ã±â
	m_Mesh->ApplyDamage(10.f, result.ImpactPoint, result.ImpactNormal, 10.f);
	m_DestroyEnable = true;
}
