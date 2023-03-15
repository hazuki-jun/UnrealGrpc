// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealGrpcTypes.h"
#include "Widgets/SWindow.h"

/**
 * 
 */
class UNREALGRPCEDITOR_API SUnrealGrpcNewProtoDialog : public SWindow
{
public:
	SLATE_BEGIN_ARGS(SUnrealGrpcNewProtoDialog)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	
	TSharedRef<SWidget> GetProtoSourcePathWidget();
	TSharedRef<SWidget> GetPBSavePathWidget();
	TSharedRef<SWidget> MakeRow(const FText& RowText, const FText &TooltipText, EUnrealGrpcChooseDirectory ChooseDirectory);

	void OnChooseDirectoryButtonClicked(EUnrealGrpcChooseDirectory ChooseDirectory);
	
	FReply OnApplyButtonClicked();
	FReply OnCancelButtonClicked();
	
	void ShowWindow();

	FText HandleProtoPathText() const;
	FText HandleGeneratePathText() const;

	FString ProtoPath;
	FString GeneratePath;
};
