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
	 * @brief Select a exist proto to create pb
	 */
	void OnMenuNewProtoClicked();
	
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
	 * @brief Deletes specified files
	 * @param Path 
	 */
	void DeleteFiles(const FString& Path, const TArray<FString>& Suffixes);
	
    /**
     * @brief Deletes all generated pb files
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
	 * @brief Generate a pb and grpc.pb file 
	 * @param ProtoFile 
	 * @param GeneratePath 
	 */
	void GeneratePBFile(const FString& ProtoFile, const FString& GeneratePath);
	
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


