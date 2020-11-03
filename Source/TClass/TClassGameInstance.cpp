// Fill out your copyright notice in the Description page of Project Settings.


#include "TClassGameInstance.h"

UTClassGameInstance::UTClassGameInstance():Super::UGameInstance()
{
	//获取联网子系统接口
	OnlineSub = IOnlineSubsystem::Get();

	//绑定回调函数
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::
		CreateUObject(this, &UTClassGameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::
		CreateUObject(this, &UTClassGameInstance::OnStartSessionComplete);
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::
		CreateUObject(this, &UTClassGameInstance::OnFindSessionComplete);
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::
		CreateUObject(this, &UTClassGameInstance::OnJoinSessionComplete);
	OnDestroySessionCompleteDelegate = FOnDestroySessionCompleteDelegate::
		CreateUObject(this, &UTClassGameInstance::OnDestroySessionComplete);
	
}

//初始化
void UTClassGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Creating GameInstant..."));
	
}

//特殊关闭时
void UTClassGameInstance::Shutdown()
{
	UE_LOG(LogTemp, Warning, TEXT("Shutting Down GameInstant..."));
	DestroySession();
}

//显示载入界面
void UTClassGameInstance::ShowLoadingScreen_Implementation()
{
	//判断界面是否存在
	if (!IsValid(LoadingUMG))
	{
		//导入载入界面
		TSubclassOf<UUMG_Loading> LoadingUMGClass = LoadClass<UUMG_Loading>(this, TEXT("/Game/Widgets/BP_UMG_Loading.BP_UMG_Loading_C"));
		if (LoadingUMGClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("UMG_Loading Found..."));
			LoadingUMG = CreateWidget<UUMG_Loading>(GetWorld(), LoadingUMGClass);
		}
	}
	LoadingUMG->AddToViewport();

}

//注册控制器
void UTClassGameInstance::AssignPlayerController_Implementation(APlayerController* InController)
{
	//获取联网子系统接口
	OnlineSub = IOnlineSubsystem::Get();

	//获取玩家控制器
	PlayerController = GetPrimaryPlayerController();
	UserID = GetPrimaryPlayerUniqueId().ToSharedRef();

	if (PlayerController)
		UE_LOG(LogTemp, Warning, TEXT("Controller Assigned Success"));

}

//创建游戏
void UTClassGameInstance::HostSession_Implementation()
{
	if (OnlineSub)
	{
		//获取会话接口
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//会话设置
			FOnlineSessionSettings Settings;

			//连接数
			Settings.NumPublicConnections = 10;
			Settings.bShouldAdvertise = true;
			Settings.bAllowJoinInProgress = true;

			//使用局域网
			Settings.bIsLANMatch = true;
			Settings.bUsesPresence = true;
			Settings.bAllowJoinViaPresence = true;
		

			//绑定委托
			OnCreateSessionCompleteDelegateHandle = Session
				->AddOnCreateSessionCompleteDelegate_Handle
				(OnCreateSessionCompleteDelegate);
			//创建会话
			Session->CreateSession(*UserID, NAME_GameSession, Settings);
		}
	}
}

//加入游戏
void UTClassGameInstance::ClientSession_Implementation()
{
	if (OnlineSub)
	{
		//获取会话接口
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//实例化搜索结果指针并且设定参数
			SearchObject = MakeShareable(new FOnlineSessionSearch);

			//返回结果数
			SearchObject->MaxSearchResults = 10;

			//是否是局域网，就是IsLAN
			SearchObject->bIsLanQuery = true;
			SearchObject->QuerySettings.Set(SEARCH_PRESENCE, true,EOnlineComparisonOp::Equals);
			
			//绑定寻找会话委托
			OnFindSessionsCompleteDelegateHandle = Session->
				AddOnFindSessionsCompleteDelegate_Handle
				(OnFindSessionsCompleteDelegate);
			//进行会话寻找
			Session->FindSessions(*UserID, SearchObject.ToSharedRef());
		}
	}
}

//摧毁会话
void UTClassGameInstance::DestroySession_Implementation()
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//注销销毁会话委托
			Session->ClearOnDestroySessionCompleteDelegate_Handle
			(OnDestroySessionCompleteDelegateHandle);
			//其它逻辑。。。
			Session->DestroySession(NAME_GameSession);
		}
	}
}

//创建会话完成
void UTClassGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{

	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//解绑创建会话完成回调函数
			Session->
				ClearOnCreateSessionCompleteDelegate_Handle
				(OnCreateSessionCompleteDelegateHandle);
			//判断创建会话是否成功
			if (bWasSuccessful)
			{
				UE_LOG(LogTemp, Warning, TEXT("Create Session Succeed"));

				//绑定开启会话委托
				OnStartSessionCompleteDelegateHandle = Session->
					AddOnStartSessionCompleteDelegate_Handle
					(OnStartSessionCompleteDelegate);
				Session->StartSession(NAME_GameSession);
			}
			else UE_LOG(LogTemp, Warning, TEXT("Create Session Failed"));
		}
	}
}

//会话开始
void UTClassGameInstance::OnStartSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Session Started"));
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//注销开启会话委托绑定
			Session->ClearOnStartSessionCompleteDelegate_Handle
			(OnStartSessionCompleteDelegateHandle);
			if (bWasSuccessful)
			{
				UE_LOG(LogTemp, Warning, TEXT("Start Session Succeed"));

				//服务端跳转场景
				UGameplayStatics::OpenLevel(PlayerController->GetWorld(),
					FName("Map_TPS"), true, FString("listen"));
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("Start Session Failed"));
		}
	}
}

//查找会话完成
void UTClassGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
	if (Session.IsValid())
	{
		//取消寻找会话委托绑定
		Session->ClearOnStartSessionCompleteDelegate_Handle
		(OnStartSessionCompleteDelegateHandle);

		//如果寻找会话成功
		if (bWasSuccessful)
		{
			//如果收集的结果存在且大于0
			if (SearchObject.IsValid() && SearchObject->SearchResults.Num() > 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Find Session Succeed"));
				//绑定加入Session委托
				OnJoinSessionCompleteDelegateHandle = Session
					->AddOnJoinSessionCompleteDelegate_Handle
					(OnJoinSessionCompleteDelegate);
				//执行加入会话
				Session->JoinSession(*UserID, NAME_GameSession, SearchObject->SearchResults[0]);
			}
			else
				UE_LOG(LogTemp, Warning, TEXT("Session Num <=0 "));
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Find Session Failed"));
	}
}

//加入会话完成
void UTClassGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//取消加入对话委托绑定
			Session->ClearOnJoinSessionCompleteDelegate_Handle
			(OnJoinSessionCompleteDelegateHandle);
			//如果加入成功
			if (Result == EOnJoinSessionCompleteResult::Success)
			{
				//传送玩家到新地图
				FString ConnectString;
				if (Session->GetResolvedConnectString(NAME_GameSession, ConnectString))
				{
					UE_LOG(LogTemp, Warning, TEXT("Join Session Succeed"));
					
					//设置输入模式仅游戏
					UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);

					//客户端切换到服务器的关卡
					PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
				}
				else
					UE_LOG(LogTemp, Warning, TEXT("Join Session Failed"));
			}
		}
	}
}

//会话销毁完成
void UTClassGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (OnlineSub)
	{
		IOnlineSessionPtr Session = OnlineSub->GetSessionInterface();
		if (Session.IsValid())
		{
			//绑定销毁会话委托
			OnDestroySessionCompleteDelegateHandle = Session->
				AddOnDestroySessionCompleteDelegate_Handle
				(OnDestroySessionCompleteDelegate);
			//执行销毁会话
			Session->DestroySession(NAME_GameSession);
		}
	}
}
