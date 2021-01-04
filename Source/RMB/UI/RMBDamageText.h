#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/WidgetComponent.h"

#include "RMBDamageText.generated.h"

UCLASS()
class RMB_API URMBDamageText : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage, const FGameplayTagContainer& Tags);
};