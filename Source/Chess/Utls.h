#pragma once

#include "CoreMinimal.h"
#include <Runtime/Engine/Public/EngineUtils.h>

namespace Utls
{
	const char ROW[8] = { '1', '2', '3', '4', '5', '6', '7', '8' };
	const char COLUMN[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	static FString GetCBoxName(int32 X, int32 Y)
	{
		FString Name;
		Name += COLUMN[X];
		Name += ROW[Y];
		return Name;
	}

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
	static TArray<UTexture2D*> LoadTexturesFromPath(const FString Path)
	{
		TArray<UObject*> Assets;
		TArray<UTexture2D*> Textures;
		EngineUtils::FindOrLoadAssetsByPath(*Path, Assets, EngineUtils::ATL_Regular);
		for (auto asset : Assets)
		{
			//UE_LOG(LogTemp, Warning, TEXT("[Asset name: %s]"), *asset->GetName());
			Textures.Add(Cast<UTexture2D>(asset));
		}
		return Textures;
	}
}
