#include "UnrealGrpcEditorStyle.h"


#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr< FSlateStyleSet > FUnrealGrpcEditorStyle::UnrealGrpcEditorStyleInstance = nullptr;

void FUnrealGrpcEditorStyle::Initialize()
{
	Get();
}

void FUnrealGrpcEditorStyle::Shutdown()
{
	if (UnrealGrpcEditorStyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*UnrealGrpcEditorStyleInstance);
		ensure(UnrealGrpcEditorStyleInstance.IsUnique());
		UnrealGrpcEditorStyleInstance.Reset();
	}
}

void FUnrealGrpcEditorStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FUnrealGrpcEditorStyle::Get()
{
	if (!UnrealGrpcEditorStyleInstance.IsValid())
	{
		UnrealGrpcEditorStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*UnrealGrpcEditorStyleInstance);
	}
	return *UnrealGrpcEditorStyleInstance;
}

FName FUnrealGrpcEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("UnrealGrpcEditor"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define DEFAULT_FONT(...) FCoreStyle::GetDefaultFontStyle(__VA_ARGS__)

const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);
const FVector2D Icon64x64(200.0f, 200.0f);
const FVector2D Icon512x512(512.0f, 512.0f);

TSharedRef<FSlateStyleSet> FUnrealGrpcEditorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("UnrealGrpcEditor"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("UnrealGrpc")->GetBaseDir() / TEXT("Resources"));

	Style->Set("UnrealGrpcEditor.Menu", new IMAGE_BRUSH(TEXT("grpc_logo_x40"), Icon40x40));

	return Style;
}

const FSlateBrush* FUnrealGrpcEditorStyle::GetBrush(FName PropertyName, const ANSICHAR* Specifier)
{
	return nullptr;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef DEFAULT_FONT