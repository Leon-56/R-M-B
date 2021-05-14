
#include "RMBGameMode.h"
#include "Characters/Survivor/RMBSurvivorCharacter.h"
#include "GameFramework/SpectatorPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RMBPlayerController.h"
#include "UObject/ConstructorHelpers.h"

ARMBGameModeBase::ARMBGameModeBase()
{
	RespawnDelay = 5.0f;

	SurvivorClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/02_Blueprint/03_Survivor/BP_Survivor"));
	if (!SurvivorClass)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Failed to find SurvivorClass. If it was moved, please update the reference location in C++."), *FString(__FUNCTION__));
	}
}

void ARMBGameModeBase::SurvivorDied(AController* Controller)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ASpectatorPawn* SpectatorPawn = GetWorld()->SpawnActor<ASpectatorPawn>(SpectatorClass, Controller->GetPawn()->GetActorTransform(), SpawnParameters);

	Controller->UnPossess();
	Controller->Possess(SpectatorPawn);

	FTimerHandle RespawnTimerHandle;
	FTimerDelegate RespawnDelegate;

	RespawnDelegate = FTimerDelegate::CreateUObject(this, &ARMBGameModeBase::RespawnSurvivor, Controller);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnDelegate, RespawnDelay, false);

	ARMBPlayerController* PC = Cast<ARMBPlayerController>(Controller);
	if (PC)
	{
		PC->SetRespawnCountdown(RespawnDelay);
	}
}

void ARMBGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Get the enemy hero spawn point
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		if (Actor->GetName() == FString("EnemyHeroSpawn"))
		{
			EnemySpawnPoint = Actor;
			break;
		}
	}

	if (!EnemySpawnPoint)
	{
		UE_LOG(LogTemp, Error, TEXT("%s EnemySpawnPoint is null."), *FString(__FUNCTION__));
	}
}

void ARMBGameModeBase::RespawnSurvivor(AController* Controller)
{
	if (Controller->IsPlayerController())
	{
		// Respawn player hero
		AActor* PlayerStart = FindPlayerStart(Controller);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ARMBSurvivorCharacter* Survivor = GetWorld()->SpawnActor<ARMBSurvivorCharacter>(SurvivorClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParameters);

		APawn* OldSpectatorPawn = Controller->GetPawn();
		Controller->UnPossess();
		OldSpectatorPawn->Destroy();
		Controller->Possess(Survivor);
		
		ARMBPlayerController* PC = Cast<ARMBPlayerController>(Controller);
		if (PC)
		{
			PC->ClientSetControlRotation(PlayerStart->GetActorRotation());
		}
	}
	else
	{
		// Respawn AI hero
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ARMBSurvivorCharacter* Survivor = GetWorld()->SpawnActor<ARMBSurvivorCharacter>(SurvivorClass, EnemySpawnPoint->GetActorTransform(), SpawnParameters);

		APawn* OldSpectatorPawn = Controller->GetPawn();
		Controller->UnPossess();
		OldSpectatorPawn->Destroy();
		Controller->Possess(Survivor);
	}
}
