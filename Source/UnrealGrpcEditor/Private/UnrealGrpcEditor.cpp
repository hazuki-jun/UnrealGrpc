#include "UnrealGrpcEditor.h"

#include "UnrealGrpcDialog.h"
#include "UnrealGrpcEditorCommand.h"
#include "UnrealGrpcEditorDelegates.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"

#define LOCTEXT_NAMESPACE "FUnrealGrpcEditorModule"

void FUnrealGrpcEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FUnrealGrpcEditorStyle::Initialize();
	FUnrealGrpcEditorStyle::ReloadTextures();
	FUnrealGrpcEditorCommand::Register();

	// FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	// TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	// MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this));
	// LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);

	FString SavedString;
	const FString FileName = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Intermediate"/ "Config";
	FFileHelper::LoadFileToString(SavedString, *FileName);
	SavedString.Split("|||", &PbPath, &ProtoPath);

	FUnrealGrpcEditorDelegates::OnSettingsApplied.AddLambda([this](const FString& InSavePath, const FString& InSourcePath)
	{
		PbPath = InSavePath;
		ProtoPath = InSourcePath;
	});
	
	BuildMenus();
}

void FUnrealGrpcEditorModule::BuildMenus()
{
	ActionList = MakeShareable(new FUICommandList);

	const auto UnrealGrpcCommand = FUnrealGrpcEditorCommand::Get();
	ActionList->MapAction(UnrealGrpcCommand.UnrealGrpcGenerateAction,FExecuteAction::CreateRaw(this, &FUnrealGrpcEditorModule::OnMenuGenerateClicked));
	ActionList->MapAction(UnrealGrpcCommand.UnrealGrpcSettingsAction,FExecuteAction::CreateRaw(this, &FUnrealGrpcEditorModule::OnMenuSettingsClicked));
	
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
	FToolMenuSection& Section = Menu->AddSection("UnrealGrpc");
	
	FToolMenuEntry Entry = FToolMenuEntry::InitComboButton(
	"UnrealGrpcMenu",
	FUIAction(),
	FOnGetContent::CreateLambda([this] { return MakeMenuWidget();}),
	TAttribute<FText>(),
	TAttribute<FText>(),
	FSlateIcon(FUnrealGrpcEditorStyle::GetStyleSetName(), "UnrealGrpcEditor.Menu"),
	false);
	
	Section.AddEntry(Entry);
}

void FUnrealGrpcEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FUnrealGrpcEditorStyle::Shutdown();
	FUnrealGrpcEditorCommand::Unregister();
}

TSharedRef<SWidget> FUnrealGrpcEditorModule::MakeMenuWidget() const
{
	FMenuBuilder MenuBuilder(true, ActionList);
	
	MenuBuilder.BeginSection(NAME_None, LOCTEXT("UnrealGrpcOptions", "UnrealGrpc Options"));
	{
		MenuBuilder.AddMenuEntry(FUnrealGrpcEditorCommand::Get().UnrealGrpcGenerateAction);
		MenuBuilder.AddMenuEntry(FUnrealGrpcEditorCommand::Get().UnrealGrpcSettingsAction);
	}
	MenuBuilder.EndSection();

	return MenuBuilder.MakeWidget();
}

void FUnrealGrpcEditorModule::OnMenuGenerateClicked()
{
	GenerateAllPBFiles(GetProtocExecPath(), ProtoPath);
}

void FUnrealGrpcEditorModule::OnMenuSettingsClicked()
{
	TSharedRef<SUnrealGrpcDialog> UnrealGrpcDialog = SNew(SUnrealGrpcDialog);
	UnrealGrpcDialog->ShowWindow();
}

void FUnrealGrpcEditorModule::RegenerateAllPBFiles()
{
	DeleteAllPBFiles(ProtoPath);
	GenerateAllPBFiles(GetProtocExecPath(), ProtoPath);
}

void FUnrealGrpcEditorModule::DeleteAllPBFiles(const FString& Path)
{
	if (!FPaths::DirectoryExists(Path))
	{
		return;
	}

	TArray<FString> AllProtoCodeFiles;

	auto SearchSuffixFiles = [=,&AllProtoCodeFiles](const FString& pSuffix)
	{
		IFileManager::Get().FindFilesRecursive(AllProtoCodeFiles, *Path, *pSuffix, true, false, false);
	};

	for (const FString& Suffix : { TEXT("*.pb.cc") ,TEXT("*.pb.h") ,TEXT("*.pb.cpp") })
	{
		SearchSuffixFiles(Suffix);
	}

	for (const auto& File : AllProtoCodeFiles)
	{
		if (FPaths::FileExists(File))
		{
			IFileManager::Get().Delete(*File, true);
		}
	}
}

void FUnrealGrpcEditorModule::GenerateAllPBFiles(const FString &ExecDirectory, const FString& Path)
{
	bool bExistPath = true;
	if (!FPaths::DirectoryExists(PbPath))
	{
		UE_LOG(LogUnrealGrpc, Error, TEXT("********** Save path doesnt exists"))
		bExistPath = false;
	}

	if (!FPaths::DirectoryExists(ProtoPath))
	{
		UE_LOG(LogUnrealGrpc, Error, TEXT("********** Source path doesnt exists"))
		bExistPath = false;
	}

	if (!bExistPath)
	{
		return;
	}
	
	TArray<FString> AllFiles;
	TArray<FString> ProtocCommands;
	TArray<FString> ProtocPluginCommands;
	IFileManager::Get().FindFilesRecursive(AllFiles, *Path, TEXT("*.proto"),true,false,true);
	for (const auto& ProtoFile : AllFiles)
	{
		FString OutDirectory;
		FString FilePath = ProtoFile;
		{
			int32 Pos;
			if (FilePath.FindLastChar('/', Pos))
			{
				FilePath.RemoveAt(Pos, FilePath.Len() - Pos);
			}

			if (FilePath.FindLastChar('/', Pos))
			{
				OutDirectory = FilePath.Right(FilePath.Len() - Pos - 1);
			}
		}

		FString OtherParam = (TEXT("--proto_path=\"") + FilePath + TEXT("\"")) +  (TEXT(" \"") + ProtoFile +TEXT("\"") + TEXT(" "));
		FString OutPath = TEXT("\"") + PbPath / OutDirectory + TEXT("\"");

		if (!FPaths::DirectoryExists(PbPath/OutDirectory))
		{
			IFileManager::Get().MakeDirectory(*FString(PbPath/OutDirectory));
		}
		
		FString OutCPP = OtherParam + TEXT("--cpp_out=") + OutPath;
		ProtocCommands.Add(MoveTemp(OutCPP));

		FString PluginPath = ExecDirectory / "grpc_cpp_plugin.exe";
		FString OutRPC = OtherParam + TEXT("--plugin=protoc-gen-grpc=") + TEXT("\"") + PluginPath + TEXT("\"") + TEXT(" --grpc_out=") + OutPath;
		ProtocPluginCommands.Add(MoveTemp(OutRPC));
	}

	bool bGenerateSuccess = true;

	// Generate pb.* files
	for (const auto& Command : ProtocCommands)
	{
		FProcHandle ProtocProcIns = FPlatformProcess::CreateProc(*(ExecDirectory / "protoc.exe"), *Command, true, false, NULL, NULL, NULL, NULL, NULL);
		if (!ProtocProcIns.IsValid())
		{
			bGenerateSuccess = false;
			break;
		}
	}

	if (bGenerateSuccess)
	{
		// Generate grpc.pb.* files
		for (const auto& ProtocPluginCommand : ProtocPluginCommands)
		{
			FProcHandle ProtocProcIns = FPlatformProcess::CreateProc(*(ExecDirectory / "protoc.exe"), *ProtocPluginCommand, true, false, NULL, NULL, NULL, NULL, NULL);
			if (!ProtocProcIns.IsValid())
			{
				bGenerateSuccess = false;
				break;
			}
		}
	}

	if (!bGenerateSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("*********** Generate Proto files failed ************ "))
	}
}

FString FUnrealGrpcEditorModule::GetProtocExecPath() const
{
	FString RetPath;
	FString PluginPath = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir();
	PluginPath.Append(TEXT(""));
	FString ExecPath = FPaths::Combine(PluginPath, TEXT("Tools"));
	return ExecPath;
}


#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FUnrealGrpcEditorModule, UnrealGrpcEditor)
