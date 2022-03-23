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
	
	// OnSystemFinished : �� ��ƼŬ�ý���������Ʈ�� ������ �ִ� ��ƼŬ�ý����� ����� ��� ���ᰡ �Ǿ��� ��� ȣ��� �Լ��� �����صд�.
	// ����� ������ �Լ��� ȣ��ȴ�.
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

	//���ڸ� �־��ش�.... ȣ��� �Լ��� �������ش�.(��������Ʈó��) ��������Ʈ�� ���� ����
	m_AsyncParticleLoadHandle = streamMgr.RequestAsyncLoad(m_AsyncParticlePath,
		FStreamableDelegate::CreateUObject(this, &AEffect::LoadParticleAsyncComplete));
}

void AEffect::LoadParticleAsyncComplete()
{
	//�ε��� ������ �� �ڵ��� ������ ���� �Ʊ� �޾Ƴ����� (m_AsyncParticleLoadHandle)
	m_AsyncParticleLoadHandle->ReleaseHandle();

	//��θ� �־��� �ε��ص� ��ƼŬ�� ���� �� �ְ� ����
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