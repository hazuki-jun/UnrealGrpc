// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <map>
#include <grpcpp/channel.h>

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UnrealGrpcPool.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGRPCPROTOBUF_API UUnrealGrpcPool : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UUnrealGrpcPool& Get(UObject* Context);
	
	std::shared_ptr<grpc::Channel> NewChannel(const FString& EndPoint);

	std::shared_ptr<grpc::Channel> GetChannel(const FString& EndPoint);
	
	std::map<std::string, std::shared_ptr<grpc::Channel>> channel_pools;
};
