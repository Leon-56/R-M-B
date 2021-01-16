#pragma once
#include "GameplayEffectExecutionCalculation.h"

#include "RMBDamageExecutionCalc.generated.h"

UCLASS()
class URMBDamageExecutionCalc : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	URMBDamageExecutionCalc();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
	float HeadShotMultiplier;
	
};
