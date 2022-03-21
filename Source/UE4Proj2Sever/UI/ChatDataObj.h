// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "UObject/NoExportTypes.h"
#include "ChatDataObj.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UE4PROJ2SEVER_API UChatDataObj : public UObject
{
	GENERATED_BODY()
	
public:
	UChatDataObj();

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_Message;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool  m_Flag = false;

public:
	void SetMessage(const FString& Msg) { m_Message = Msg; }
	void SetFlag(bool Flag) { m_Flag = Flag; }

};
