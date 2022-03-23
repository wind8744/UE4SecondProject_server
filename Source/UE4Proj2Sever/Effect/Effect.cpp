// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect.h"
#include "../AssetMgr/AssetPathMain.h"

// Sets default values
AEffect::AEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

	SetRootComponent(m_ParticleSystem);

	m_AssetLoop = false;
}

// Called when the game starts or when spawned
void AEffect::BeginPlay()
{
	Super::BeginPlay();
	
	// OnSystemFinished : 이 파티클시스템컴포넌트가 가지고 있는 파티클시스템이 재생이 모두 종료가 되었을 경우 호출될 함수를 지정해둔다.
	// 종료시 지정된 함수가 호출된다.
	if (!m_AssetLoop)
		m_ParticleSystem->OnSystemFinished.AddDynamic(this, &AEffect::ParticleFinish);
}

// Called every frame
void AEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffect::LoadParticle(const FString& Path)
{
	UParticleSystem* Particle = LoadObject<UParticleSystem>(GetWorld(), *Path);

	if (Particle)
		m_ParticleSystem->SetTemplate(Particle);
}
void AEffect::LoadParticleAsync(const FString& Name)
{
	UAssetPathMain* AssetPath = UAssetPathMain::StaticClass()->GetDefaultObject<UAssetPathMain>();

	const FSoftObjectPath* Path = AssetPath->FindParticlePath(Name);

	if (!Path)
		return;

	m_AsyncParticlePath = *Path;

	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();

	//인자를 넣어준다.... 호출될 함수를 지정해준다.(델리게이트처럼) 델리게이트름 만들어서 지정
	m_AsyncParticleLoadHandle = streamMgr.RequestAsyncLoad(m_AsyncParticlePath,
		FStreamableDelegate::CreateUObject(this, &AEffect::LoadParticleAsyncComplete));
}

void AEffect::LoadParticleAsyncComplete()
{
	//로딩이 끝났을 대 핸들을 릴리즈 해줌 아까 받아놨던것 (m_AsyncParticleLoadHandle)
	m_AsyncParticleLoadHandle->ReleaseHandle();

	//경로를 넣어줌 로딩해둔 파티클을 얻어올 수 있게 해줌
	TAssetPtr<UParticleSystem>	NewParticle(m_AsyncParticlePath); 

	if (NewParticle)
	{
		m_ParticleSystem->SetTemplate(NewParticle.Get());
	}
}

void AEffect::ParticleFinish(UParticleSystemComponent* Particle)
{
	Destroy();
}