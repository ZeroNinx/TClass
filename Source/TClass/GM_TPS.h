// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_TPS.generated.h"

//��Ϸ���
UENUM(BlueprintType)
enum class GameResult :uint8
{
	Equal = 0,
	P1Win = 1,
	P2Win = 2
};


/**
 * ��Ϸģʽ
 */
UCLASS()
class TCLASS_API AGM_TPS : public AGameModeBase
{
	GENERATED_BODY()

	
};
