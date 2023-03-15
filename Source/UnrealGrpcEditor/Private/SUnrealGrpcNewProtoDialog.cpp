// Fill out your copyright notice in the Description page of Project Settings.


#include "SUnrealGrpcNewProtoDialog.h"

#include "DesktopPlatformModule.h"
#include "SChooseDirectoryButton.h"
#include "SlateOptMacros.h"
#include "UnrealGrpcEditorDelegates.h"
#include "Interfaces/IMainFrameModule.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"

#define LOCTEXT_NAMESPACE "UnrealGrpcNewProtoWindow"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUnrealGrpcNewProtoDialog::Construct(const FArguments& InArgs)
{
	TSharedRef<SWidget> ProtoSourcePathWidget = GetProtoSourcePathWidget();
	TSharedRef<SWidget> PBSavePathWidget = GetPBSavePathWidget();
	
	SWindow::Construct(SWindow::FArguments()
			.Title(LOCTEXT("UnrealGrpcWindowTitle", "New Proto"))
			.SupportsMinimize(false)
			.SupportsMaximize(false)
			.ClientSize(FVector2D(600, 300))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				.Padding(FMargin(0.f, 10.f, 0.f, 0.f))
				.AutoHeight()
				[
					ProtoSourcePathWidget
				]
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				.Padding(FMargin(0.f, 10.f, 0.f, 0.f))
				.AutoHeight()
				[
					PBSavePathWidget
				]

				+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Bottom)
				.FillHeight(1.0f)
				.Padding(FMargin(0.f, 0.f, 0.f, 20.f))
				[
					SNew(SHorizontalBox)
					// Add new slot for apply button
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.AutoWidth()
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("PrimaryButton"))
						.Text(LOCTEXT("Apply", "Apply"))
						.OnClicked(this, &SUnrealGrpcNewProtoDialog::OnApplyButtonClicked)
					]
					// Add some gaps between buttons
					+ SHorizontalBox::Slot()
					[
						SNew(SSpacer)
						.Size(FVector2D(30.f, 0.f))
					]
					// Add new slot for cancel button
					+ SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					.AutoWidth()
					[
						SNew(SButton)
						.HAlign(HAlign_Center)
						.ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("Button"))
						.Text(LOCTEXT("Cancel", "Cancel"))
						.OnClicked(this, &SUnrealGrpcNewProtoDialog::OnCancelButtonClicked)
					]
				]
			]
		);
}

TSharedRef<SWidget> SUnrealGrpcNewProtoDialog::GetProtoSourcePathWidget()
{
	return MakeRow(LOCTEXT("Source_Path", "Proto File"), LOCTEXT("Source_Path_Tooltip", "The directory where you place the *.proto files"), EUnrealGrpcChooseDirectory::SourcePath);
}

TSharedRef<SWidget> SUnrealGrpcNewProtoDialog::GetPBSavePathWidget()
{
	return MakeRow(LOCTEXT("Generate_Path", "Generate Path"), LOCTEXT("Save_Path_Tooltip", "The directory to save pb.* files"), EUnrealGrpcChooseDirectory::SaveProto);
}

TSharedRef<SWidget> SUnrealGrpcNewProtoDialog::MakeRow(const FText& RowText, const FText &TooltipText, EUnrealGrpcChooseDirectory ChooseDirectory)
{
	FSlateFontInfo FontStyle = FAppStyle::GetFontStyle( TEXT("PropertyWindow.NormalFont") );
	
	TAttribute<FText> HandleTextChangeRow;

	if (ChooseDirectory == EUnrealGrpcChooseDirectory::SaveProto)
	{
		HandleTextChangeRow.BindRaw(this, &SUnrealGrpcNewProtoDialog::HandleGeneratePathText);
	}
	else
	{
		HandleTextChangeRow.BindRaw(this, &SUnrealGrpcNewProtoDialog::HandleProtoPathText);
	}
	
	TSharedRef<SWidget> Border =
		SNew(SBorder)
		.HAlign(HAlign_Fill)
		.BorderImage(FAppStyle::Get().GetBrush("Brushes.Panel"));
	
	TSharedRef<SSplitter> Splitter =
		SNew(SSplitter).Orientation(Orient_Horizontal)
		+ SSplitter::Slot()
		[
			SNew(STextBlock)
			.AutoWrapText(true)
			.IsEnabled(true)
			.Text(RowText)
			.ToolTipText(TooltipText)
			.Margin(FMargin(5.0f, 0.f, 0.0f, 0.0f))
		]
		+ SSplitter::Slot()
		.Value(4.f)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.FillWidth(1.0f)
			.Padding(FMargin(0.f, 0.f, 10.f, 0.f))
			[
				SNew(SEditableTextBox)
				.Text(HandleTextChangeRow)
				.Font(FontStyle)
			]
		];
	
	// Add choose directory button
	TSharedRef<SHorizontalBox> HorizontalBox =
		SAssignNew(Border, SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		[
			Splitter
		]
		+SHorizontalBox::Slot()
		.Padding(FMargin(0.f, 0.f, 10.f, 3.f))
		.AutoWidth()
		[
			SNew(SChooseDirectoryButton)
			.ChooseDirectory(ChooseDirectory)
			.ClickedDelegate(this, &SUnrealGrpcNewProtoDialog::OnChooseDirectoryButtonClicked)
		];
	
	return Border;
}

void SUnrealGrpcNewProtoDialog::OnChooseDirectoryButtonClicked(EUnrealGrpcChooseDirectory ChooseDirectory)
{
	FString SavedString;
	const FString FileName = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Intermediate"/ "Config";
	FFileHelper::LoadFileToString(SavedString, *FileName);

	FString SrcPath;
	FString DestPath;
	SavedString.Split("|||", &DestPath, &SrcPath);
	
	FString Directory;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		auto DefaultPath = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Source" / "UnrealGrpc";
		if (ChooseDirectory == EUnrealGrpcChooseDirectory::SaveProto && !DestPath.IsEmpty())
		{
			DefaultPath = DestPath;
		}
		else if (ChooseDirectory == EUnrealGrpcChooseDirectory::SourcePath && !SrcPath.IsEmpty())
		{
			DefaultPath = SrcPath;
		}
		
		TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(SharedThis(this));
		void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid()) ? ParentWindow->GetNativeWindow()->GetOSWindowHandle() : nullptr;
		FString Filter = TEXT("Proto file|*.proto");
		TArray<FString> OutFiles;
		for (;;)
		{
			if (DesktopPlatform->OpenFileDialog(ParentWindowHandle, TEXT("Choose A File"), TEXT(""), TEXT(""), Filter, EFileDialogFlags::None, OutFiles))
			{
				if (OutFiles.Num() > 0)
				{
					FString ProtoDirectory;
					ProtoDirectory = ProtoPath = OutFiles[0];
					
					GeneratePath = DestPath;
					
					int32 Pos;
					if (ProtoDirectory.FindLastChar('/', Pos))
					{
						ProtoDirectory.RemoveAt(Pos, ProtoDirectory.Len() - Pos);
					}
					if (ProtoDirectory.FindLastChar('/', Pos))
					{
						ProtoDirectory.RemoveAt(0, Pos + 1);
					}
					GeneratePath = GeneratePath / ProtoDirectory;
				}
			}
			break;
		}
	}
}

FReply SUnrealGrpcNewProtoDialog::OnApplyButtonClicked()
{
	FUnrealGrpcEditorDelegates::OnNewProtoApplied.Broadcast(ProtoPath, GeneratePath);
	RequestDestroyWindow();
	return FReply::Unhandled();
}

FReply SUnrealGrpcNewProtoDialog::OnCancelButtonClicked()
{
	RequestDestroyWindow();
	return FReply::Unhandled();
}

void SUnrealGrpcNewProtoDialog::ShowWindow()
{
	IMainFrameModule& MainFrameModule = FModuleManager::LoadModuleChecked<IMainFrameModule>(TEXT("MainFrame"));

	if ( MainFrameModule.GetParentWindow().IsValid() )
	{
		FSlateApplication::Get().AddWindowAsNativeChild(SharedThis(this), MainFrameModule.GetParentWindow().ToSharedRef());
	}
	else
	{
		FSlateApplication::Get().AddWindow(SharedThis(this));
	}
}

FText SUnrealGrpcNewProtoDialog::HandleProtoPathText() const
{
	return FText::FromString(ProtoPath);
}

FText SUnrealGrpcNewProtoDialog::HandleGeneratePathText() const
{
	return FText::FromString(GeneratePath);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef LOCTEXT_NAMESPACE
