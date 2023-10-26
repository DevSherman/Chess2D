#pragma once

#include "CoreMinimal.h"
#include "Chess2D.h"
#include <Runtime/Engine/Public/EngineUtils.h>

namespace Utls
{
	static FString GetCBoxName(int X, int Y)
	{
		FString Name = "";
		Name += COLUMN[X];
		Name += ROW[Y];
		//UE_LOG(LogTemp, Warning, TEXT("Name: %d,%d %s"), X + 1, Y + 1, *Name);
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
