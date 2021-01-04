
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RMBGameMode.generated.h"

UCLASS()
class RMB_API ARMBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARMBGameModeBase();
	void SurvivorDied(AController* Controller);

protected:
	float RespawnDelay;

	TSubclassOf<class ARMBSurvivorCharacter> SurvivorClass;

	AActor* EnemySpawnPoint;

	virtual void BeginPlay() override;

	void RespawnSurvivor(AController* Controller);
};



