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

	bool	m_AssetLoop; //한번 사용 후 없앨건지 아닐건지

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
	void LoadParticle(const FString& Path); //파티클 경로를 읽어와서 지정
	void LoadParticleAsync(const FString& Name); //이름으로 찾아서 로드
	void LoadParticleAsyncComplete();

public:
	UFUNCTION()
		void ParticleFinish(UParticleSystemComponent* Particle);

};
