// Fill out your copyright notice in the Description page of Project Settings.

#include "DynamicTextureStaticMeshActor.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"


// Sets default values
ADynamicTextureStaticMeshActor::ADynamicTextureStaticMeshActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	RootComponent = GetStaticMeshComponent();

	if (!IsRunningDedicatedServer()) {
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [ADynamicTextureStaticMeshActor] Construct - Not a Dedicated server."));
		// For some reason the dedicated server can't load the material, but it does not need it.

		// The Material needs a Texture Sample 2d parameter named "BaseColor"

		static ConstructorHelpers::FObjectFinder<UMaterial> MatFinder(TEXT("Material'/Game/Display/m_16x9_display.m_16x9_display'"));
		// Material'/Game/Display/m_16x9_display.m_16x9_display'
		if (MatFinder.Succeeded())
		{
			UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [ADynamicTextureStaticMeshActor] [Construct] Found Material "));
			Material = MatFinder.Object;
			//MaterialInstance = UMaterialInstanceDynamic::Create(Material, NULL);
			//GetStaticMeshComponent()->SetMaterial(0, MaterialInstance);
			//MaterialInstance = GetStaticMeshComponent()->CreateAndSetMaterialInstanceDynamicFromMaterial(0, Material);

			// For some reason on OpenMOBA begin play is not called
			// Trying this here instead - not working
			//MaterialInstance = UMaterialInstanceDynamic::Create(Material, NULL);
			//GetStaticMeshComponent()->SetMaterial(0, MaterialInstance);
		}


	}

	//bReplicates = true;
	//bReplicateMovement = true;
}


void ADynamicTextureStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();

	// Only run this on client
	if (!IsRunningDedicatedServer())
	{
		UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [ADynamicTextureStaticMeshActor] BeginPlay - Not a Dedicated server."));

		// Only do this if it was not done previously.
		//if (!MaterialInstance)
		//{
			UE_LOG(LogTemp, Log, TEXT("[UETOPIA] [ADynamicTextureStaticMeshActor] BeginPlay - MaterialInstance is not valid."));
			MaterialInstance = UMaterialInstanceDynamic::Create(Material, NULL);
			GetStaticMeshComponent()->SetMaterial(0, MaterialInstance);
		//}
		
	}
}


