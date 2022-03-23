// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAurora.h"
#include "GameAnimInstance.h"
#include "../Effect/Effect.h"

// Sets default values
ACharacterAurora::ACharacterAurora()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh Asset
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AuroraAsset(TEXT("SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));
	if (AuroraAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(AuroraAsset.Object);

	// Anim Asset
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("AnimBlueprint'/Game/Player/Aurora/BPAuroraAnim.BPAuroraAnim_C'"));
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	// Montage Asset (Combo Attack)
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack1Asset(TEXT("AnimMontage'/Game/Player/Aurora/AMAttack1.AMAttack1'"));
	if (Attack1Asset.Succeeded())
		m_AttackMontageArray.Add(Attack1Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack2Asset(TEXT("AnimMontage'/Game/Player/Aurora/AMAttack2.AMAttack2'"));
	if (Attack2Asset.Succeeded())
		m_AttackMontageArray.Add(Attack2Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack3Asset(TEXT("AnimMontage'/Game/Player/Aurora/AMAttack3.AMAttack3'"));
	if (Attack3Asset.Succeeded())
		m_AttackMontageArray.Add(Attack3Asset.Object);
	
	// Montage Asset (Skill)
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill1Asset(TEXT("AnimMontage'/Game/Player/Aurora/AMAuroraSkill1.AMAuroraSkill1'"));
	if (Skill1Asset.Succeeded())
		m_SkillMontageArray.Add(Skill1Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill2Asset(TEXT("AnimMontage'/Game/Player/Aurora/AMAuroraSkill2.AMAuroraSkill2'"));
	if (Skill2Asset.Succeeded())
		m_SkillMontageArray.Add(Skill2Asset.Object);

	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Skill3Asset(TEXT("AnimMontage'/Game/Player/Aurora/AMAuroraSkill3.AMAuroraSkill3'"));
	if (Skill3Asset.Succeeded())
		m_SkillMontageArray.Add(Skill3Asset.Object);

	// Skill Blueprint
	static ConstructorHelpers::FClassFinder<AActor>	SkillClass(TEXT("Blueprint'/Game/Player/Aurora/BPAuroraSKill.BPAuroraSKill_C'"));
	if (SkillClass.Succeeded())
		m_SkillClass = SkillClass.Class;


	m_AttackIdx = 0;

	// Info
	m_CharInfo.Name = TEXT("aurora");
	m_CharInfo.Job = ECharJob::Wizard;
	m_CharInfo.HP = 120;
	m_CharInfo.MP = 20;
	m_CharInfo.AttackDistance = 300.f;
	m_CharInfo.AttackAngle = 30.f;
	m_CharInfo.Level = 1;
	m_CharInfo.Exp = 0.f;
	m_CharInfo.Gold = 100.f;
}

// Called when the game starts or when spawned
void ACharacterAurora::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACharacterAurora::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 마법진 스킬
	// 언더커서를 이용해서 통과하는 것 검사
	// selectplayercontroller에서 언더커서 갖고옴
	// 커서를 꼐속 인지해서 그 커서로 마법진이 생기게 해야하므로
	//if (m_OnSkill2)
	//{
	//	FHitResult	result;
	//	bool Hit = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(
	//		ECollisionChannel::ECC_GameTraceChannel5, //RayLand에 쏠것이므로
	//		false, result);
	//	if (Hit)
	//	{
	//		m_Skill2Decal->SetActorLocation(result.ImpactPoint);
	//	}
	//}
}

// Called to bind functionality to input
void ACharacterAurora::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterAurora::Dash()
{

}

void ACharacterAurora::Attack()
{
	if (!m_AnimInst->Montage_IsPlaying(m_AttackMontageArray[m_AttackIdx]))
	{
		m_AnimInst->Montage_SetPosition(m_AttackMontageArray[m_AttackIdx], 0.f);
		m_AnimInst->Montage_Play(m_AttackMontageArray[m_AttackIdx]);
		m_AnimInst->SetAttackEnable(true);

		m_AttackIdx = (m_AttackIdx + 1) % m_AttackMontageArray.Num();
	}
}

void ACharacterAurora::AttackEnd()
{
	Super::AttackEnd();

	m_iUseSkillIdx = 0;
	m_AttackIdx = 0;
}

void ACharacterAurora::Skill1()
{
	if (!m_AnimInst->Montage_IsPlaying(m_SkillMontageArray[0]))
	{
		m_iUseSkillIdx = 1;
		m_AnimInst->Montage_SetPosition(m_SkillMontageArray[0], 0.f);
		m_AnimInst->Montage_Play(m_SkillMontageArray[0]);
		m_AnimInst->SetAttackEnable(true); // 포즈 블렌딩 쓰기 위함
	}
}

void ACharacterAurora::Skill2()
{
	if (!m_AnimInst->Montage_IsPlaying(m_SkillMontageArray[1]))
	{
		m_iUseSkillIdx = 2;
		m_AnimInst->Montage_SetPosition(m_SkillMontageArray[1], 0.f);
		m_AnimInst->Montage_Play(m_SkillMontageArray[1]);
	}
}

void ACharacterAurora::Skill3()
{
	if (!m_AnimInst->Montage_IsPlaying(m_SkillMontageArray[2]))
	{
		m_iUseSkillIdx = 3;
		m_AnimInst->Montage_SetPosition(m_SkillMontageArray[2], 0.f);
		m_AnimInst->Montage_Play(m_SkillMontageArray[2]);
		m_AnimInst->SetAttackEnable(true);
	}
}
void ACharacterAurora::NormalAttack()
{
	Super::NormalAttack();

	FVector	PlayerLoc = GetActorLocation();
	FVector	Forward = GetActorForwardVector();

	FCollisionQueryParams	params(NAME_None, false, this);

	TArray<FHitResult>	HitResultArray;
	bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, PlayerLoc, PlayerLoc, FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeSphere(200.f), params);

	TArray<FHitResult>	CollisionArray;
	if (Sweep)
	{
		// 1차 구충돌이 일어난 타겟과 나와의 각도를 구해준다.
		//for (int32 i = 0; i < HitResultArray.Num(); ++i)
		for (auto& result : HitResultArray)
		{
			FVector	Dir = result.ImpactPoint - GetActorLocation();

			// 구해준 방향벡터를 단위벡터로 만든다. 그 이유는 원뿔 형태로 체크를 하기 위해서
			// 각도를 체크해줘야 하는데 단위벡터의 내적을 이용하게 된다면 더 벡터간 각도의
			// 코사인 세타 값을 구해줄 수 있다.
			// 그러므로 이러한 코사인 세타를 아크코사인을 이용하여 세타(각도)로 변경하고
			// 이를 비교하여 원뿔 안에 들어오는지를 판단할 수 있다.
			Dir.Normalize();

			Forward = GetActorForwardVector();
			Forward.Normalize();

			float Dot = FVector::DotProduct(Dir, Forward);
			// Acos를 이용해서 각도를 구하면 이 값은 Radian 값으로 들어오게 된다.
			// 그러므로 이를 Degree 로 변환해주고 이를 비교하는 각도로 사용한다.
			float Angle = FMath::Acos(Dot);
			Angle = FMath::RadiansToDegrees(Angle);

			if (Angle <= 30.f)
				CollisionArray.Add(result);

			else
			{
				// 이게 아니라면 직선을 이용해서 상대방 충돌체를 관통하는지 판단한다.
			}
		}
	}
#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = CollisionArray.Num() > 0 ? FColor::Red : FColor::Green;
	DrawDebugCone(GetWorld(), PlayerLoc, GetActorForwardVector(), 200.f,
		FMath::DegreesToRadians(30.f),
		FMath::DegreesToRadians(30.f), 20,
		DrawColor, false, 1.f);

#endif

	for (auto& result : CollisionArray)
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEffect* Effect = GetWorld()->SpawnActor<AEffect>(AEffect::StaticClass(),	result.ImpactPoint, result.ImpactNormal.Rotation(), param);
		Effect->LoadParticleAsync(TEXT("AuroraHit"));

		// 데미지를 전달한다.
		FDamageEvent	DmgEvent;
		float Damage = result.GetActor()->TakeDamage(200.f, DmgEvent, GetController(), this);
	}
}

void ACharacterAurora::UseSkill()
{
	//m_AnimInst->SetAnimType(ECharAnimType::SKILL);

	switch (m_iUseSkillIdx)
	{

	case 1:
	{
		FVector Loc = GetActorLocation();
		Loc.Z += 50.f;
		AAuroraSkill* Skill = GetWorld()->SpawnActor<AAuroraSkill>(m_SkillClass, Loc + GetActorForwardVector() * 100.f, GetActorRotation());
		break;
	}
	case 2:
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEffect* Effect = GetWorld()->SpawnActor<AEffect>(AEffect::StaticClass(),
			GetActorLocation(), GetActorRotation(), param);
		//Effect->LoadParticle(TEXT("ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Ultimate/FX/P_Aurora_Frozen_Ground_Water_Ultimate1.P_Aurora_Frozen_Ground_Water_Ultimate1'"));
		Effect->LoadParticleAsync(TEXT("AuroraSkill2A"));

		AEffect* Effect1 = GetWorld()->SpawnActor<AEffect>(AEffect::StaticClass(),
			GetActorLocation(), GetActorRotation(), param);
		//Effect1->LoadParticle(TEXT("ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Ultimate/FX/P_Aurora_Ultimate_InitialBlast.P_Aurora_Ultimate_InitialBlast'"));
		Effect1->LoadParticleAsync(TEXT("AuroraSkill2B"));
		
		AEffect* Effect2 = GetWorld()->SpawnActor<AEffect>(AEffect::StaticClass(),
			GetActorLocation(), GetActorRotation(), param);
		//Effect2->LoadParticle(TEXT("ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Freeze/FX/P_Aurora_Freeze_Whrilwind.P_Aurora_Freeze_Whrilwind'"));
		Effect2->LoadParticleAsync(TEXT("AuroraSkill2C"));
		
		AuroraSkill2();

		break;
	}
	case 3:
	{

		break;
	}
	default:
		break;
	}

}


void ACharacterAurora::AuroraSkill2()
{
	// 충돌체
	FHitResult result2;
	FVector	PlayerLoc = GetActorLocation();
	FVector	Forward = GetActorForwardVector();
	FVector AttackBox;
	AttackBox.X = 300.f;
	AttackBox.Y = 300.f;
	AttackBox.Z = 100.f;

	FCollisionQueryParams	params(NAME_None, false, this); 

	// 부딪힌 obj array
	TArray<FHitResult>	HitResultArray; 

	bool Sweep = GetWorld()->SweepMultiByChannel(HitResultArray, PlayerLoc, //멀티는 여러마리, 싱글은 한마리 ,두번째 인자는 충돌 시작점	
		PlayerLoc, FQuat::Identity, // 공격 거리, 회전 정보
		ECollisionChannel::ECC_GameTraceChannel6, FCollisionShape::MakeBox(AttackBox), params);

#if ENABLE_DRAW_DEBUG
	PrintViewport(1.f, FColor::Yellow, TEXT("AuroraSkill2"));
	FColor	DrawColor = HitResultArray.Num() > 0 ? FColor::Red : FColor::Green;
	DrawDebugBox(GetWorld(), PlayerLoc, AttackBox, DrawColor, false, 1.f);
#endif

	for (auto& result : HitResultArray)
	{
		FActorSpawnParameters	param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AEffect* Effect = GetWorld()->SpawnActor<AEffect>(AEffect::StaticClass(), result.ImpactPoint, result.ImpactNormal.Rotation(), param); 
		//Effect->LoadParticle(TEXT("ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Freeze/FX/P_Aurora_Freeze_Rooted.P_Aurora_Freeze_Rooted'"));
		Effect->LoadParticleAsync(TEXT("AuroraHit"));

		// 데미지를 전달한다.
		FDamageEvent	DmgEvent;
		float Damage = result.GetActor()->TakeDamage(m_CharInfo.AttackDistance, DmgEvent, GetController(), this);
	}

}