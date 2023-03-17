// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <grpcpp/channel.h>
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UnrealGrpcProtoBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UNREALGRPCPROTOBUF_API UUnrealGrpcProtoBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void NewStub() {};

	virtual void OnCreated() {}
	
	virtual void SetEndPoint(const FString& InEndPoint) { EndPoint = InEndPoint; }

	virtual std::shared_ptr<grpc::Channel> GetChannel(); 
	
protected:
	FString EndPoint;
};
