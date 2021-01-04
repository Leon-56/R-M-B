#pragma once

#include "AbilitySystemInterface.h"
#include "RMB/Characters/Abilities/RMBAbilitySystemComponent.h"
#include "RMBWeapon.generated.h"

UCLASS()
class RMB_API ARMBWeapon : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARMBWeapon();
	
	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY()
	URMBAbilitySystemComponent* AbilitySystemComponent;
};
