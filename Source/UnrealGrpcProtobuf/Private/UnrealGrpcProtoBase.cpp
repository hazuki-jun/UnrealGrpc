// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGrpcProtoBase.h"

#include "UnrealGrpcPool.h"

std::shared_ptr<grpc::Channel> UUnrealGrpcProtoBase::GetChannel()
{
	auto& UnrealGrpcPool = UUnrealGrpcPool::Get(GetOuter());
	auto Channel = UnrealGrpcPool.GetChannel(EndPoint);
	return Channel;
}
