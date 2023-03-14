// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UnrealGrpcManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGRPC_API UUnrealGrpcManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UUnrealGrpcManager& Get(UObject* Context);

	template<class T>
	T* Create(const FString& Channel);

public:
	UPROPERTY()
	TArray<UObject*> CachedProto;
};

template <class T>
T* UUnrealGrpcManager::Create(const FString& Channel)
{
	T* NewProto = NewObject<T>(GetOuter());
	if (NewProto)
	{
		NewProto->SetEndPoint(Channel);
		CachedProto.Emplace(NewProto);
		return NewProto;
	}

	return nullptr;
}