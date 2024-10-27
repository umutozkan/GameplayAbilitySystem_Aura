// Copyright o3n Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AAuraAIController;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();
	virtual void PossessedBy(AController* NewController) override;

	/** Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** End Enemy Interface */

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	virtual void Die() override;
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/** End Combat Interface */

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadOnly, Category="Aura|Combat")
	bool bHitReacting = false;

	UPROPERTY(EditAnywhere, Category="Aura|Combat")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, Category="Aura|Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite, Category="Aura|Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Aura|Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Aura|Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category="Aura|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;

private:
	static void EnableMeshHighlight(USkeletalMeshComponent* Mesh);
	static void DisableMeshHighlight(USkeletalMeshComponent* Mesh);
};
