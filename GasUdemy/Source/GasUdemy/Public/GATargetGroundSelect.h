// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetGroundSelect.generated.h"

class UDecalComponent;
class USceneCompoennt;

/**
 * 
 */
UCLASS()
class GASUDEMY_API AGATargetGroundSelect : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	AGATargetGroundSelect();
	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void Tick(float DeltaSeconds);
	virtual void ConfirmTargetingAndContinue() override;

	UFUNCTION(BlueprintCallable, Category = "GroundSelect")
	bool GetPlayerLookingPoint(FVector& OutViewPoint);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn=true), Category = "GroundSelect")
	float Radius;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GroundBlast")
	UDecalComponent* Decal;

	USceneComponent* RootComponent;
};
