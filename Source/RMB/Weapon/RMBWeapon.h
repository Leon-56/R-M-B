#pragma once

#include "AbilitySystemInterface.h"
#include "RMB/RMB.h"
#include "RMB/Characters/Abilities/RMBAbilitySystemComponent.h"
#include "RMB/Characters/Abilities/RMBGATA_LineTrace.h"

#include "RMBWeapon.generated.h"

UCLASS()
class RMB_API ARMBWeapon : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARMBWeapon();
	
	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "RMB|RMBWeapon")
	virtual USkeletalMeshComponent* GetWeaponMesh() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;

	virtual int32 GetAbilityLevel(ERMBAbilityInputID AbilityID);

	// Getter for LineTraceTargetActor. Spawns it if it doesn't exist yet.
	UFUNCTION(BlueprintCallable, Category = "RMB|Targeting")
    ARMBGATA_LineTrace* GetLineTraceTargetActor();

	// Called when the player equips this weapon
	virtual void Equip();

	// Called when the player unequips this weapon
	virtual void UnEquip();

	virtual void AddAbilities();

	virtual void RemoveAbilities();

protected:

	UPROPERTY()
	ARMBGATA_LineTrace* LineTraceTargetActor;

	UPROPERTY()
	URMBAbilitySystemComponent* AbilitySystemComponent;

	// Collision capsule for when weapon is in pickup mode
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "RMB|RMBWeapon")
	USkeletalMeshComponent* WeaponMesh;

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
};
