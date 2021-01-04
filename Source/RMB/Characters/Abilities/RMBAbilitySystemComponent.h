#pragma once
#include "AbilitySystemComponent.h"
#include "RMBAbilitySystemComponent.generated.h"

UCLASS()
class RMB_API URMBAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	URMBAbilitySystemComponent();

	bool bCharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;
};
