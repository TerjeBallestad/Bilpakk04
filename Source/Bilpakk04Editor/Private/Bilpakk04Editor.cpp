#include "Bilpakk04Editor.h"
#include "Toolkits/AssetEditorManager.h"

#include "AssetToolsModule.h"
#include "IAssetTools.h"

#define LOCTEXT_NAMESPACE "FBilpakk04EditorModule"

void FBilpakk04EditorModule::StartupModule()
{
	// const auto Style = MakeShareable(new FTextAssetEditorStyle());
	// IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	//
	// RegisterAssetTypeAction(AssetTools, MakeShareable(new FTextAssetActions(Style.ToSharedRef())));
}

void FBilpakk04EditorModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FBilpakk04EditorModule, Bilpakk04Editor)