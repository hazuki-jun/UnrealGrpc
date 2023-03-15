// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma warning(push)
#pragma warning (disable : 4005) // 'TEXT': macro redefinition
#pragma warning (disable : 4456) // declaration of 'size' hides previous local declaration
#pragma warning (disable : 4125) // decimal digit terminates..
#pragma warning (disable : 4582) // constructor is not implicitly called
#pragma warning (disable : 4583) // destructor is not implicitly called
#pragma warning (disable : 4647) // behavior change __is_pod...
#pragma warning (disable : 4668) // 'symbol' is not defined as a preprocessor macro...
#pragma warning (disable : 4800) // Implicit conversion from 'type' to bool. Possible information loss
#pragma warning (disable : 4946) // reinterpret_cast used between related classes

#include "CoreMinimal.h"
#include <grpcpp/grpcpp.h>
#include "PlayerInformation.grpc.pb.h"
#include "UnrealGrpcProtoBase.h"
#include "UnrealGrpcProtoPlayerInformation.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGRPCPROTOBUF_API UUnrealGrpcProtoPlayerInformation : public UUnrealGrpcProtoBase
{
	GENERATED_BODY()
	
public:
	UUnrealGrpcProtoPlayerInformation(const FObjectInitializer& ObjectInitializer);
	
	virtual void NewStub() override final;
	
private:
	std::unique_ptr<PlayerInformation::Greeter::Stub> stub_;
};

#pragma warning(pop)
