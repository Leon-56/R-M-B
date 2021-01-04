#pragma once
#include "RMBAbilityTypes.h"
#include "Abilities/GameplayAbility.h"
#include "RMB/Characters/RMBCharacterBase.h"
#include "RMBGameplayAbility.generated.h"

class USkeletalMeshComponent;

USTRUCT()
struct RMB_API FAbilityMeshMontage
{
	GENERATED_BODY()

	public:
	UPROPERTY()
	class USkeletalMeshComponent* Mesh;

	UPROPERTY()
	class UAnimMontage* Montage;

	FAbilityMeshMontage() : Mesh(nullptr), Montage(nullptr)
	{
	}

	FAbilityMeshMontage(class USkeletalMeshComponent* InMesh, class UAnimMontage* InMontage) 
        : Mesh(InMesh), Montage(InMontage)
	{
	}
};

UCLASS()
class RMB_API URMBGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	URMBGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	ERMBAbilityInputID AbilityInputID = ERMBAbilityInputID::None;

	// Value to associate an ability with an slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	ERMBAbilityInputID AbilityID = ERMBAbilityInputID::None;

	// Map of gameplay tags to gameplay effect containers
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayEffects")
	TMap<FGameplayTag, FRMBGameplayEffectContainer> EffectContainerMap;
};
