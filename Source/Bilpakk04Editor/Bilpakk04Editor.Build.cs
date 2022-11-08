using UnrealBuildTool;

public class Bilpakk04Editor : ModuleRules
{
    public Bilpakk04Editor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Bilpakk04"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "AssetTools",
                "UnrealEd"
            }
        );
    }
}