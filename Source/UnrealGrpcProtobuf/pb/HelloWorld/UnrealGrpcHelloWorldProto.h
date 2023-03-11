// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma warning(push)
#pragma warning (disable : 4005)
#pragma warning (disable : 4125)
#pragma warning (disable : 4582)
#pragma warning (disable : 4583)
#pragma warning (disable : 4647)
#pragma warning (disable : 4668)
#pragma warning (disable : 4800)
#pragma warning (disable : 4946)

#include "CoreMinimal.h"
#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"
#include "UnrealGrpcProtoBase.h"
#include "UnrealGrpcHelloWorldProto.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGRPCPROTOBUF_API UUnrealGrpcHelloWorldProto : public UUnrealGrpcProtoBase
{
	GENERATED_BODY()
	
public:
	UUnrealGrpcHelloWorldProto(const FObjectInitializer& ObjectInitializer);
	
	virtual void NewStub(const FString& InChannel) override final;
	
public:
	virtual void SayHello();
	
private:
	std::unique_ptr<helloworld::Greeter::Stub> stub_;
};

#pragma warning(pop)
