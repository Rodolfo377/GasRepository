// Fill out your copyright notice in the Description page of Project Settings.


#include "GATargetGroundSelect.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"
#include "Components/DecalComponent.h"
#include "Components/SceneComponent.h"

AGATargetGroundSelect::AGATargetGroundSelect()
{
	PrimaryActorTick.bCanEverTick = true;
	Decal = CreateDefaultSubobject<UDecalComponent>("Decal");
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(RootComponent);
	Decal->SetupAttachment(RootComponent);
	Radius = 200.0f;
	Decal->DecalSize = FVector(Radius);
}

void AGATargetGroundSelect::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGATargetGroundSelect::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector LookPoint;
	GetPlayerLookingPoint(LookPoint);
	Decal->SetWorldLocation(LookPoint);
}

void AGATargetGroundSelect::ConfirmTargetingAndContinue()
{
	
	FVector ViewLocation;
	GetPlayerLookingPoint(ViewLocation);

	TArray<FOverlapResult> Overlaps;
	TArray<TWeakObjectPtr<AActor>> OverlappedActors;
	bool TraceComplex = false;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bTraceComplex = TraceComplex;
	CollisionQueryParams.bReturnPhysicalMaterial = false;
	if (APawn* MasterPawn = MasterPC->GetPawn())
	{
		CollisionQueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}
	
	bool TryOverlap = GetWorld()->OverlapMultiByObjectType(Overlaps,
		ViewLocation, 
		FQuat::Identity, 
		FCollisionObjectQueryParams(ECC_Pawn), 
		FCollisionShape::MakeSphere(Radius), 
		CollisionQueryParams);

	if (TryOverlap)
	{
		for (int32 i = 0; i < Overlaps.Num(); ++i)
		{
			APawn* PawnOverlapped = Cast<APawn>(Overlaps[i].GetActor());
			if (PawnOverlapped && !OverlappedActors.Contains(PawnOverlapped))
			{
				OverlappedActors.Add(PawnOverlapped);
			}
		}
	}

	FGameplayAbilityTargetData_LocationInfo* CenterLocation = new FGameplayAbilityTargetData_LocationInfo();
	if (Decal)
	{
		CenterLocation->TargetLocation.LiteralTransform = Decal->GetComponentTransform();
		CenterLocation->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	}

	if (OverlappedActors.Num() > 0)
	{
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlappedActors);
		TargetData.Add(CenterLocation);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle(CenterLocation));
	}
}

bool AGATargetGroundSelect::GetPlayerLookingPoint(FVector& OutViewPoint)
{
	FVector ViewPoint;
	FRotator ViewRotation;
	MasterPC->GetPlayerViewPoint(ViewPoint, ViewRotation);
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	if (APawn* MasterPawn = MasterPC->GetPawn())
	{
		QueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}

	bool TryTrace = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPoint, ViewPoint + ViewRotation.Vector() * 10000.0f, ECC_Visibility, QueryParams);
	if (TryTrace)
	{
		OutViewPoint = HitResult.ImpactPoint;
	}
	else
	{
		OutViewPoint = FVector();
	}
	return TryTrace;
}
