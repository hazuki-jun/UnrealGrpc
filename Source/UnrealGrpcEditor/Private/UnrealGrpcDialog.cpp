#include "UnrealGrpcDialog.h"

#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "SChooseDirectoryButton.h"
#include "UnrealGrpcEditorDelegates.h"
#include "Components/SlateWrapperTypes.h"
#include "Interfaces/IMainFrameModule.h"
#include "Interfaces/IPluginManager.h"
#include "Misc/FileHelper.h"

#define LOCTEXT_NAMESPACE "UnrealGrpcWindow"

void SUnrealGrpcDialog::Construct(const FArguments& InArgs)
{
	TSharedRef<SWidget> ProtoSourcePathWidget = GetProtoSourcePathWidget();
	TSharedRef<SWidget> PBSavePathWidget = GetPBSavePathWidget();
	
	SWindow::Construct(SWindow::FArguments()
		.Title(LOCTEXT("UnrealGrpcWindowTitle", "UnrealGrpc Settings"))
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
					.OnClicked(this, &SUnrealGrpcDialog::OnApplyButtonClicked)
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
					.OnClicked(this, &SUnrealGrpcDialog::OnCancelButtonClicked)
				]
			]
		]
	);
	
	FString SavedString;
	const FString FileName = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Intermediate"/ "Config";
	FFileHelper::LoadFileToString(SavedString, *FileName);
	SavedString.Split("|||", &PbPath, &ProtoPath);
	SavePathText = FText::FromString(PbPath);
	SourcePathText = FText::FromString(ProtoPath);
}

FReply SUnrealGrpcDialog::OnApplyButtonClicked()
{
	if (PbPath.IsEmpty() && ProtoPath.IsEmpty())
	{
		return FReply::Unhandled();
	}
	
	FString SavedString;
	SavedString.Append(PbPath);
	SavedString.Append("|||");
	SavedString.Append(ProtoPath);
	const FString FileName = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Intermediate"/ "Config";
	FFileHelper::SaveStringToFile(SavedString, *FileName);

	RequestDestroyWindow();
	return FReply::Unhandled();
}

FReply SUnrealGrpcDialog::OnCancelButtonClicked()
{
	RequestDestroyWindow();
	return FReply::Unhandled();
}

TSharedRef<SWidget> SUnrealGrpcDialog::GetProtoSourcePathWidget()
{
	return MakeRow(LOCTEXT("Source_Path", "Proto Path"), LOCTEXT("Source_Path_Tooltip", "The directory where you place the *.proto files"), EUnrealGrpcChooseDirectory::SourcePath);
}

TSharedRef<SWidget> SUnrealGrpcDialog::GetPBSavePathWidget()
{
	return MakeRow(LOCTEXT("Save_Path", "PB Path"), LOCTEXT("Save_Path_Tooltip", "The directory to save pb.* files"), EUnrealGrpcChooseDirectory::SaveProto);
}

TSharedRef<SWidget> SUnrealGrpcDialog::MakeRow(const FText& RowText, const FText &TooltipText, EUnrealGrpcChooseDirectory ChooseDirectory)
{
	FSlateFontInfo FontStyle = FAppStyle::GetFontStyle( TEXT("PropertyWindow.NormalFont") );
	
	TAttribute<FText> HandleTextChangeRow;

	if (ChooseDirectory == EUnrealGrpcChooseDirectory::SaveProto)
	{
		HandleTextChangeRow.BindRaw(this, &SUnrealGrpcDialog::HandleSavePathText);
	}
	else
	{
		HandleTextChangeRow.BindRaw(this, &SUnrealGrpcDialog::HandleSourcePathText);
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
			.ClickedDelegate(this, &SUnrealGrpcDialog::OnChooseDirectoryButtonClicked)
		];
	
	return Border;
}

FText SUnrealGrpcDialog::HandleSourcePathText() const
{
	return SourcePathText;
}

FText SUnrealGrpcDialog::HandleSavePathText() const
{
	return SavePathText;
}

void SUnrealGrpcDialog::OnChooseDirectoryButtonClicked(EUnrealGrpcChooseDirectory ChooseDirectory)
{
	FString Directory;
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		auto DefaultPath = IPluginManager::Get().FindPlugin(TEXT("UnrealGrpc"))->GetBaseDir() / "Source" / "UnrealGrpc";
		if (ChooseDirectory == EUnrealGrpcChooseDirectory::SaveProto && !PbPath.IsEmpty())
		{
			DefaultPath = PbPath;
		}
		else if (ChooseDirectory == EUnrealGrpcChooseDirectory::SourcePath && !ProtoPath.IsEmpty())
		{
			DefaultPath = ProtoPath;
		}
		
		TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().FindWidgetWindow(SharedThis(this));
		void* ParentWindowHandle = (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid()) ? ParentWindow->GetNativeWindow()->GetOSWindowHandle() : nullptr;
		// Loop until; a) the user cancels (OpenDirectoryDialog returns false), or, b) the chosen path is valid (IsValidPath returns true)
		for (;;)
		{
			if (DesktopPlatform->OpenDirectoryDialog(ParentWindowHandle, LOCTEXT("FolderDialogTitle", "Choose a directory").ToString(), DefaultPath, Directory))
			{
				if (ChooseDirectory == EUnrealGrpcChooseDirectory::SaveProto)
				{
					PbPath = Directory;
					SavePathText = FText::FromString(Directory);
				}
				else
				{
					ProtoPath = Directory;
					SourcePathText = FText::FromString(Directory);
				}
				
				FUnrealGrpcEditorDelegates::OnSettingsApplied.Broadcast(PbPath, ProtoPath);
			}
			break;
		}
	}
}

void SUnrealGrpcDialog::ShowWindow()
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

#undef LOCTEXT_NAMESPACE
