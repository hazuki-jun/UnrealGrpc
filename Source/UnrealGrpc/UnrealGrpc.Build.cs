// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class UnrealGrpc : ModuleRules
{
	private string ThirdPartyDirectory => Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/"));

	private string ThirdPartyLibrariesDirectory => Path.Combine(ThirdPartyDirectory, "libs/");

	private string PbDirectory()
	{
		string FileName = Path.Combine(PluginDirectory, "Intermediate/Config");
		if (File.Exists(FileName) == true)
		{
			IEnumerable<string> Lines = File.ReadLines(FileName);
			string[] SavedStrings = String.Join(Environment.NewLine, Lines).Split("|||");
			if (SavedStrings.Length >= 2)
			{
				return SavedStrings[0];
			}
		}
		
		return "";
	}
	
	public UnrealGrpc(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UnrealGrpcProtobuf" });
  //
		// if (Target.Platform == UnrealTargetPlatform.Win64)
		// {
		// 	bEnableExceptions = true;
  //           bEnableUndefinedIdentifierWarnings = false;
		// 	
		// 	PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS");
		// 	PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI");
		// 	PublicDefinitions.Add("GRPC_ALLOW_EXCEPTIONS=0");
		// 	PublicDefinitions.Add("GPR_FORBID_UNREACHABLE_CODE");
		// 	
		// 	PublicIncludePaths.Add(Path.Combine(PluginDirectory, "Source/UnrealGrpc"));
		// 	// PublicIncludePaths.Add(PbDirectory());
		// 	PublicIncludePaths.Add(Path.Combine(ThirdPartyDirectory, "include"));
  //
		// 	PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "libprotobuf.lib"));
		// 	
		// 	PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "address_sorting.lib"));
	 //        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "cares.lib"));
	 //        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "upb.lib"));
	 //        
	 //        // grpc merged library
	 //        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "grpc_core.lib"));
		// 	// absl merged library
	 //        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyLibrariesDirectory, "absl_core.lib"));
	 //        
	 //        AddEngineThirdPartyPrivateStaticDependencies(Target, "zlib");
	}
}
