// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGrpcManager.h"

UUnrealGrpcManager& UUnrealGrpcManager::Get(UObject* Context)
{
	check(Context);

	check(Context->GetWorld());

	check(Context->GetWorld()->GetGameInstance());

	return *UGameInstance::GetSubsystem<UUnrealGrpcManager>(Context->GetWorld()->GetGameInstance());
}

