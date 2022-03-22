// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE4Proj2SeverGameModeBase.h"
#include "UI/ChatUI.h"
#include "Network/NetworkManager.h"
#include "Network/RecvQueue.h"
#include "Network/PacketStream.h"
#include "User/MyUserCharacter.h"

AUE4Proj2SeverGameModeBase::AUE4Proj2SeverGameModeBase()
{
	// Use Tick ( actor�� ������ gamemodebase������ ƽ ��� ���� )
	PrimaryActorTick.bCanEverTick = true;

	// Set main UI
	static ConstructorHelpers::FClassFinder<UMainUI> MainUIClass(TEXT("WidgetBlueprint'/Game/UI/MainUI.MainUI_C'"));
	if (MainUIClass.Succeeded())
		m_MainUIClass = MainUIClass.Class;

	// Set default pawn
	static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("Blueprint'/Game/Player/Kwang/BPKwang.BPKwang_C'"));
	if (PawnClass.Succeeded())
		DefaultPawnClass = PawnClass.Class;

	// Set default pawn
	//static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("Blueprint'/Game/Player/Aurora/BPAurora.BPAurora_C'"));
	//if (PawnClass.Succeeded())
	//	DefaultPawnClass = PawnClass.Class;


	// Set default Controller
	static ConstructorHelpers::FClassFinder<AController> ControllClass(TEXT("Blueprint'/Game/Player/BPCharController.BPCharController_C'"));
	if (ControllClass.Succeeded())
	PlayerControllerClass = ControllClass.Class;

}


void AUE4Proj2SeverGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(m_MainUIClass))
	{
		m_MainWidget = Cast<UMainUI>(CreateWidget(GetWorld(), m_MainUIClass));

		if (m_MainWidget)
			m_MainWidget->AddToViewport();
	}

}

void AUE4Proj2SeverGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ť�� ó���� �޼��� ���� ���� �޼����� êâ���� ����
	RecvQueue* Que = NetworkManager::GetInst()->GetQueue();

	while (!Que->Empty()) // ť size �ʱ�ȭ ��.. �Ұ�
	{
		int32 Protocol = -1;
		int32 Length = 0;
		uint8 Packet[PACKET_SIZE] = {};

		if (Que->Pop(Protocol, Length, Packet))
		{
			switch ((NetworkProtocol)Protocol)
			{
			case NetworkProtocol ::Chat:
			{
				TCHAR Mgs[1024] = {};
				FMemory::Memcpy(Mgs, Packet, Length);
				m_MainWidget->GetChatWidget()->AddMessage(Mgs);

				//PrintViewport(1.f, FColor::Red, Mgs);

				break;
			}
			case NetworkProtocol::UserConnect:
			{
				// ���⿡ ������ �ٸ� ������ �����ߴٴ� �� -> ���� ����
				PacketStream	stream;
				stream.SetBuffer(Packet);

				ECharJob	Job;
				stream.Read(&Job, 4);

				FVector	Pos, Scale;
				FRotator	Rot;

				stream.Read(&Pos, 12);
				stream.Read(&Scale, 12);
				stream.Read(&Rot, 12);

				AUserCharacter* User = nullptr;

				switch (Job)
				{
				case ECharJob::Knight:
				{
					FActorSpawnParameters	param;
					param.SpawnCollisionHandlingOverride =
						ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
					User = GetWorld()->SpawnActor<AMyUserCharacter>(
						AMyUserCharacter::StaticClass(), Pos + FVector(0.f, -200.f, 0.f), Rot,
						param);
					User->SetActorScale3D(Scale);

					PrintViewport(1.f, FColor::Red, TEXT("Knight"));
				}
				break;
				case ECharJob::Archer:
				{
					FActorSpawnParameters	param;
					param.SpawnCollisionHandlingOverride =
						ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
					User = GetWorld()->SpawnActor<AMyUserCharacter>(
						AMyUserCharacter::StaticClass(), Pos + FVector(0.f, -200.f, 0.f), Rot,
						param);
					User->SetActorScale3D(Scale);

					PrintViewport(1.f, FColor::Red, TEXT("Archer"));
				}
					break;
				case ECharJob::Wizard:
				{
					FActorSpawnParameters	param;
					param.SpawnCollisionHandlingOverride =
						ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
					User = GetWorld()->SpawnActor<AMyUserCharacter>(
						AMyUserCharacter::StaticClass(), Pos + FVector(0.f, -200.f, 0.f), Rot,
						param);
					User->SetActorScale3D(Scale);

					PrintViewport(1.f, FColor::Red, TEXT("Wizard"));
				}
					break;
				}
				break;
			}
			}
		}
	}

}
