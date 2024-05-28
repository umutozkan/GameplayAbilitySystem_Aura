// Copyright o3n Games


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	if (Weapon)
	{
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AAuraEnemy::HighlightActor()
{
	EnableMeshHighlight(GetMesh());
	EnableMeshHighlight(Weapon);
}

void AAuraEnemy::UnHighlightActor()
{
	DisableMeshHighlight(GetMesh());
	DisableMeshHighlight(Weapon);
}

void AAuraEnemy::EnableMeshHighlight(USkeletalMeshComponent* Mesh)
{
	if (!Mesh) return;
	Mesh->SetRenderCustomDepth(true);
}

void AAuraEnemy::DisableMeshHighlight(USkeletalMeshComponent* Mesh)
{
	if (!Mesh) return;
	Mesh->SetRenderCustomDepth(false);
}
