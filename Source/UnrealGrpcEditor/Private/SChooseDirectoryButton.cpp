// Fill out your copyright notice in the Description page of Project Settings.


#include "SChooseDirectoryButton.h"

#include "SlateOptMacros.h"

#define LOCTEXT_NAMESPACE "SelectPathButton"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SChooseDirectoryButton::Construct(const FArguments& InArgs)
{
	ChooseDirectory = InArgs._ChooseDirectory;
	OnClickedDelegate = InArgs._ClickedDelegate;
	
	SButton::Construct(
		SButton::FArguments()
		.HAlign(HAlign_Center)
		.ButtonStyle( FAppStyle::Get(), "HoverHintOnly" )
		.ForegroundColor( FSlateColor::UseForeground() )
		.IsFocusable(false)
		.Text(InArgs._Text)
		.OnClicked(this, &SChooseDirectoryButton::OnClicked)
		[
			SNew(SImage)
			.Image(FAppStyle::GetBrush("PropertyWindow.Button_Ellipsis"))
			.ColorAndOpacity(FSlateColor::UseForeground())
		]);
		
}

FReply SChooseDirectoryButton::OnClicked()
{
	OnClickedDelegate.ExecuteIfBound(ChooseDirectory.Get());
	
	return FReply::Unhandled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE
