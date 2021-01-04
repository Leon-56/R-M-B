#pragma once

#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "RMB/RMB.h"
#include "RMBCharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ARMBCharacterBase*, Character);

USTRUCT(BlueprintType)
struct RMB_API FRMBDamageNumber
{
	GENERATED_BODY()

	float DamageAmount;

	FGameplayTagContainer Tags;

	FRMBDamageNumber() {}

	FRMBDamageNumber(float InDamageAmount, FGameplayTagContainer InTags) : DamageAmount(InDamageAmount)
	{
		Tags.AppendTags(InTags);
	}
};

UCLASS()
class RMB_API ARMBCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Set default values of this character's properties
	ARMBCharacterBase(const class FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, Category = "RMB|RMBCharacter")
	FCharacterDiedDelegate OnCharacterDied;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "RMB|RMBCharacter")
	virtual bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "RMB|RMBCharacter")
	virtual int32 GetAbilityLevel(ERMBAbilityInputID AbilityID) const;

	virtual void RemoveCharacterAbilities();

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "RMB|RMBCharacter")
	virtual void FinishDying();

	virtual void AddDamageNumber(float Damage, FGameplayTagContainer DamageNumberTags);

	/**
	* Getters for attributes from GSAttributeSetBase
	**/

	UFUNCTION(BlueprintCallable, Category = "RMB|RMBCharacter|Attributes")
    int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "RMB|RMBCharacter|Attributes")
    float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "RMB|RMBCharacter|Attributes")
    float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "RMB|RMBCharacter|Attributes")
    float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "RMB|RMBCharacter|Attributes")
    float GetMaxStamina() const;

	// Gets the Current value of MoveSpeed
	UFUNCTION(BlueprintCallable, Category = "RMB|RMBCharacter|Attributes")
    float GetMoveSpeed() const;

	// Gets the Base value of MoveSpeed
	UFUNCTION(BlueprintCallable, Category = "RMB|RMBCharacter|Attributes")
    float GetMoveSpeedBaseValue() const;

protected:
	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	TArray<FRMBDamageNumber> DamageNumberQueue;
	FTimerHandle DamageNumberTimer;

	// Reference to the ASC. It will live on the PlayerState or here if the character doesn't have a PlayerState.
	UPROPERTY()
	class URMBAbilitySystemComponent* AbilitySystemComponent;

	// Reference to the AttributeSetBase. It will live on the PlayerState or here if the character doesn't have a PlayerState.
	UPROPERTY()	
	class URMBAttributeSetBase* AttributeSetBase;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RMB|RMBCharacter")
	FText CharacterName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RMB|Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RMB|Audio")
	class USoundCue* DeathSound;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RMB|Abilities")
	TArray<TSubclassOf<class URMBGameplayAbility>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RMB|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RMB|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	UPROPERTY(EditAnywhere, Category = "RMB|UI")
	TSubclassOf<class URMBDamageText> DamageNumberClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	virtual void ShowDamageNumber();


	/**
	* Setters for Attributes. Only use these in special cases like Respawning, otherwise use a GE to change Attributes.
	* These change the Attribute's Base Value.
	*/

	virtual void SetHealth(float Health);
	virtual void SetStamina(float Stamina);
};
