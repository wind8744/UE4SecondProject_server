// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimapUI.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UMinimapUI::NativeConstruct()
{
	Super::NativeConstruct();

	m_PlayerPoint = Cast<UImage>(GetWidgetFromName(TEXT("PlayerArrow")));
	CreateMonsterArray();
}

void UMinimapUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UMinimapUI::CreateMonsterArray()
{
	m_AddCnt = 0;
	
	// 오브젝트 풀링 , 미리 20개 만들어놓음..
	// 단점은 안쓰는건 메모리 아깝, 적당히 만들어 놓을것.
	UCanvasPanel* Panel = WidgetTree->FindWidget<UCanvasPanel>(TEXT("MonsterParent"));
	for (int32 i = 0; i < 20; ++i)
	{
		// 위젯 생성
		FString Name = FString::Printf(TEXT("Monster%d"), i); 
		UImage* Img = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *Name);
		Img->SetVisibility(ESlateVisibility::Collapsed);
		m_MonsterArray.Add(Img);

		if (Panel)
		{
			UCanvasPanelSlot* PanelSlot = Panel->AddChildToCanvas(Img);
			PanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			PanelSlot->SetSize(FVector2D(10.f, 10.f));
		}
	}
}


void UMinimapUI::RotPoint(float Z)
{
	// 플레이어의 회전과 위치에 따라 포인트 이미지를 바꾸깅
	// RemderTramsform의 Angle
	m_PlayerPoint->SetRenderTransformAngle(Z);
}


void UMinimapUI::ClearMonster()
{
	for (int i = 0; i < m_AddCnt; ++i)
	{
		m_MonsterArray[i]->SetVisibility(ESlateVisibility::Collapsed);
	}

	m_AddCnt = 0;
}

void UMinimapUI::AddMonster(const FVector& MonPos)
{
	if (m_AddCnt == m_MonsterArray.Num())
	{
		// 위젯트리에서 몬스터 캔버스 패널 root 받아와서
		UCanvasPanel* Panel = WidgetTree->FindWidget<UCanvasPanel>(TEXT("MonsterParent"));
		
		FString	Name = FString::Printf(TEXT("Monster%d"), m_AddCnt);
		
		// 몬스터 이미지 UI 추가
		UImage* Image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *Name);

		Image->SetVisibility(ESlateVisibility::Collapsed);

		m_MonsterArray.Add(Image);

		if (Panel)
		{
			// 자식으로 넣어줌
			UCanvasPanelSlot* PanelSlot = Panel->AddChildToCanvas(Image);

			PanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			PanelSlot->SetSize(FVector2D(10.f, 10.f));
		}
	}

	//PrintViewport(1.f, FColor::Red, Pos.ToString());
	m_MonsterArray[m_AddCnt]->SetVisibility(ESlateVisibility::Visible);

	FVector2D	ImagePos;

	ImagePos.X = MonPos.Y;
	ImagePos.Y = MonPos.X * -1.f;
	ImagePos *= 0.1f;

	ImagePos.X += 200.f;
	ImagePos.Y += 150.f;

	PrintViewport(1.f, FColor::Red, ImagePos.ToString());

	UImage* Image = m_MonsterArray[m_AddCnt];
	++m_AddCnt;

	UCanvasPanelSlot* PanelSlot = Cast<UCanvasPanelSlot>(Image->Slot);

	PanelSlot->SetPosition(ImagePos);
}