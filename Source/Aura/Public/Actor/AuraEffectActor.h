// Copyright o3n Games

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplciationPolicy: uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy: uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void EndOverlap(AActor* TargetActor);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Aura|Applied Effects")
	bool bDestroyOnEffectApplication = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Aura|Applied Effects")
	bool bApplyEffectsToEnemies = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Aura|Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Aura|Applied Effects")
	EEffectApplciationPolicy InstantEffectApplicationPolicy = EEffectApplciationPolicy::DoNotApply;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Aura|Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Aura|Applied Effects")
	EEffectApplciationPolicy DurationEffectApplicationPolicy = EEffectApplciationPolicy::DoNotApply;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Aura|Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Aura|Applied Effects")
	EEffectApplciationPolicy InfiniteEffectApplicationPolicy = EEffectApplciationPolicy::DoNotApply;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Aura|Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Aura|Applied Effects")
	float ActorLevel = 1.f;
};
