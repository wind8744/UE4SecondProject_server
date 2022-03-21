// Copyright Epic Games, Inc. All Rights Reserved.


#include "UE4Proj2SeverGameModeBase.h"
#include "UI/ChatUI.h"
#include "Network/NetworkManager.h"
#include "Network/RecvQueue.h"
#include "Network/PacketStream.h"

AUE4Proj2SeverGameModeBase::AUE4Proj2SeverGameModeBase()
{
	// Use Tick ( actor기 때문에 gamemodebase에서도 틱 사용 가능 )
	PrimaryActorTick.bCanEverTick = true;

	// Set main UI
	static ConstructorHelpers::FClassFinder<UMainUI> MainUIClass(TEXT("WidgetBlueprint'/Game/UI/MainUI.MainUI_C'"));
	if (MainUIClass.Succeeded())
		m_MainUIClass = MainUIClass.Class;

	// Set default pawn
	static ConstructorHelpers::FClassFinder<APawn> PawnClass(TEXT("Blueprint'/Game/Player/Muriel/BPMuriel.BPMuriel_C'"));
	if (PawnClass.Succeeded())
		DefaultPawnClass = PawnClass.Class;
	
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

	// 큐에 처리할 메세지 있을 때만 메세지를 챗창으로 전달
	RecvQueue* Que = NetworkManager::GetInst()->GetQueue();

	while (!Que->Empty()) // 큐 size 초기화 꼭.. 할것
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

				PrintViewport(1.f, FColor::Red, Mgs);

				break;
			}

			default:
				break;
			}
		}
	}

}
