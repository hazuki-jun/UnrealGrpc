// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealGrpcTypes.h"
#include "Widgets/Input/SButton.h"

/**
 * 
 */
class UNREALGRPCEDITOR_API SChooseDirectoryButton : public SButton
{
public:
	DECLARE_DELEGATE_OneParam(FOnClickedDelegate, EUnrealGrpcChooseDirectory)
	
	SLATE_BEGIN_ARGS(SChooseDirectoryButton)
		: _Text()
		, _ChooseDirectory(EUnrealGrpcChooseDirectory::None)
		{
		}

	/** The text to display in this button, if no custom content is specified */
	SLATE_ATTRIBUTE( FText, Text )

	SLATE_ATTRIBUTE( EUnrealGrpcChooseDirectory, ChooseDirectory )

	SLATE_EVENT( FOnClickedDelegate, ClickedDelegate )
	
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FReply OnClicked();
	
	FOnClickedDelegate OnClickedDelegate;
	
private:
	TAttribute<EUnrealGrpcChooseDirectory> ChooseDirectory;
};
