// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "CharacterBase.h"

UAttributeSetBase::UAttributeSetBase():
	Health(200.0f),
	MaxHealth(200.0f),
	Mana(100.0f),
	MaxMana(100.0f),
	Strength(250.0f),
	MaxStrength(250.0f)
{

}

void UAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	if(Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(),GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f ,MaxHealth.GetCurrentValue()));
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());

		if (ACharacterBase* CharacterOwner = Cast<ACharacterBase>(GetOwningActor()))
		{	
			if (Health.GetCurrentValue() == MaxHealth.GetCurrentValue())
			{
				CharacterOwner->AddGameplayTag(CharacterOwner->FullHealthTag);
			}
			else
			{
				CharacterOwner->RemoveGameplayTag(CharacterOwner->FullHealthTag);
			}
		}
	}
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.0f, MaxMana.GetCurrentValue()));
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Strength)))
	{
		Health.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.0f, MaxStrength.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.0f, MaxStrength.GetCurrentValue()));
		OnStrengthChange.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
	}
}
