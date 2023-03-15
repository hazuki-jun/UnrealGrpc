// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGrpcPool.h"

#include <grpcpp/create_channel.h>

FUnrealGrpcCreateChannelRunnable::FUnrealGrpcCreateChannelRunnable()
{
	Thread = nullptr;
	ThreadState = EUnrealGrpcCreateChannelThreadState::Idle;
}

FUnrealGrpcCreateChannelRunnable::~FUnrealGrpcCreateChannelRunnable()
{
	if (Thread)
	{
		Thread->WaitForCompletion();
		Thread->Kill(false);
	}
}

uint32 FUnrealGrpcCreateChannelRunnable::Run()
{
	if (!Master.IsValid())
	{
		Stop();
		return 0;
	}

	while (ThreadState != EUnrealGrpcCreateChannelThreadState::PendingKill)
	{
		if (ThreadState == EUnrealGrpcCreateChannelThreadState::Idle)
		{
			FPlatformProcess::Sleep(0.2f);
		}
		
		std::string end_point = TCHAR_TO_UTF8(*EndPoint);
		std::shared_ptr<grpc::Channel> ret = grpc::CreateChannel(end_point, grpc::InsecureChannelCredentials());

		FScopeLock ChannelPools(&Master->ChannelsPoolCS);
		Master->channels_pool.emplace(end_point, ret);
		Master->OnChannelCreated(EndPoint);
		ThreadState = EUnrealGrpcCreateChannelThreadState::Idle;
	}

	return 0;
}

void FUnrealGrpcCreateChannelRunnable::StartThread()
{
	if (!Thread)
	{
		Thread = FRunnableThread::Create(this, TEXT("UnrealGrpcCreateChannelRunnable"), 0, TPri_Normal, FPlatformAffinity::GetPoolThreadMask());
	}

	ThreadState = EUnrealGrpcCreateChannelThreadState::Running;
}

bool FUnrealGrpcCreateChannelRunnable::IsIdling()
{
	return ThreadState == EUnrealGrpcCreateChannelThreadState::Idle;
}

UUnrealGrpcPool& UUnrealGrpcPool::Get(UObject* Context)
{
	check(Context);

	check(Context->GetWorld());

	check(Context->GetWorld()->GetGameInstance());

	return *UGameInstance::GetSubsystem<UUnrealGrpcPool>(Context->GetWorld()->GetGameInstance());
}

void UUnrealGrpcPool::NewChannel(const FString& EndPoint)
{
	std::string end_point = TCHAR_TO_UTF8(*EndPoint);
	if (channels_pool.find(end_point) != channels_pool.end())
	{
		// channel already exist
		return;
	}

	InternalNewChannel(EndPoint);
}

void UUnrealGrpcPool::InternalNewChannel(const FString& EndPoint)
{
	for (const auto& ChannelThread : CreateChannelThreadPool)
	{
		if (ChannelThread->IsIdling())
		{
			ChannelThread->EndPoint = EndPoint;
			ChannelThread->StartThread();
			return;
		}
	}

	auto ChannelRunnable = MakeUnique<FUnrealGrpcCreateChannelRunnable>();
	ChannelRunnable->Master = this;
	CreateChannelThreadPool.Emplace(MoveTemp(ChannelRunnable));
	InternalNewChannel(EndPoint);
}

std::shared_ptr<grpc::Channel> UUnrealGrpcPool::GetChannel(const FString& EndPoint)
{
	std::shared_ptr<grpc::Channel> ret;
	std::string end_point = TCHAR_TO_UTF8(*EndPoint);
	
	auto channel_iter = channels_pool.find(end_point);
	if (channel_iter != channels_pool.end())
	{
		ret = channel_iter->second;
	}
	
	return ret;
}

void UUnrealGrpcPool::OnChannelCreated(const FString& EndPoint)
{
	FScopeLock SC_ChannelCreatedDelegate(&ChannelCreatedDelegateCS);
	OnChannelCreatedDelegate.Broadcast(EndPoint);
}
