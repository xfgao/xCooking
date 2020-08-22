// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STAOG.h"
#include "Planner.h"
#include "BasePlanner.h"
#include "Planner2.h"
//#include "AIMethods.h"
//#include "TaskInfo.h" //alrealy included in STAOG.h
//#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Core/Public/Containers/Queue.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformFile.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/Math/TransformNonVectorized.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "GameFramework/Pawn.h"
#include "Runtime/RenderCore/Public/RenderCore.h"
#include "Runtime/Core/Public/Misc/DateTime.h"

#include "TaskPawn.generated.h"

#define GETENUMSTRING(etype, evalue) ( (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true) != nullptr) ? FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetEnumName((int32)evalue) : FString("Invalid - are you sure enum uses UENUM() macro?") )


struct FScenetoolLocation
{
		TArray<FVector2D> coordinates;

	FScenetoolLocation(TArray<FVector2D> t) {
		coordinates = t;
	}
};


struct Planner_state {
	int32 xpos;
	int32 ypos;
	int32 apple1_status;
	int32 apple2_status;
	int32 apple3_status;
	int32 bowl_status;
	int32 kind;
	int32 current_time;

	Planner_state(int32 x, int32 y, int32 apple1, int32 apple2, int32 apple3, int32 bowl, int32 time) {
		xpos = x;
		ypos = y;
		apple1_status = apple1;
		apple2_status = apple2;
		apple3_status = apple3;
		bowl_status = bowl;
		kind = 1;
		current_time = time;
	}

};



UCLASS()
class SIMPLEOVERCOOKED_API ATaskPawn : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	ATaskPawn();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	Planner_state state = Planner_state(0,0,0,0,0,0,0);
	TArray<FString> RobotPlannedNodeDescription;
	TArray<FString> HumanPlannedNodeDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explanation")
	int disagreeTimes;




	void resetPrior();
	BasePlanner *Planner;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explanation")
	FString explanationSubtaskPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explanation")
	FString explanationAtomicActionPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explanation")
	FString explanationSubtaskRobot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Explanation")
	FString explanationAtomicActionRobot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameName")
		FString GameName;

	

	TSharedPtr<FAOGNode> RobotNextNode;
	TSharedPtr<FAOGNode> HumanNextNode;

	TSharedPtr<FAOGNode> RobotCurrentSubTask;
	TSharedPtr<FAOGNode> HumanCurrentSubTask;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
	EItemType last_changed_item = EItemType::ITEM_NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
	EAbstractLocation last_changed_item_location = EAbstractLocation::UNKNOWN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
	ECOOKTYPE last_modified_player = ECOOKTYPE::NOBODY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		FString last_modified_item_name;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimatePawn") //Thread Lock, make sure that only one character is making change to this task manager(pawn);
		bool ThreadLock = false; //Important! Thread lock!

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimatePawn")
		UStaticMeshComponent* PawnMesh;

	//Task
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskManagement")
		TArray<FString> AllTasks;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskManagement")
		int32 currentTaskIndex;


	//UI
	TArray<TSharedPtr<TaskTree>> TaskTrees;//Relavent to task process 
	TSharedPtr<TaskTree> currentTaskTree;

	UFUNCTION(BlueprintCallable)
		void AddTaskTree(FString task_name);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskManagement")
		ECOOKGAMEMODE CookGameMode;

	UFUNCTION(BlueprintCallable)
		void SetCookGameMode(ECOOKGAMEMODE game_mode);

	UFUNCTION(BlueprintCallable)
		void ClearKitchenItems();

	void ClearSuggested(TSharedPtr<FAOGNode> currentNode);
	int findPlayerLocation();

	//Level Items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskManagement")
		int32 TaskTimeTick; //record time tick, each action increases one tick

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskManagement")
		TArray<FKitchenItem> LevelItems;

	TMap<FString, FString> FluentTable;


	UFUNCTION(BlueprintCallable) //Add new item to itemlist for record
		void AddNewKitchenItemToLevelItems(FString item_name, EItemType item_type, EAbstractLocation location, ECOOKTYPE cook_type = ECOOKTYPE::PLAYER);

	UFUNCTION(BlueprintCallable) //Delete item in itemlist
		void DeleteKitchenItemInLevelItems(FString item_name);

	UFUNCTION(BlueprintCallable) //Add to item attribute, e.g put a cut apple to a bowl
		void AddKitchenItemAttribute(FString parentName, FString attrName, ECOOKTYPE cook_type = ECOOKTYPE::PLAYER);

	UFUNCTION(BlueprintCallable) //Change item type
		void ChangeKitchenItemType(FString item_name, EItemType item_type, ECOOKTYPE cook_type = ECOOKTYPE::PLAYER);

	UFUNCTION(BlueprintCallable) //check item: whether it is an item required in the task
		bool CheckKitchenItemByName(FString item_name, FKitchenItem TaskItem);

	UFUNCTION(BlueprintCallable) //Remove item attributes
		void RemoveItemAttributes(FString item_name);

	UFUNCTION(BlueprintCallable) //Get item AI action control name(which is a string: e.g "green apple")
		FString GetPlannableNameForAI(FString item_name);

	UFUNCTION(BlueprintCallable) //Change item abstract location(e.g green apple: on hold)
		void ChangeItemAbstractLocation(FString item_name, EAbstractLocation a_location);


	//Suggestion Candidate
	TArray<TSharedPtr<FAOGNode>> SugguestionCandidates;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		FSuggestionForUI SuggestionForPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		FSuggestionForUI SuggestionForRobot;

	//UFUNCTION(BlueprintCallable)//Check suggestion for Robot
		//void CheckSuggestionForRobotFromSuggestionCandidates();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		FString suggestion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TArray<FString> AllowedQuestions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TArray<FString> PreparedAnswers;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		EUserMindLevel UserMindLevel = EUserMindLevel::TASK; //He/She is thinking about Task?Plan?Control?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		int32 UserMindDepth = 0; //How deep he/she is thinking?

	int32 MaxPlanDepth = 3; //maximum depth for usermind::plan
	int32 MaxControlDepth = 2; //maximum depth for usrmind::control


	//AI Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		bool AIbListening; //check whether AI is listening

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TQueue<TPair<EAIAction, FString>> AIActionPlan; //AI Action Plan: AIAction and Target

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		EAIAction AIAction; //give AI action instruction, idle/move/pickup/cut/...

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	//	FVector AITargetLocation; //give the target location only related to "move" instruction

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FString AITargetName; //give the target actor name only related to "move" instruction
;

	//Affordance map: Scene tools
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TaskManagement")
		TArray<FSCENETOOL> SceneTools; //Scenetools: give the target actor name only related to "move" instruction

	UFUNCTION(BlueprintCallable)
		void AddTool(FString display_name, ESCENETOOLTYPE tool_type, ECONTROLTYPE control_type, FString other_info = FString(""), int32 location_code = 0);

	UFUNCTION(BlueprintCallable)
		void ChangeToolOccupation(FString display_name, bool bOcuppied);

	//AI UI Pick up dropped Item to table
	UFUNCTION(BlueprintCallable)
		void PickUpItem2MiddleTable(FString item_name);

	//File system
	UFUNCTION(BlueprintCallable)
		bool VerifyOrCreateDirectory(const FString& TestDir) ;

	UFUNCTION(BlueprintCallable)
		bool WriteStringtoFile(const FString& RelativeDirectory, const FString& FileName, const FString& TextToSave);

	//Player Attention Prediction: Linear Regression
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attention")
		TArray<FVector> PlayerLocationArray;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attention")
		int32 PlayerLocationArray_MaxLength = 10;

	UFUNCTION(BlueprintCallable)
		void RecordPlayerLocation();

	UFUNCTION(BlueprintCallable) //Write player location vector to file
		void WritePlayerLocationArray2File(const FString& TargetActorClass);

	UFUNCTION(BlueprintCallable) // Logistic Regression: to predict what player is going to get(scenetool next)
		ESCENETOOLTYPE LogisticRegressionForPlayerLocationPrediction1_2();

	//Player Response Time Record
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attention")
	FDateTime SuggestionTime; //record the time when the system gives player suggestion

	UFUNCTION(BlueprintCallable)
		void SetSuggestionTime(); //set the time for suggestion

	UFUNCTION(BlueprintCallable)
		void LRecordResponseTime(); //write the suggestion time to file

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attention")
		bool RecordResponseTime; //Lock for whether to write suggestion and reponse time to file or not

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attention")
		TArray<int32> ResponseTimeRecordMinArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attention")
		TArray<int32> ResponseTimeRecordSecArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attention")
		TArray<int32> SuggestionTimeRecordMinArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attention")
		TArray<int32> SuggestionTimeRecordSecArray;


	bool planKitchen1();


	UFUNCTION(BlueprintCallable)
	bool actionPlanEmpty();

	UFUNCTION(BlueprintCallable)
		void clearAppleInJuicer();


	//UFUNCTION(BlueprintCallable)
	//bool Replan();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Attention")
	int suggestionFollowTimes = 0;

private:
	FString newFluent;
	FString changedItem;
	TMap<ESCENETOOLTYPE, FScenetoolLocation> scenetoolLocations;
	TArray<double> priors;
	TArray<double> subTaskPriors;

	FString currentLevel;

};
