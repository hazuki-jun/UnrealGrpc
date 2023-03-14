#include "UnrealGrpcEditor.h"

#include "UnrealGrpcDialog.h"
#include "UnrealGrpcEditorCommand.h"
#include "UnrealGrpcEditorDelegates.h"
#include "Async/Async.h"
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
	
	TArray<FString> ProtoFiles;
	TArray<FString> GeneratedFilesName;
	TArray<FString> GeneratedPaths;
	TArray<FString> ProtocCommands;
	TArray<FString> ProtocPluginCommands;
	IFileManager::Get().FindFilesRecursive(ProtoFiles, *Path, TEXT("*.proto"),true,false,true);
	for (const auto& ProtoFile : ProtoFiles)
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

		FString ProtoFileName = ProtoFile;
		{
			int32 Pos;
			if (ProtoFileName.FindLastChar('/', Pos))
			{
				ProtoFileName.RemoveAt(0, Pos + 1);
				ProtoFileName.RemoveFromEnd(".proto");
			}
		} 
		
		FString OtherParam = (TEXT("--proto_path=\"") + FilePath + TEXT("\"")) +  (TEXT(" \"") + ProtoFile +TEXT("\"") + TEXT(" "));
		FString OutPath = TEXT("\"") + PbPath / OutDirectory + TEXT("\"");

		if (FPaths::FileExists(PbPath / OutDirectory / ProtoFileName + ".pb.h"))
		{
			continue;
		}
		
		GeneratedPaths.Emplace(PbPath / OutDirectory);
		if (!FPaths::DirectoryExists(PbPath/OutDirectory))
		{
			IFileManager::Get().MakeDirectory(*FString(PbPath/OutDirectory));
		}
		
		FString OutCPP = ExecDirectory / "protoc.exe " + OtherParam + TEXT("--cpp_out=") + OutPath;
		ProtocCommands.Add(MoveTemp(OutCPP));

		FString PluginPath = ExecDirectory / "grpc_cpp_plugin.exe";
		FString OutRPC = ExecDirectory / "protoc.exe " + OtherParam + TEXT("--plugin=protoc-gen-grpc=") + TEXT("\"") + PluginPath + TEXT("\"") + TEXT(" --grpc_out=") + OutPath;
		ProtocPluginCommands.Add(MoveTemp(OutRPC));
	}

	if (ProtocCommands.IsEmpty() || ProtocPluginCommands.IsEmpty())
	{
		return;
	}
	
	// GeneratePBFiles(ProtocCommands);
	// GenerateGrpcPBFiles(ProtocPluginCommands);

	// Pause console if need
	// ProtocCommands.Add("pause");
	FString PBBat = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Intermediate/generate_pb.bat";
	FFileHelper::SaveStringArrayToFile(ProtocCommands, *PBBat);

	// Pause console if need
	// ProtocPluginCommands.Add("pause");
	FString GrpcBat = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Intermediate/generate_grpc_pb.bat";
	FFileHelper::SaveStringArrayToFile(ProtocPluginCommands, *GrpcBat);

	AsyncTask(ENamedThreads::AnyThread, [this, PBBat, GrpcBat]()
	{
		auto HandleIDPB = FPlatformProcess::CreateProc(*PBBat, NULL, false, false, false, nullptr, 0, nullptr, nullptr);
		auto HandleIDGrpc = FPlatformProcess::CreateProc(*GrpcBat, NULL, false, false, false, nullptr, 0, nullptr, nullptr);
		while (FPlatformProcess::IsProcRunning(HandleIDGrpc) || FPlatformProcess::IsProcRunning(HandleIDPB))
		{
			FPlatformProcess::Sleep(0.2f);
		}
			
		FixProtoWarning(PbPath, TEXT("*.pb.cc"));
	});
	
	GenerateUnrealGrpcProtoFiles(GeneratedPaths, ProtoFiles);
}

void FUnrealGrpcEditorModule::GeneratePBFiles(TArray<FString>& Command)
{
	// Pause console if need
	// Command.Add("pause");
	
	// Generate pb.* files
	UE_LOG(LogUnrealGrpc, Warning, TEXT("**************** Generating pb.* files ****************"))
	FString PBBat = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Intermediate/generate_pb.bat";
	FFileHelper::SaveStringArrayToFile(Command, *PBBat);
	
	// CreateProcess(NULL, BatFile.GetCharArray().GetData(), nullptr, nullptr, false, (::DWORD)CREATE_NEW_CONSOLE, NULL, NULL, &StartupInfoEx.StartupInfo, &ProcInfo);
	FPlatformProcess::CreateProc(*PBBat, NULL, false, false, false, nullptr, 0, nullptr, nullptr);
}

void FUnrealGrpcEditorModule::GenerateGrpcPBFiles(TArray<FString>& Command)
{
	// Pause console if need
	// Command.Add("pause");
	
	// Generate grp.pb.* files
	UE_LOG(LogUnrealGrpc, Warning, TEXT("**************** Generating grpc.pb.* files ****************"))
	FString GrpcBat = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Intermediate/generate_grpc_pb.bat";
	FFileHelper::SaveStringArrayToFile(Command, *GrpcBat);
	
	AsyncTask(ENamedThreads::AnyThread, [this, GrpcBat]()
	{
		auto HandleID = FPlatformProcess::CreateProc(*GrpcBat, NULL, false, false, false, nullptr, 0, nullptr, nullptr);
		while (FPlatformProcess::IsProcRunning(HandleID))
		{
			FPlatformProcess::Sleep(0.2f);
		}
		
		FixProtoWarning(PbPath, TEXT("*grpc.pb.cc"));
	});
}

void FUnrealGrpcEditorModule::GenerateUnrealGrpcProtoFiles(const TArray<FString>& Paths, const TArray<FString>& ProtoFiles)
{
	const FString TemplateHeader = GetTemplateHeaderContent();
	const FString TemplateSource = GetTemplateSourceContent();

	if (TemplateHeader.IsEmpty() || TemplateSource.IsEmpty())
	{
		return;
	}
	
	for (int i = 0; i < ProtoFiles.Num(); ++i)
	{
		FString ProtoContent; 
		FFileHelper::LoadFileToString(ProtoContent, *ProtoFiles[i]);

		TArray<FString> Lines;
        int32 LineCount = ProtoContent.ParseIntoArray(Lines, TEXT("\n"), true);
		FString PackageName;
		FString ServiceName;

		// package name
		for (const auto& Line : Lines)
		{
			if (Line.StartsWith("package "))
			{
				PackageName = Line.Mid(8, Line.Len() - 8);
				PackageName.RemoveFromEnd(";");
				break;
			}
		}

		// service name
		for (const auto& Line : Lines)
		{
			if (Line.StartsWith("service "))
			{
				ServiceName = Line.Mid(8, Line.Len() - 8);
				ServiceName.RemoveFromEnd(" {");
				break;
			}
		}
		
		FString ModuleName = "UNREALGRPCPROTOBUF";
		FString ClassName = "UUnrealGrpcProto" + PackageName;
		FString FileToSave = TemplateHeader;
		FileToSave = FileToSave.Replace(TEXT("#PackageName#"), *PackageName);
		FileToSave = FileToSave.Replace(TEXT("#ServiceName#"), *ServiceName);
		FileToSave = FileToSave.Replace(TEXT("#ModuleName#"), *ModuleName);
		FileToSave = FileToSave.Replace(TEXT("#ClassName#"), *ClassName);

		// Save header
		FString FileName = Paths[i] / "UnrealGrpcProto" + PackageName;
		FFileHelper::SaveStringToFile(FileToSave, *(FileName + ".h"));

		FileToSave = TemplateSource;
		FileToSave = FileToSave.Replace(TEXT("#ClassName#"), *ClassName);
		FileToSave = FileToSave.Replace(TEXT("#PackageName#"), *PackageName);

		// Save source
		FFileHelper::SaveStringToFile(FileToSave, *(FileName + ".cpp"));
	}
}

void FUnrealGrpcEditorModule::FixProtoWarning(const FString& InPath, const FString& Suffix)
{
	FString WarningToDisable = "#pragma warning(push)\n\n#pragma warning (disable : 4125)\n\n";
	FString EndWarningToDisable = "#pragma warning(pop)\n\n";
	
	TArray<FString> CCFiles;
	IFileManager::Get().FindFilesRecursive(CCFiles, *InPath, *Suffix,true,false,true);

	for (const auto& CCFile : CCFiles)
	{
		FString FileContent;
		FFileHelper::LoadFileToString(FileContent, *CCFile);
		FileContent = WarningToDisable + FileContent + "\n\n" + EndWarningToDisable;
		FFileHelper::SaveStringToFile(FileContent, *CCFile);
	}
}

FString FUnrealGrpcEditorModule::GetTemplateHeaderContent()
{
	FString FileName =  IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Resources" / "TemplateToGenerate.h.txt";

	FString Result;
    FFileHelper::LoadFileToString(Result, *FileName);

    return Result;
}

FString FUnrealGrpcEditorModule::GetTemplateSourceContent()
{
	FString FileName = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Resources" / "TemplateToGenerate.cpp.txt";

	FString Result;
	FFileHelper::LoadFileToString(Result, *FileName);

	return Result;
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
