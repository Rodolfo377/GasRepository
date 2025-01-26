// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorAround.generated.h"

/**
 * 
 */
UCLASS()
class GASUDEMY_API AGATargetActorAround : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	void StartTargeting(UGameplayAbility* Ability) override;

	void ConfirmTargetingAndContinue() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "FindAround")
	float Radius;
};
