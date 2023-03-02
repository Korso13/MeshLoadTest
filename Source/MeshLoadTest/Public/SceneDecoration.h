// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneDecoration.generated.h"

UCLASS()
class MESHLOADTEST_API ASceneDecoration : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	class USceneComponent* SceneRoot;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* ActorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UStaticMesh> MeshRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UMaterial> MaterialRef;
	
	TSharedPtr<struct FStreamableHandle> MeshLoadHandler;
	TSharedPtr<FStreamableHandle> MaterialLoadHandler;

	double ExecutionStartTime;
	double LocalExecStartTime;
	
public:	
	// Sets default values for this actor's properties
	ASceneDecoration();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LoadResources();

	void LoadResourcesAsync(double Time);

	void OnResourcesLoaded(TSharedPtr<FStreamableHandle>* LoadedAsset);
};
