#include "RMBPlayerState.h"

#include "AbilitySystemComponent.h"
#include "RMB/Characters/Abilities/RMBAbilitySystemComponent.h"
#include "RMB/Characters/Abilities/AttributeSets/RMBAttributeSetBase.h"
#include "RMB/Characters/Survivor/RMBSurvivorCharacter.h"

ARMBPlayerState::ARMBPlayerState()
{
	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<URMBAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another GDPlayerState (Hero) receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	AttributeSetBase = CreateDefaultSubobject<URMBAttributeSetBase>(TEXT("AttributeSetBase"));

	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;

	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead");
	KnockedDownTag = FGameplayTag::RequestGameplayTag("State.KnockedDown");
}

UAbilitySystemComponent* ARMBPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

URMBAttributeSetBase* ARMBPlayerState::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool ARMBPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

float ARMBPlayerState::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float ARMBPlayerState::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float ARMBPlayerState::GetHealthRegenRate() const
{
	return AttributeSetBase->GetHealthRegenRate();
}

void ARMBPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		// Attribute change callbacks
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &ARMBPlayerState::HealthChanged);

		// Tag change callbacks
		// AbilitySystemComponent->RegisterGameplayTagEvent(KnockedDownTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ARMBPlayerState::KnockDownTagChanged);
	}
}

void ARMBPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	// Check for and handle knockdown and death
	ARMBSurvivorCharacter* Survivor = Cast<ARMBSurvivorCharacter>(GetPawn());
	if (IsValid(Survivor) && !IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		if (Survivor)
		{
			Survivor->FinishDying();
		}
	}
}

void ARMBPlayerState::KnockDownTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
}
