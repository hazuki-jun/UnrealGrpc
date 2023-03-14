#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FUnrealGrpcEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

	void BuildMenus();
	
	TSharedRef<SWidget> MakeMenuWidget() const;
	
    /**
     * @brief On Generate button pressed
     */
    void OnMenuGenerateClicked();

	/**
	 * @brief On Settings button pressed
	 */
	void OnMenuSettingsClicked();
	
    void RegenerateAllPBFiles();

    /**
     * @brief Delete all generated pb files
     * @param Path 
     */
    void DeleteAllPBFiles(const FString& Path);

    /**
     * @brief Generate pb and grpc.pb files 
     * @param ExecDirectory 
     * @param Path 
     */
    void GenerateAllPBFiles(const FString &ExecDirectory, const FString &Path);

    /**
     * @brief Generate pb files
     * @param Command 
     */
    void GeneratePBFiles(TArray<FString>& Command);

    /**
     * @brief Generate grpc.pb files
     * @param Command 
     */
    void GenerateGrpcPBFiles(TArray<FString>& Command);

	
    /**
     * @brief GenerateUnrealGrpcProtoFiles
     * @param Paths 
     * @param ProtoFiles 
     */
    void GenerateUnrealGrpcProtoFiles(const TArray<FString>& Paths, const TArray<FString>& ProtoFiles);

    /**
     * @brief Disable warning
     * @param InPath 
     */
    void FixProtoWarning(const FString& InPath, const FString& Suffix);
	
    /**
     * @brief The template header string
     * @return 
     */
    FString GetTemplateHeaderContent();

	
    /**
     * @brief The template source string
     * @return 
     */
    FString GetTemplateSourceContent();

    /**
     * @brief grpc_cpp_plugin.exe and protoc.exe path
     * @return 
     */
    FString GetProtocExecPath() const;
    
private:
    TSharedPtr<class FUICommandList> ActionList;

	FString ProtoPath;
	FString PbPath;
};


