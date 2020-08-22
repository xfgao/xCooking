// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Runtime/CoreUObject/Public/UObject/Object.h"
//#include "TaskInfo.h"

#include "STAOG.generated.h"


/**
 * 
 */
//class SIMPLEOVERCOOKED_API STAOG
//{
//public:
//	STAOG();
//	~STAOG();
//};

//USTRUCT()
//struct FJoyStruct
//{
//	GENERATED_BODY()
//
//	//Always make USTRUCT variables into UPROPERTY()
//	//    any non-UPROPERTY() struct vars are not replicated
//	
//	// So to simplify your life for later debugging, always use UPROPERTY()
//	UPROPERTY()
//	int32 SampleInt32;
//	
//};
//
struct FluentPrecondition {
	EItemType item_type;
	EAbstractLocation location;
	int requiredTimes;


	FluentPrecondition(EItemType type,
	EAbstractLocation loc,
	int t) {
		item_type = type;
		location = loc;
		requiredTimes = t;

	}

};


UENUM(BlueprintType)	
enum class ECOOKTYPE : uint8
{
	PLAYER 	UMETA(DisplayName = "PLAYER"),
	ROBOT 	UMETA(DisplayName = "ROBOT"),
	NOBODY 	UMETA(DisplayName = "NOBODY")
};

UENUM(BlueprintType)
enum class EUserMindLevel : uint8
{
	TASK 	UMETA(DisplayName = "TASK"),
	PLAN 	UMETA(DisplayName = "PLAN"),
	CONTROL 	UMETA(DisplayName = "CONTROL")
};


UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EAOGNodeType : uint8
{
	ROOT_NODE   UMETA(DisplayName = "ROOT"),
	OR_NODE 	UMETA(DisplayName = "OR"),
	AND_NODE 	UMETA(DisplayName = "AND"),
	TERMINAL_NODE	UMETA(DisplayName = "TERMINAL")
};

UENUM(BlueprintType)
enum class EItemType : uint8 {
	ITEM_NONE	UMETA(DisplayName = "None"),

	ITEM_HAMBERGER UMETA(DisplayName = "Hamberger"),
	ITEM_APPLE_GREEN	UMETA(DisplayName = "Apple(green)"),
	ITEM_SLICED_APPLE_GREEN	UMETA(DisplayName = "Sliced Apple(green)"),
	ITEM_JUICE_APPLE_GREEN	UMETA(DisplayName = "Apple(green) Juice"),


	ITEM_APPLE_RED	UMETA(DisplayName = "Apple(red)"),
	ITEM_SLICED_APPLE_RED	UMETA(DisplayName = "Sliced Apple(red)"),
	ITEM_JUICE_APPLE_RED	UMETA(DisplayName = "Apple(red) Juice"),

	ITEM_Cocunut	UMETA(DisplayName = "Coconut"),
	ITEM_SLICED_Cocunut	UMETA(DisplayName = "Sliced Coconut"),
	ITEM_JUICE_Coconut	UMETA(DisplayName = "Coconut Juice"),

	ITEM_BOWL UMETA(DisplayName = "Bowl"),
	ITEM_PLATE UMETA(DisplayName = "Plate"),


	ITEM_JUICE_CONTAINER  UMETA(DisplayName = "juice container"),

	ITEM_TOMATO UMETA(DisplayName = "Tomato"),
	ITEM_SLICED_TOMATO UMETA(DisplayName = "Sliced Tomato"),

	ITEM_MEAT UMETA(DisplayName = "Meat"),
	ITEM_SLICED_MEAT UMETA(DisplayName = "Sliced Meat"),
	ITEM_COOKED_MEAT UMETA(DisplayName = "Cooked Meat"),
	ITEM_COOKED_CUT_MEAT UMETA(DisplayName = "Cooked Cut Meat"),


	ITEM_LETTUCE UMETA(DisplayName = "Lettuce"),
	ITEM_SLICED_LETTUCE UMETA(DisplayName = "Sliced Lettuce"),

	ITEM_POT_CONTAINER UMETA(DisplayName = "Pot Container"),
	ITEM_BREAD UMETA(DisplayName = "Bread")
};


UENUM(BlueprintType)
enum class EAbstractLocation : uint8 {
	ON_TABLE UMETA(DisplayName = "On table"),
	ON_DELIVERY_BENCH UMETA(DisplayName = "On Delivery Bench"),
	IN_BASKET UMETA(DisplayName = "In Basket"),
	IN_CABINET UMETA(DisplayName = "In Cabinet"),
	ON_CUTBOARD UMETA(DisplayName = "On cutboard"),
	IN_JUCIER UMETA(DisplayName = "In jucier"),
	BE_HOLD UMETA(DisplayName = "Be holding"),
	IN_BOWL UMETA(DisplayName = "In bowl"),
	ON_PLATE UMETA(DisplayName = "On Plate"),
	ON_PAN UMETA(DisplayName = "On Pan"),

	UNKNOWN UMETA(DisplayName = "Unknown"),
	ANY UMETA(DisplayName = "ANY"),
};

/**
 *Task Information Script: AI CONTROL and Human Robot Interaction
 */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EAIAction : uint8
{
	IDLE 	UMETA(DisplayName = "IDLE"),
	LOOK_AT UMETA(DisplayName = "LOOK AT"),
	MOVE_TO 	UMETA(DisplayName = "MOVE TO"),
	PICK_UP_DROP	UMETA(DisplayName = "PICK UP / DROP"),
	INSPECT UMETA(DisplayName = "INSPECT")
};

//Tools in scence, e.g cutboard, juicer, microwave,...
UENUM(BlueprintType)
enum class ESCENETOOLTYPE : uint8
{
	BASKET	UMETA(DisplayName = "BASKET"),
	JUICER	UMETA(DisplayName = "JUICER"),
	CUTBOARD	UMETA(DisplayName = "CUTBOARD"),
	CABINET	   UMETA(DisplayName = "CABINET"),
	SENDER	UMETA(DisplayName = "SENDER"),
	TRASHBIN UMETA(DisplayName = "TRASH BIN"),
	TABLE  UMETA(DisplayName = "TABLE"),
	PAN UMETA(DisplayName = "PAN"),
	UNKNOWN UMETA(DisplayName = "UNKNOWN")
};

USTRUCT(BlueprintType)
struct FKitchenItem {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		FString item_name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		EItemType item_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		TArray<EItemType> item_attributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		FTransform item_transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		EAbstractLocation location_abstract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		EAbstractLocation previous_abstract_location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		int32 last_modification_time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Struct")
		ECOOKTYPE last_modification_cook_type;

	bool usedForCompletionCriterion;


	bool IsAnExampleOf(FKitchenItem& anotherItem) {
		if(this->item_type != anotherItem.item_type)
			return false;
		
		int32 attribute_length = this->item_attributes.Num();

		//UE_LOG(LogTemp, Warning, TEXT("STAOG: %s"), *FString::FromInt(attribute_length));
		//UE_LOG(LogTemp, Warning, TEXT("STAOG: %s"), *FString::FromInt(anotherItem.item_attributes.Num()));


		if (attribute_length != anotherItem.item_attributes.Num())
			return false;

		
		//Compare item attributes are the same
		TArray<bool> occupations; //to record the matching instance postions
		occupations.Init(false, attribute_length);
		for (int32 i = 0; i < attribute_length; ++i) {
			bool found_index = false;
			for (int32 j = 0; j < attribute_length; ++j) {
				if ((occupations[j] == false) && (anotherItem.item_attributes[j] == this->item_attributes[i])) {
					occupations[j] = true;
					found_index = true;
					break;
				}
			}
			if (found_index == false)
				return false;
		}
		return true;
	}
};

//USTRUCT(BlueprintType)
struct FAOGNode {

	//GENERATED_USTRUCT_BODY()

	//NAME and Description
	FString node_name;
	FString description;
	int32 node_id;
	EAOGNodeType node_type;

	//Condition
	bool is_completed;
	bool put_into_plan;
	bool is_casual;
	FString causal_how;

	int32 required_times = 1;
	int32 available_times = 0;


	//Competion criteria
	TArray<FKitchenItem> item_lists; //??????????????????

	//used for detecting fluentChanges at the terminal node
	//an array of 4 items (old itemType, new itemType, old location, new location )
	TArray<int8> fluentChanges;

	TArray<FluentPrecondition> fluentPreconditions;

	//Connection
	TArray<TSharedPtr<FAOGNode>> children;
	TArray<TSharedPtr<FAOGNode>> parents;
	TArray<TSharedPtr<FAOGNode>> preconditions;
	TArray<TPair<EItemType, EAbstractLocation>> completionCriterion;
	bool suggested;
	int suggestedTime = 0;

	//Time
	int32 completion_time; //when completed
	ECOOKTYPE completion_cook; //who completed:AI or human

	//AI PLAN: Action2Class: e.g. Move to: BP_apple
	TArray<TPair<EAIAction, FString>> AOG_Action_Plan;
	ECOOKTYPE Planer; //who is in charge of this task preferred, AI or Player

	void AddActionPair(EAIAction action, FString target) {
		AOG_Action_Plan.Add(TPair<EAIAction, FString>(action, target));
	}

	

	void setFluentChanges(FString itemName, int8 old_itemType, int8 new_itemType, int8 old_location, int8 new_location) {
		
		fluentChanges.Empty();
		fluentChanges.Add(old_itemType);
		fluentChanges.Add(new_itemType);
		fluentChanges.Add(old_location);
		fluentChanges.Add(new_location);
	}

	//For Player Attention Prediction
	TArray<ESCENETOOLTYPE> valid_scenetools;


	//Constructor
	FAOGNode() {};

	FAOGNode(FString name, FString des, int32 id, EAOGNodeType type, bool bCompleted = false, bool bCausal = false) {
		node_name = name;
		description = des;
		node_id = id;
		node_type = type;
		is_completed = bCompleted;
		is_casual = bCausal;
		put_into_plan = false;
		suggested = false;
	}

	FAOGNode(EAOGNodeType dummy_type) {
		node_type = dummy_type;
	}


	void AddChild(TSharedPtr<FAOGNode> child) {
		children.Add(child);
	}

	void AddParent(TSharedPtr<FAOGNode> parent) {
		parents.Add(parent);
	}

	void AddCriterion(FKitchenItem item) {
		item_lists.Add(item);
	}

	//void SetCompleted(bool bCompleted) {
	//	is_completed = bCompleted;
	//}
};

class TaskTree
{
public:
	FString TaskName; //Task name
	TArray<TSharedPtr<FAOGNode> > subTasks;
	TSharedPtr<FAOGNode> RobotRootNode; //Root Node of task tree
	TSharedPtr<FAOGNode> HumanRootNode;
	

	TSharedPtr<FAOGNode> FinishNode; //Root Node of task finishing

	TaskTree();
	TaskTree(FString task);

	TArray<FString> TaskDescriptions; //Task descriptions with 3 depths
};


//UI Task Instructions types: what kind of suggestions to give 
UENUM(BlueprintType)
enum class EINSTRUCTIONTYPE : uint8
{
	SHOW_TASK_INSTRUCTION 	UMETA(DisplayName = "show task instruction"),
	SHOW_CONTROL_MAP 	UMETA(DisplayName = "show control map"),
	SHOW_AFFORDANCE_MAP  UMETA(DisplayName = "show affordance map"),
	SHOW_AOG_PLANNING_MAP  UMETA(DisplayName = "show AOG planning map"),
	SHOW_AOG_PLANNING_PATH  UMETA(DisplayName = "show AOG planning path"),	
	SHOW_IMMEDIATE_SUGGESTION  UMETA(DisplayName = "show immediate suggestion")
};

//Game Mode: Work together in turn of work at the same time
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ECOOKGAMEMODE : uint8
{
	IN_TURN 	UMETA(DisplayName = "WORK IN TURN"),
	TOGETHER UMETA(DisplayName = "WORK TOGETHER")
};

//Operation/Pickup drop
UENUM(BlueprintType)
enum class ECONTROLTYPE : uint8
{
	PICKUPDROP	UMETA(DisplayName = "PICKUP DROP"),
	OPERATE	UMETA(DisplayName = "OPERATE")
};

USTRUCT(BlueprintType)
struct FSCENETOOL {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Struct")
		FString tool_name; //Display Name from Blueprint!!!! GetActorLable()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Struct")
		FString tool_description; //Description

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Struct")
		ESCENETOOLTYPE tool_type; //tool type

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Struct")
		ECONTROLTYPE control_type; //

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Struct")
		int32 location_code; //location id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Struct")
		FString other_information; //other information

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Struct")
		bool is_occupied = false; //for table only

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tool Struct")
		EItemType occupied_item;

	//Constructor
	//FSCENETOOL() {};
	//FSCENETOOL(FString tool_name, ESCENETOOLTYPE tool_type, ECONTROLTYPE control_type, int32 location_code = 0) {
	//	tool_name = tool_name;
	//	tool_type = tool_type;
	//	control_type = control_type;
	//	location_code = location_code;
	//}

};

USTRUCT(BlueprintType)
struct FSceneToolInfo
{
	GENERATED_USTRUCT_BODY()

		FSceneToolInfo() {};

	//UPROPERTY(EditAnywhere, Category = "Scene Tool")
	TArray<TSharedPtr<FSCENETOOL>> AllTools;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Tool")
		FString sceneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Tool")
		TArray<FSCENETOOL> Baskets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Tool")
		TArray<FSCENETOOL> Juicers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Tool")
		TArray<FSCENETOOL> Cutboards;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Tool")
		TArray<FSCENETOOL> Cabinets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Tool")
		TArray<FSCENETOOL> Senders;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Tool")
		TArray<FSCENETOOL> Trashbins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scene Tool")
		TArray<FSCENETOOL> Tables;

};

//Suggestion for 1-2 Task-Question-Answering UI
USTRUCT(BlueprintType)
struct FSuggestionForUI
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suggestion Struct")
		ECOOKTYPE cook_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suggestion Struct")
		TMap<FString, int32> InstructionFoldMap; //record how many time it has been the same, if still in this map, show
	//suggestion for the user to give them suggestions: Node_id->Fold

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suggestion Struct")
		TMap<FString, int32> InstructionTimesMap; //record how many time it has been the same, if still in this map, show
	//Node_id->Times

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suggestion Struct")
		int32 DuplicatedTimes = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suggestion Struct")
		TArray<ESCENETOOLTYPE> PossibleSceneTools;
};