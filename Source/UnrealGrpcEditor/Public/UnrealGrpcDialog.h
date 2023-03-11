#pragma once

#include "CoreMinimal.h"
#include "UnrealGrpcTypes.h"
#include "Widgets/SWindow.h"

class UNREALGRPCEDITOR_API SUnrealGrpcDialog : public SWindow
{
public:
	SLATE_BEGIN_ARGS( SUnrealGrpcDialog) {}

	SLATE_END_ARGS()

	SUnrealGrpcDialog() {}

	void Construct(const FArguments& InArgs);

	TSharedRef<SWidget> GetProtoSourcePathWidget();
	TSharedRef<SWidget> GetPBSavePathWidget();
	TSharedRef<SWidget> MakeRow(const FText& RowText, const FText &TooltipText, EUnrealGrpcChooseDirectory ChooseDirectory);

	FText HandleSourcePathText() const;

	FText HandleSavePathText() const;
	
	void OnChooseDirectoryButtonClicked(EUnrealGrpcChooseDirectory ChooseDirectory);

	FReply OnApplyButtonClicked();

	FReply OnCancelButtonClicked();
	
	void ShowWindow();
	
private:
	TAttribute<FText> Title;
	FVector2D ClientSize = FVector2D::ZeroVector;

	FText SourcePathText;
	FText SavePathText;

	FString ProtoPath;
	FString PbPath;
};
