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
	T* CreateProto(const FString& Channel);

// 	void RemoveProto(UObject* ProtoObjectToRemove);
// 	
// public:
// 	UPROPERTY()
// 	TArray<UObject*> CachedProto;
};

template <class T>
T* UUnrealGrpcManager::CreateProto(const FString& Channel)
{
	T* NewProto = NewObject<T>(GetOuter());
	if (NewProto)
	{
		NewProto->SetEndPoint(Channel);
		NewProto->OnCreated();
		// CachedProto.AddUnique(NewProto);
		return NewProto;
	}

	return nullptr;
}