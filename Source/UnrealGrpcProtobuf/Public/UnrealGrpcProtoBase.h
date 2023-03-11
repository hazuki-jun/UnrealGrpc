// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	virtual void NewStub(const FString& InChannel) {};
};
