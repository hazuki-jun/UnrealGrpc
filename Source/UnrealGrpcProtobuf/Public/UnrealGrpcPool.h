// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>
#include <grpcpp/channel.h>
#include "HAL/Runnable.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UnrealGrpcPool.generated.h"

enum class EUnrealGrpcCreateChannelThreadState : uint8
{
	Idle,
	Running,
	PendingKill
};

class FUnrealGrpcCreateChannelRunnable : public FRunnable
{
public:
	FUnrealGrpcCreateChannelRunnable();
	virtual ~FUnrealGrpcCreateChannelRunnable() override;

	
	//~ Begin FRunnable Interface
	virtual void Stop() override;
	virtual uint32 Run() override;
	//~ End FRunnable Interface
	
	void StartThread();

	bool IsIdling();
	
	FString EndPoint;

	TWeakObjectPtr<class UUnrealGrpcPool> Master;
	
	FRunnableThread* Thread;

	mutable TAtomic<EUnrealGrpcCreateChannelThreadState> ThreadState;
};

/**
 * 
 */
UCLASS()
class UNREALGRPCPROTOBUF_API UUnrealGrpcPool : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	friend class FUnrealGrpcCreateChannelRunnable;
	
public:
	virtual void Deinitialize() override;
	
	static UUnrealGrpcPool& Get(UObject* Context);
	
	void NewChannel(const FString& EndPoint);

	std::shared_ptr<grpc::Channel> GetChannel(const FString& EndPoint);
	
	std::map<std::string, std::shared_ptr<grpc::Channel>> channels_pool;

	void OnChannelCreated(std::shared_ptr<grpc::Channel>& InChannel, const FString& EndPoint);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnUnrealGrpcChannelCreated, FString)
	FOnUnrealGrpcChannelCreated OnChannelCreatedDelegate; 
	
protected:
	mutable FCriticalSection ChannelsPoolCS;
	mutable FCriticalSection ChannelCreatedDelegateCS;

	TArray<TUniquePtr<FUnrealGrpcCreateChannelRunnable>> CreateChannelThreadPool;

private:
	void InternalNewChannel(const FString& EndPoint);
};




