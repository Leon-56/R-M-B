#pragma once

#include "RMB/Characters/RMBCharacterBase.h"
#include "RMB/Weapon/RMBWeapon.h"
#include "RMBSurvivorCharacter.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class ERMBSurvivorWeaponState : uint8
{
	// 0
	Rifle					UMETA(DisplayName = "Rifle"),
    // 1
    RifleAiming				UMETA(DisplayName = "Rifle Aiming"),
    // 2
    RocketLauncher			UMETA(DisplayName = "Rocket Launcher"),
    // 3
    RocketLauncherAiming	UMETA(DisplayName = "Rocket Launcher Aiming")
};

USTRUCT()
struct RMB_API FRMBSurvivorInventory
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY()
	TArray<ARMBWeapon*> Weapons;

	// Consumable items

	// Passive items like armor

	// Door keys

	// Etc
};

UCLASS()
class RMB_API ARMBSurvivorCharacter : public ARMBCharacterBase
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCamera;
public:
	ARMBSurvivorCharacter(const class FObjectInitializer& ObjectInitializer);

	// Only called on the Server. Calls before Server's AcknowledgePossession.
	virtual void PossessedBy(AController* NewController) override;

	// Getter for LineTraceTargetActor. Spawns it if it doesn't exist yet.
	UFUNCTION(BlueprintCallable, Category = "RMB|Targeting")
    ARMBGATA_LineTrace* GetLineTraceTargetActor();


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	* Called via input to turn at a given rate. 
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	void BindASCInput();

	bool bASCInputBound;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "RMB|RMBSurvivor")
	TSubclassOf<UGameplayEffect> ReviveEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "RMB|RMBSurvivor")
	TSubclassOf<UGameplayEffect> DeathEffect;
	
	public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCamera() const { return TopDownCamera; }

	UPROPERTY()
	ARMBGATA_LineTrace* LineTraceTargetActor;
};
