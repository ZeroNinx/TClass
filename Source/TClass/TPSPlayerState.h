// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TPSPlayerState.generated.h"

//��ҷ����ṹ��
USTRUCT(BlueprintType)
struct FPlayerScore
{
	GENERATED_BODY()

	//�������
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name="";

	//��ҵ÷�
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Score=0;

	//��һ�ɱ
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int Kill=0;

	//�������
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int Died=0;
};


/**
 * ���״̬
 */
UCLASS()
class TCLASS_API ATPSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	ATPSPlayerState();
	
	//�趨����
	UFUNCTION(BlueprintCallable)
	void SetName(FString NewName);

	//�趨����
	UFUNCTION(BlueprintCallable)
	void SetScore(int NewScore);

	//�趨��ɱ
	UFUNCTION(BlueprintCallable)
	void SetKill(int NewKill);

	//�趨����
	UFUNCTION(BlueprintCallable)
	void SetDied(int NewDied);

	//��ȡ��Ϣ
	UFUNCTION(BlueprintCallable)
	FPlayerScore GetPlayerInfo();

protected:

	//��ҵ÷�
	UPROPERTY(BlueprintReadWrite)
	FPlayerScore PlayerScore;

	//�������ֵ
	UPROPERTY(BlueprintReadWrite)
	int Life = 100;

};
