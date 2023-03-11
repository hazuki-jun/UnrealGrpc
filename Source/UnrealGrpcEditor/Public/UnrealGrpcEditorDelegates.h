#pragma once

#include "CoreMinimal.h"

class FUnrealGrpcEditorDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSettingsApplied, const FString&, const FString&);

	static FOnSettingsApplied OnSettingsApplied;
};
