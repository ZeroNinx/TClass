// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "UMG_Loading.h"
#include "Net/UnrealNetwork.h"
#include "Online.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TClassGameInstance.generated.h"

/**
 * 游戏实例类
 */
UCLASS()
class TCLASS_API UTClassGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

    //构造函数
    UTClassGameInstance();

	//生成时
	virtual void Init() override;
    
    //关闭时
    virtual void Shutdown() override;

    //注册控制器
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void AssignPlayerController(APlayerController* InController);

	//显示载入界面
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowLoadingScreen();

    //创建游戏
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void HostSession();

	//加入游戏
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ClientSession();

    //摧毁会话
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void DestroySession();

protected:	
    
    //载入界面
    UUMG_Loading* LoadingUMG;

protected:

    //玩家控制器
    APlayerController* PlayerController;

    //用户ID
    TSharedPtr<const FUniqueNetId> UserID;

    //联网子系统
    IOnlineSubsystem* OnlineSub;

    //开启服务器委托
    FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
    FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

    //开启服务器委托句柄
    FDelegateHandle OnCreateSessionCompleteDelegateHandle;
    FDelegateHandle OnStartSessionCompleteDelegateHandle;

    //加入服务器委托
    FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
    FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

    //加入服务器委托句柄
    FDelegateHandle OnFindSessionsCompleteDelegateHandle;
    FDelegateHandle OnJoinSessionCompleteDelegateHandle;

    //销毁会话委托与句柄
    FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
    FDelegateHandle OnDestroySessionCompleteDelegateHandle;

    //搜索结果指针
    TSharedPtr<FOnlineSessionSearch> SearchObject;

protected:

    //当创建会话结束后，回调函数
    void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

    //当开始会话结束后，回调函数
    void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);

    //寻找服务器后，回调函数
    void OnFindSessionComplete(bool bWasSuccessful);
   
    //加入服务器后，回调函数
    void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

    //销毁会话后,回调函数
    void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

};
