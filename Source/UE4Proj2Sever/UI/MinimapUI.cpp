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
	
	// ������Ʈ Ǯ�� , �̸� 20�� ��������..
	// ������ �Ⱦ��°� �޸� �Ʊ�, ������ ����� ������.
	UCanvasPanel* Panel = WidgetTree->FindWidget<UCanvasPanel>(TEXT("MonsterParent"));
	for (int32 i = 0; i < 20; ++i)
	{
		// ���� ����
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
	// �÷��̾��� ȸ���� ��ġ�� ���� ����Ʈ �̹����� �ٲٱ�
	// RemderTramsform�� Angle
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
		// ����Ʈ������ ���� ĵ���� �г� root �޾ƿͼ�
		UCanvasPanel* Panel = WidgetTree->FindWidget<UCanvasPanel>(TEXT("MonsterParent"));
		
		FString	Name = FString::Printf(TEXT("Monster%d"), m_AddCnt);
		
		// ���� �̹��� UI �߰�
		UImage* Image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(), *Name);

		Image->SetVisibility(ESlateVisibility::Collapsed);

		m_MonsterArray.Add(Image);

		if (Panel)
		{
			// �ڽ����� �־���
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