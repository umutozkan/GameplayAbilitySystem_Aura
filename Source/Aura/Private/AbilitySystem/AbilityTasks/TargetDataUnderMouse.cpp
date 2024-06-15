// Copyright o3n Games


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	Super::Activate();

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		// TODO: We are on the server, so listen for target data
	}
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	if (APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get())
	{
		FHitResult CursorHit;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
		if (!CursorHit.bBlockingHit) return;

		FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
		Data->HitResult = CursorHit;
		FGameplayAbilityTargetDataHandle DataHandle;
		DataHandle.Add(Data);

		AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
		                                                      GetActivationPredictionKey(),
		                                                      DataHandle,
		                                                      FGameplayTag(),
		                                                      AbilitySystemComponent->ScopedPredictionKey);

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			ValidData.Broadcast(DataHandle);
		}
	}
}
