// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GasUdemyHUD.generated.h"

UCLASS()
class AGasUdemyHUD : public AHUD
{
	GENERATED_BODY()

public:
	AGasUdemyHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

