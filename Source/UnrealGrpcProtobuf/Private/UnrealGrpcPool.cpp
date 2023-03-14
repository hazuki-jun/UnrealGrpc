// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGrpcPool.h"

#include <grpcpp/create_channel.h>

UUnrealGrpcPool& UUnrealGrpcPool::Get(UObject* Context)
{
	check(Context);

	check(Context->GetWorld());

	check(Context->GetWorld()->GetGameInstance());

	return *UGameInstance::GetSubsystem<UUnrealGrpcPool>(Context->GetWorld()->GetGameInstance());
}

std::shared_ptr<grpc::Channel> UUnrealGrpcPool::NewChannel(const FString& EndPoint)
{
	std::string end_point = TCHAR_TO_UTF8(*EndPoint);
	std::shared_ptr<grpc::Channel> ret;
	if (channel_pools.find(end_point) != channel_pools.end())
	{
		ret = grpc::CreateChannel(end_point, grpc::InsecureChannelCredentials());
		channel_pools.emplace(end_point, ret);
	}
	
	return ret;
}

std::shared_ptr<grpc::Channel> UUnrealGrpcPool::GetChannel(const FString& EndPoint)
{
	std::shared_ptr<grpc::Channel> ret;
	std::string end_point = TCHAR_TO_UTF8(*EndPoint);
	
	auto channel_iter = channel_pools.find(end_point);
	if (channel_iter != channel_pools.end())
	{
		ret = channel_iter->second;
	}
	
	return ret;
}
