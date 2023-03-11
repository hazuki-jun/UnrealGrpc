#pragma once
#include "UnrealGrpcEditorStyle.h"

class FUnrealGrpcEditorCommand : public TCommands<FUnrealGrpcEditorCommand> 
{
public:
	FUnrealGrpcEditorCommand()
	: TCommands<FUnrealGrpcEditorCommand>(TEXT("UnrealGrpcEditor"), NSLOCTEXT("Contexts", "UnrealGrpcEditor", "UnrealGrpcEditor Plugin"), NAME_None, FUnrealGrpcEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

	// TSharedPtr<FUICommandInfo> UnrealGrpcMenuAction;
	
	TSharedPtr<FUICommandInfo> UnrealGrpcGenerateAction;
	
	TSharedPtr<FUICommandInfo> UnrealGrpcSettingsAction;
	
};
