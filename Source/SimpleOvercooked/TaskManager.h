// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TaskManager.generated.h"

UCLASS()
class SIMPLEOVERCOOKED_API ATaskManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimatePawn")
		USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskManagement")
		TArray<FString> allTasks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskManagement")
		TArray<int32> taskIndexes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskManagement")
		int32 currentTask;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskManagement")
		TMap<FString, int32> ingredient2index;
};
