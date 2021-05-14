#include "RMBWeapon.h"

#include "Components/CapsuleComponent.h"

ARMBWeapon::ARMBWeapon()
{
	// Set this actor to never tick
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	bNetUseOwnerRelevancy = true;
	NetUpdateFrequency = 100.0f; // Set this to a value that's appropriate for your game
	
	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(FName("CollisionComponent"));
	CollisionComp->InitCapsuleSize(40.0f, 50.0f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Manually enable when in pickup mode
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("WeaponMesh"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->CastShadow = false;
	WeaponMesh->SetVisibility(true, true);
	WeaponMesh->SetupAttachment(CollisionComp);
	WeaponMesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
}

UAbilitySystemComponent* ARMBWeapon::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

USkeletalMeshComponent* ARMBWeapon::GetWeaponMesh() const
{
	return WeaponMesh;
}

void ARMBWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}

void ARMBWeapon::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
}

int32 ARMBWeapon::GetAbilityLevel(ERMBAbilityInputID AbilityID)
{
	// All abilities for now are level 1
	return 1;
}

ARMBGATA_LineTrace* ARMBWeapon::GetLineTraceTargetActor()
{
	if (LineTraceTargetActor)
	{
		return LineTraceTargetActor;
	}

	LineTraceTargetActor = GetWorld()->SpawnActor<ARMBGATA_LineTrace>();
	LineTraceTargetActor->SetOwner(this);
	return LineTraceTargetActor;
}

void ARMBWeapon::Equip()
{
}

void ARMBWeapon::UnEquip()
{
}

void ARMBWeapon::AddAbilities()
{
}

void ARMBWeapon::RemoveAbilities()
{
}

void ARMBWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ARMBWeapon::EndPlay(EEndPlayReason::Type EndPlayReason)
{
}
