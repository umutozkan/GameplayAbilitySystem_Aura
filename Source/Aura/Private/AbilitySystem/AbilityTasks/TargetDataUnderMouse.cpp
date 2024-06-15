// Copyright o3n Games


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

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
	
	if (APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get())
	{
		FHitResult CursorHit;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
		if (!CursorHit.bBlockingHit) return;
		ValidData.Broadcast(CursorHit.Location);
	}
}
