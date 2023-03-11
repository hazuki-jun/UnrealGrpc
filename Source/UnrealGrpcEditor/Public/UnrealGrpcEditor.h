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
     * @brief Generate pb files 
     * @param ExecDirectory 
     * @param Path 
     */
    void GenerateAllPBFiles(const FString &ExecDirectory, const FString &Path);
	
    FString GetProtocExecPath() const;
    
private:
    TSharedPtr<class FUICommandList> ActionList;

	FString ProtoPath;
	FString PbPath;
};
