#pragma once

#include "CoreMinimal.h"
#include <Runtime/Engine/Public/EngineUtils.h>

namespace Utls
{
	template <typename T>
	static UClass* LoadBlueprintFromPath(const FString Path)
	{
		UBlueprint* blueprint = Cast<UBlueprint>(StaticLoadObject(UObject::StaticClass(), NULL, *Path));
		if (!blueprint)
		{
			UE_LOG(LogTemp, Error, TEXT("[Can't find/load blueprint: %s]"), *FString(typeid(T).name()));
			return nullptr;
		}
		return (UClass*)(blueprint->GeneratedClass);
	}

	template <typename T>
	static TArray<T*> LoadAssetsFromPath(const FString Path)
	{
		TArray<UObject*> Assets;
		TArray<T*> FinalAssets;
		EngineUtils::FindOrLoadAssetsByPath(*Path, Assets, EngineUtils::ATL_Regular);
		for (auto asset : Assets)
		{
			//UE_LOG(LogTemp, Warning, TEXT("[Asset name: %s]"), *asset->GetName());
			FinalAssets.Add(Cast<T>(asset));
		}
		return FinalAssets;
	}
}
