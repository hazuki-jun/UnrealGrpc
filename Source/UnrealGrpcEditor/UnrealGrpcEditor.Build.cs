using UnrealBuildTool;

public class UnrealGrpcEditor : ModuleRules
{
    public UnrealGrpcEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core", "CoreUObject", "Engine", "Slate", "SlateCore", "UnrealEd", "Projects",
            "ToolMenus", "MainFrame", "DesktopPlatform"
        });
    }
}