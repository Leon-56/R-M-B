#include "RMBPlayerController.h"

ARMBPlayerController::ARMBPlayerController()
{
}

void ARMBPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ARMBCharacterBase* TargetCharacter,
	FGameplayTagContainer DamageNumberTags)
{
}

bool ARMBPlayerController::ShowDamageNumber_Validate(float DamageAmount, ARMBCharacterBase* TargetCharacter,
	FGameplayTagContainer DamageNumberTags)
{
	return true;
}

void ARMBPlayerController::SetRespawnCountdown_Implementation(float RespawnTimeRemaining)
{
	
}

bool ARMBPlayerController::SetRespawnCountdown_Validate(float RespawnTimeRemaining)
{
	return true;
}

void ARMBPlayerController::ClientSetControlRotation_Implementation(FRotator NewRotation)
{
}

bool ARMBPlayerController::ClientSetControlRotation_Validate(FRotator NewRotation)
{
	return true;
}
