// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInfo.h"

DEFINE_LOG_CATEGORY(UE4Proj2Server);

//�ð�, ����, text�� �޾Ƽ� �����Ϳ� ���
void PrintViewport(float Time, const FColor& Color, const FString& Text)
{
	//gegine�̶�� ���������� ���� ���� �� �Լ��� ���ؼ� �����Ϳ� ���
	//-1�� �ƹ����Գ� ���
	GEngine->AddOnScreenDebugMessage(-1, Time, Color, Text);
}