#include "RMBWeapon.h"

ARMBWeapon::ARMBWeapon()
{
}

UAbilitySystemComponent* ARMBWeapon::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
