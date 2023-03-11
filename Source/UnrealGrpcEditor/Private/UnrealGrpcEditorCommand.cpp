#include "UnrealGrpcEditorCommand.h"

#define LOCTEXT_NAMESPACE "FUnrealGrpcEditorModule"

void FUnrealGrpcEditorCommand::RegisterCommands()
{
	// UI_COMMAND(UnrealGrpcMenuAction, "UnrealGrpc", "Expand menu", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(UnrealGrpcGenerateAction, "Generate", "Generate pb files", EUserInterfaceActionType::Button, FInputChord());

	UI_COMMAND(UnrealGrpcSettingsAction, "Settings", "Opens the settings for UnrealGrpc", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE