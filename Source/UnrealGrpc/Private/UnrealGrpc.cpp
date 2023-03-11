// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealGrpc.h"

#define LOCTEXT_NAMESPACE "FUnrealGrpcModule"

void FUnrealGrpcModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FUnrealGrpcModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUnrealGrpcModule, UnrealGrpc)