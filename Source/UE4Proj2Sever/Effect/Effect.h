// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Effect.generated.h"

UCLASS()
class UE4PROJ2SEVER_API AEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffect();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* m_ParticleSystem;

	FSoftObjectPath		m_AsyncParticlePath;

	TSharedPtr<FStreamableHandle>	m_AsyncParticleLoadHandle;

	bool	m_AssetLoop; //�ѹ� ��� �� ���ٰ��� �ƴҰ���

public:
	void AssetLoop()
	{
		m_AssetLoop = true;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void LoadParticle(const FString& Path); //��ƼŬ ��θ� �о�ͼ� ����
	void LoadParticleAsync(const FString& Name); //�̸����� ã�Ƽ� �ε�
	void LoadParticleAsyncComplete();

public:
	UFUNCTION()
		void ParticleFinish(UParticleSystemComponent* Particle);

};
