// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskPawn.h"
#include <cmath>
#include <algorithm>
//#include "Runtime/Engine/Classes/GameFramework/Actor.h"

void printPreCon(TSharedPtr<FAOGNode> currentNode) {
	for (int i = 0; i < currentNode->preconditions.Num(); i++)
		UE_LOG(LogTemp, Warning, TEXT("node Description precondtion: %s"), *currentNode->preconditions[i]->description);
}
// for debug only





void ATaskPawn::ClearSuggested(TSharedPtr<FAOGNode> currentNode) {
	if (currentNode->node_type == EAOGNodeType::TERMINAL_NODE) {
		currentNode->suggested = false;
		return;
	}

	for (auto it : currentNode->children) {
		ClearSuggested(it);
	}
	currentNode->suggested = false;
}

// Sets default values
ATaskPawn::ATaskPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PawnMesh"));
	
	suggestion = FString("Hello, Welcome to VRKItchen Overcooked mode!");
}

// Called when the game starts or when spawned
void ATaskPawn::BeginPlay()
{
	Super::BeginPlay();

	TaskTimeTick = 0;
	disagreeTimes = 0;
	suggestionFollowTimes = 0;

	//Set SuggestionForPlayer/Robot information UI
	SuggestionForPlayer.cook_type = ECOOKTYPE::PLAYER;
	SuggestionForRobot.cook_type = ECOOKTYPE::ROBOT;

	//Recorder for play location, repeatly record every 0.15 second
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ATaskPawn::RecordPlayerLocation, 0.1f, true);

	//Set a random game name
	for (int32 i = 0; i < 10; ++i)
		GameName.Append(FString::FromInt(FMath::RandRange(0, 9)));

	currentLevel = GetWorld()->GetName();
	if (currentLevel == "Kitchen1") {
		UE_LOG(LogTemp, Error, TEXT("using palnner1"));
		AddTaskTree("Green Apple Juice");
		scenetoolLocations.Add(ESCENETOOLTYPE::BASKET, FScenetoolLocation(TArray<FVector2D> { FVector2D(500.0, -600.0) }));
		scenetoolLocations.Add(ESCENETOOLTYPE::JUICER, FScenetoolLocation(TArray<FVector2D>{FVector2D(320.0, 150.0)}));
		scenetoolLocations.Add(ESCENETOOLTYPE::CUTBOARD, FScenetoolLocation(TArray<FVector2D> { FVector2D(-125.0, -75.0), FVector2D(-125.0, -250.0) }));
		scenetoolLocations.Add(ESCENETOOLTYPE::CABINET, FScenetoolLocation(TArray<FVector2D> { FVector2D(10.0, 360.0) }));
		scenetoolLocations.Add(ESCENETOOLTYPE::SENDER, FScenetoolLocation(TArray<FVector2D>{FVector2D(-110.0, -370.0), FVector2D(-70.0, -360.0), FVector2D(-100.0, -350.0) }));
		scenetoolLocations.Add(ESCENETOOLTYPE::TRASHBIN, FScenetoolLocation(TArray<FVector2D>{}));
		/*scenetoolLocations.Add(ESCENETOOLTYPE::TABLE, FScenetoolLocation(TArray<FVector2D>{
			FVector2D(10.0, -170.0), FVector2D(10.0, 50.0), FVector2D(10.0, 160.0), FVector2D(10.0, 260.0), FVector2D(10.0, 360.0) }));*/
		scenetoolLocations.Add(ESCENETOOLTYPE::TABLE, FScenetoolLocation(TArray<FVector2D>{ FVector2D(30.0, -60.0) }));
		//scenetoolLocations.Add(ESCENETOOLTYPE::TABLE, FScenetoolLocation(TArray<FVector2D>{
			//FVector2D(10.0, -170.0), FVector2D(10.0, 50.0), FVector2D(10.0, 160.0), FVector2D(10.0, 260.0), FVector2D(10.0, 360.0) }));
		
		scenetoolLocations.Add(ESCENETOOLTYPE::PAN, FScenetoolLocation(TArray<FVector2D>{}));

		Planner = new APlanner1();
		double N = currentTaskTree->subTasks.Num();
		subTaskPriors.Init( 1.0/N , N);
		
	}
	else if (currentLevel == "Kitchen2") {
		UE_LOG(LogTemp, Error, TEXT("using palnner2"));
		AddTaskTree("Burger");
		Planner = new APlanner2();
	}

	
	
	
}


void ATaskPawn::clearAppleInJuicer() {
	bool flag = true;
	while (flag) {
		flag = false;
		for (int i = LevelItems.Num() - 1; i >= 0; i--) {
			if (LevelItems[i].item_type == EItemType::ITEM_SLICED_APPLE_GREEN && LevelItems[i].location_abstract == EAbstractLocation::IN_JUCIER) {
				LevelItems.RemoveAt(i);
				flag = true;
				break;
			}
		}
	}
}



void ATaskPawn::resetPrior() {
	priors.SetNum(10, true);
	priors.Init(0.1, 10.0);
	if (currentLevel == "Kitchen1") {
		priors[(int8)ESCENETOOLTYPE::BASKET] = 1.0 / 7.0;
		priors[(int8)ESCENETOOLTYPE::JUICER] = 1.0 / 7.0;
		priors[(int8)ESCENETOOLTYPE::CUTBOARD] = 1.0 / 7.0;
		priors[(int8)ESCENETOOLTYPE::CABINET] = 1.0 / 7.0;
		priors[(int8)ESCENETOOLTYPE::SENDER] = 1.0 / 7.0;
		priors[(int8)ESCENETOOLTYPE::TRASHBIN] = 0.0 / 7.0;
		priors[(int8)ESCENETOOLTYPE::TABLE] = 1.0 / 7.0;
		priors[(int8)ESCENETOOLTYPE::PAN] = 0.0 / 7.0;
		priors[(int8)ESCENETOOLTYPE::UNKNOWN] = 1.0 / 7.0;
	}

}

// Called every frame
void ATaskPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ATaskPawn::ClearKitchenItems() {
	LevelItems.Empty();
}

// Called to bind functionality to input
void ATaskPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ATaskPawn::AddTaskTree(FString task_name)
{
	TaskTrees.Add(TSharedPtr<TaskTree>(new TaskTree(task_name)));
	currentTaskTree = TaskTrees[TaskTrees.Num()-1];
}

void ATaskPawn::SetCookGameMode(ECOOKGAMEMODE game_mode)
{
	CookGameMode = game_mode;
}

void ATaskPawn::AddNewKitchenItemToLevelItems(FString item_name, EItemType item_type, EAbstractLocation location, ECOOKTYPE cook_type)
{
	FKitchenItem NewItem;
	NewItem.item_name = item_name;
	NewItem.item_type = item_type;
	NewItem.last_modification_time = TaskTimeTick++;
	NewItem.last_modification_cook_type = cook_type;
	NewItem.location_abstract = location;
	LevelItems.Add(NewItem);

	//Record Player Responed Time From Suggestion
	LRecordResponseTime();
}

void ATaskPawn::AddKitchenItemAttribute(FString parentName, FString attrName, ECOOKTYPE cook_type)
{
	int32 attrIndex = 0;
	int32 parentIndex = 0;

	for (int32 i = 0; i < LevelItems.Num(); ++i) {
		if (LevelItems[i].item_name.Equals(parentName)) {
			parentIndex = i;
		}
		if (LevelItems[i].item_name.Equals(attrName)) {
			attrIndex = i;
		}
	}
	LevelItems[parentIndex].item_attributes.Add(LevelItems[attrIndex].item_type);
	LevelItems[parentIndex].last_modification_time = TaskTimeTick++;
	LevelItems[parentIndex].last_modification_cook_type = cook_type;
	LRecordResponseTime();
}

void ATaskPawn::ChangeKitchenItemType(FString item_name, EItemType item_type, ECOOKTYPE cook_type)
{
	for (int32 i = 0; i < LevelItems.Num(); ++i) {
		if (LevelItems[i].item_name == item_name) {
			LevelItems[i].item_type = item_type;
			LevelItems[i].last_modification_cook_type = cook_type;
			LevelItems[i].last_modification_time = TaskTimeTick++;
			LevelItems[i].last_modification_cook_type = cook_type;
			return;
		}
	}

	LRecordResponseTime();
}

bool ATaskPawn::CheckKitchenItemByName(FString item_name, FKitchenItem TaskItem)
{
	for (int32 i = 0; i < LevelItems.Num(); ++i) {
		if (TaskItem.IsAnExampleOf(LevelItems[i]) && LevelItems[i].item_name.Equals(item_name)) {
			return true;
		}
	}
	return false;
}

void ATaskPawn::RemoveItemAttributes(FString item_name)
{
	for (int32 i = 0; i < LevelItems.Num(); ++i) {
		if (LevelItems[i].item_name == item_name) {
			LevelItems[i].item_attributes.Empty();
		}
	}
}

int ATaskPawn::findPlayerLocation() {
	FVector location =  PlayerLocationArray[PlayerLocationArray.Num() - 1];
	FVector2D location2D = FVector2D(location);
	int miniIndex = -1;
	double miniDistance = 100000000000;
	for (int i = 0; i < (int)ESCENETOOLTYPE::UNKNOWN; i++) {
		for (int j = 0; j < scenetoolLocations[(ESCENETOOLTYPE)i].coordinates.Num(); j++) {
			double d = FVector2D::Distance(scenetoolLocations[(ESCENETOOLTYPE)i].coordinates[j], location2D);
			if ( miniIndex == -1 || d < miniDistance) { 
				miniDistance = d;
				miniIndex = i;
			}
			
		}
	}
	return miniIndex;
}



FString ATaskPawn::GetPlannableNameForAI(FString item_name)
{
	for (int32 i = 0; i < LevelItems.Num(); ++i) {
		if (LevelItems[i].item_name == item_name) {
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(item_name));
			if (LevelItems[i].item_type == EItemType::ITEM_APPLE_GREEN) {
				return FString("green apple");
			}
			else if (LevelItems[i].item_type == EItemType::ITEM_SLICED_APPLE_GREEN) {
				return FString("sliced green apple");
			}
			else if (LevelItems[i].item_type == EItemType::ITEM_BOWL) {
				FString answer("bowl");
				for (int32 j = 0; j < LevelItems[i].item_attributes.Num(); ++j) {
					if (LevelItems[i].item_attributes[j] == EItemType::ITEM_JUICE_APPLE_GREEN)
						answer.Append(FString(" green apple juice"));
					//UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(answer));
				}
				return answer;
			}
		}
	}

	for (int32 i = 0; i < SceneTools.Num(); ++i) {
		if (SceneTools[i].tool_name == item_name) {

			if (SceneTools[i].tool_type == ESCENETOOLTYPE::BASKET) {
				return FString("a basket");
			}
			else if (SceneTools[i].tool_type == ESCENETOOLTYPE::TABLE) {
				return FString("a table");
			}
			else if (SceneTools[i].tool_type == ESCENETOOLTYPE::JUICER) {
				return FString("the juicer");
			}
			else if (SceneTools[i].tool_type == ESCENETOOLTYPE::CUTBOARD) {
				return FString("the cutboard");
			}
			else if (SceneTools[i].tool_type == ESCENETOOLTYPE::SENDER) {
				return FString("the sender");
			}
		}
	}
	return FString();
}

void ATaskPawn::ChangeItemAbstractLocation(FString item_name, EAbstractLocation a_location) {
	for (int32 i = 0; i < LevelItems.Num(); ++i) {
		if (LevelItems[i].item_name == item_name) {
			LevelItems[i].previous_abstract_location = LevelItems[i].location_abstract;
			LevelItems[i].location_abstract = a_location;
		}
	}
}

void ATaskPawn::DeleteKitchenItemInLevelItems(FString item_name)
{
	int32 delete_index = -1;
	for (int32 i = 0; i < LevelItems.Num(); ++i) {
		if (LevelItems[i].item_name == item_name) {
			delete_index = i;		
			break;
		}
	}
	if(delete_index != -1)
		LevelItems.RemoveAt(delete_index);
	TaskTimeTick++;

	//Record Player Responed Time From Suggestion
	LRecordResponseTime();
}	




bool ATaskPawn::planKitchen1() {

	TArray<TPair<EAIAction, FString>> PlanSequence;
	bool ValidSequence = true;
	TArray<FString> ValidTargets;
	//if (RobotNextNode->AOG_Action_Plan.Num() == 0)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("EmptyAOGPlan "));
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("NonEmptyAOGPlan "));
	//}
	UE_LOG(LogTemp, Error, TEXT("%s"), *RobotNextNode->description);
	for (int k = 0; k < RobotNextNode->AOG_Action_Plan.Num(); k++) {
		TPair<EAIAction, FString> current_plan = RobotNextNode->AOG_Action_Plan[k];
		//UE_LOG(LogTemp, Warning, TEXT("Robot Node item %s"), *GETENUMSTRING("EAIAction", current_plan.Key));
		//UE_LOG(LogTemp, Warning, TEXT("Human Node item %s"),*current_plan.Value);
		if (current_plan.Key == EAIAction::IDLE) {
			AIActionPlan.Enqueue(current_plan);
		}
		else if (current_plan.Key == EAIAction::MOVE_TO) {
			FString current_target_name;
			if (current_plan.Value.Equals(FString("green apple basket"))) {

				for (int32 j = 0; j < SceneTools.Num(); ++j) {
					//must have a basket with green apple
					if (SceneTools[j].tool_type == ESCENETOOLTYPE::BASKET && SceneTools[j].other_information == "green apple") {
						current_target_name = SceneTools[j].tool_name;
						//UE_LOG(LogTemp, Warning, TEXT("goto green apple!"));
					}
				}

			}
			else if (current_plan.Value.Equals(FString("middle table"))) {
				for (int32 j = 0; j < SceneTools.Num(); ++j) {
					//must have a basket with green apple
					if (SceneTools[j].tool_type == ESCENETOOLTYPE::TABLE && SceneTools[j].is_occupied == false) {
						//Get multiple targets
						if (ValidTargets.Contains(SceneTools[j].tool_name)) {
							continue;
						}
						current_target_name = SceneTools[j].tool_name;
						ValidTargets.Add(current_target_name);
						//UE_LOG(LogTemp, Warning, TEXT("UpdateAIAction: updating AI Target middle table%s"), *FString(current_target_name));
						break;
					}
				}
			}
			else if (current_plan.Value.Equals(FString("cutboard"))) {
				for (int32 j = 0; j < SceneTools.Num(); ++j) {
					//must have a basket with green apple
					if (SceneTools[j].tool_type == ESCENETOOLTYPE::CUTBOARD && SceneTools[j].is_occupied == false) {
						//Get multiple targets
						if (ValidTargets.Contains(SceneTools[j].tool_name)) {
							continue;
						}
						current_target_name = SceneTools[j].tool_name;
						ValidTargets.Add(current_target_name);
						//UE_LOG(LogTemp, Warning, TEXT("UpdateAIAction: updating AI Target cutboard%s"), *FString(current_target_name));
						break;
					}
				}
			}
			else if (current_plan.Value.Equals(FString("juicer"))) {
				for (int32 j = 0; j < SceneTools.Num(); ++j) {
					//must have a basket with green apple
					if (SceneTools[j].tool_type == ESCENETOOLTYPE::JUICER) {
						//Get multiple targets
						current_target_name = SceneTools[j].tool_name;
						ValidTargets.Add(current_target_name);
						//UE_LOG(LogTemp, Warning, TEXT("UpdateAIAction: updating AI Target Juicer%s"), *FString(current_target_name));
						break;
					}
				}
			}
			else if (current_plan.Value.Equals(FString("sender"))) {
				for (int32 j = 0; j < SceneTools.Num(); ++j) {
					//must have a basket with green apple
					if (SceneTools[j].tool_type == ESCENETOOLTYPE::SENDER) {
						//Get multiple targets
						current_target_name = SceneTools[j].tool_name;
						break;
					}
				}
			}
			else if (current_plan.Value.Equals(FString("cabinet"))) {
				for (int32 j = 0; j < SceneTools.Num(); ++j) {
					//must have a basket with green apple
					if (SceneTools[j].tool_type == ESCENETOOLTYPE::CABINET) {
						//Get multiple targets
						current_target_name = SceneTools[j].tool_name;
						break;
					}
				}
			}
			else if (current_plan.Value.Equals(FString("sliced green apple"))) {
				for (int32 j = 0; j < LevelItems.Num(); ++j) {
					//BE HOLD need to be added in blueprint
					if (LevelItems[j].item_type == EItemType::ITEM_SLICED_APPLE_GREEN) {
						if ((CookGameMode == ECOOKGAMEMODE::IN_TURN && LevelItems[j].location_abstract != EAbstractLocation::BE_HOLD)
							|| (CookGameMode == ECOOKGAMEMODE::TOGETHER && LevelItems[j].location_abstract == EAbstractLocation::ON_TABLE)) {
							current_target_name = LevelItems[j].item_name;
							ValidTargets.Add(current_target_name);
							break;
						}
					}
				}
			}
			else if (current_plan.Value.Equals(FString("green apple"))) {
				for (int32 j = 0; j < LevelItems.Num(); ++j) {
					//BE HOLD need to be added in blueprint
					if (LevelItems[j].item_type == EItemType::ITEM_APPLE_GREEN && LevelItems[j].location_abstract != EAbstractLocation::BE_HOLD) {
						current_target_name = LevelItems[j].item_name;
						ValidTargets.Add(current_target_name);
						//UE_LOG(LogTemp, Warning, TEXT("green apple"));
						break;
					}
				}
			}
			else if (current_plan.Value.Equals(FString("bowl"))) {
				for (int32 j = 0; j < LevelItems.Num(); ++j) {
					//BE HOLD need to be added in blueprint
					if (LevelItems[j].item_type == EItemType::ITEM_BOWL && LevelItems[j].item_attributes.Num() == 0) {
						if ((CookGameMode == ECOOKGAMEMODE::IN_TURN && LevelItems[j].location_abstract == EAbstractLocation::ON_TABLE)
							|| (CookGameMode == ECOOKGAMEMODE::TOGETHER && LevelItems[j].location_abstract == EAbstractLocation::ON_TABLE)) {
							current_target_name = LevelItems[j].item_name;
							ValidTargets.Add(current_target_name);
							break;
						}
					}
				}
			}
			else if (current_plan.Value.Equals(FString("bowl green apple juice"))) {
				for (int32 j = 0; j < LevelItems.Num(); ++j) {
					//BE HOLD need to be added in blueprint
					if (LevelItems[j].item_type == EItemType::ITEM_BOWL && LevelItems[j].item_attributes.Num() > 0) {
						if (LevelItems[j].item_attributes[0] == EItemType::ITEM_JUICE_APPLE_GREEN) {
							current_target_name = LevelItems[j].item_name;
							ValidTargets.Add(current_target_name);
							break;
						}
					}
				}
			}
			//UE_LOG(LogTemp, Warning, TEXT("Affordance map wrong!!!!!!!!!!!!!! %s"), *FString(EnumToString(FString("EAIAction"), AIAction)));
			//if no target found
			if (current_target_name.IsEmpty()) {

				ValidSequence = false;
				break;
			}
			PlanSequence.Emplace(TPair<EAIAction, FString>(EAIAction::MOVE_TO, current_target_name));
		}
		else if (current_plan.Key == EAIAction::PICK_UP_DROP) {
			PlanSequence.Add(current_plan);

		}
		else if (current_plan.Key == EAIAction::INSPECT) {
			PlanSequence.Add(current_plan);

		}

	}

	//If this task can be planned by Plan Sequence
	if (ValidSequence) {

		for (int32 j = 0; j < PlanSequence.Num(); ++j) {
			AIActionPlan.Enqueue(PlanSequence[j]);
		}

		RobotNextNode->put_into_plan = true;
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("not valid sequence"));
		return false;
	}

	return true;
}







void ATaskPawn::AddTool(FString display_name, ESCENETOOLTYPE tool_type, ECONTROLTYPE control_type, FString other_info, int32 location_code)
{
	FSCENETOOL tool;
	tool.tool_name = display_name;
	tool.tool_type = tool_type;
	tool.control_type = control_type;
	tool.other_information = other_info;
	tool.location_code = location_code;
	SceneTools.Emplace(tool);
}

void ATaskPawn::ChangeToolOccupation(FString display_name, bool bOcuppied)
{
	for (int32 i = 0; i < SceneTools.Num(); ++i) {
		if (SceneTools[i].tool_name == display_name) {
			//bUE_LOG(LogTemp, Warning, TEXT("Change !!!!!!!!!! Occu!!!!!!!!!!!!!!!!!!!!!! %s"), *FString(display_name));
			SceneTools[i].is_occupied = bOcuppied;
		}
	}
}

bool ATaskPawn::actionPlanEmpty() {
	return AIActionPlan.IsEmpty();
}

void ATaskPawn::PickUpItem2MiddleTable(FString item_name)
{
	ThreadLock = true;
	TArray<TPair<EAIAction, FString>> PlanSequence;
	PlanSequence.Add(TPair<EAIAction, FString>(EAIAction::MOVE_TO, item_name));
	PlanSequence.Add(TPair<EAIAction, FString>(EAIAction::PICK_UP_DROP, GetPlannableNameForAI(item_name)));

	bool has_empty_table = false;
	for (int32 j = 0; j < SceneTools.Num(); ++j) {
		//must have a basket with green apple
		if (SceneTools[j].tool_type == ESCENETOOLTYPE::TABLE && SceneTools[j].is_occupied == false) {
			has_empty_table = true;
			PlanSequence.Add(TPair<EAIAction, FString>(EAIAction::MOVE_TO, SceneTools[j].tool_name));
			//UE_LOG(LogTemp, Warning, TEXT("PickUpItem2MiddleTable !!!!!! %s"), *FString(SceneTools[j].tool_name));
			break;
		}
	}
	if (!has_empty_table) {
		ThreadLock = false;
		return;
	}
	PlanSequence.Add(TPair<EAIAction, FString>(EAIAction::PICK_UP_DROP, FString()));
	TPair<EAIAction, FString> next_action_target;

	for (int32 j = 0; j < PlanSequence.Num(); ++j) {	
		AIActionPlan.Enqueue(PlanSequence[j]);
		UE_LOG(LogTemp, Warning, TEXT("Put in plan"));
	}

	AIActionPlan.Peek(next_action_target);
	AIAction = next_action_target.Key;
	AITargetName = next_action_target.Value;
	ThreadLock = false;
	return;
}

bool ATaskPawn::VerifyOrCreateDirectory(const FString & TestDir)
{
	// Every function call, unless the function is inline, adds a small
// overhead which we can avoid by creating a local variable like so.
// But beware of making every function inline!

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	FString CheckDir = FPaths::ProjectContentDir() + "/" + TestDir;

	// Directory Exists?
	if (!PlatformFile.DirectoryExists(*CheckDir))
	{
		PlatformFile.CreateDirectory(*CheckDir);

		if (!PlatformFile.DirectoryExists(*CheckDir))
		{
			return false;
			//~~~~~~~~~~~~~~
		}
	}
	return true;
}

bool ATaskPawn::WriteStringtoFile(const FString& RelativeDirectory, const FString & FileName, const FString & TextToSave)
{
	bool AllowOverwriting = false;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	FString SaveDirectory = FPaths::ProjectContentDir() + "/" + RelativeDirectory;

	//UE_LOG(LogTemp, Warning, TEXT("Game over save %s"), *FString(SaveDirectory));


	// CreateDirectoryTree returns true if the destination
	// directory existed prior to call or has been created
	// during the call.
	if (PlatformFile.CreateDirectoryTree(*SaveDirectory))
	{
		// Get absolute file path
		FString AbsoluteFilePath = SaveDirectory + "/" + FileName;

		// Allow overwriting or file doesn't already exist
		//if (AllowOverwriting || !PlatformFile.FileExists(*AbsoluteFilePath))
		//{
			FFileHelper::SaveStringToFile(TextToSave, *AbsoluteFilePath, FFileHelper::EEncodingOptions::AutoDetect,
				&IFileManager::Get(), EFileWrite::FILEWRITE_Append);
			return true;
		//}
	}
	return false;
}

void ATaskPawn::RecordPlayerLocation()
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerLocationArray.Add(myCharacter->GetActorLocation());

	if (PlayerLocationArray.Num() > PlayerLocationArray_MaxLength) {
		PlayerLocationArray.RemoveAt(0);
	}
}

void ATaskPawn::WritePlayerLocationArray2File(const FString& TargetActorClass)
{
	const FString RelativeDirectory("PlayerRecords");
	FString FileName("Location_Record_");
	FileName.Append(GameName);
	FileName.Append(".txt");

	FString TextString("");
	for (auto& vector : PlayerLocationArray) {
		TextString.Append(FString::SanitizeFloat(vector.X) + ",");
		TextString.Append(FString::SanitizeFloat(vector.Y) + ",");
	}
	TextString.Append(TargetActorClass);
	TextString.Append("\n");

	VerifyOrCreateDirectory(RelativeDirectory);
	WriteStringtoFile(RelativeDirectory, FileName, TextString);
}

ESCENETOOLTYPE ATaskPawn::LogisticRegressionForPlayerLocationPrediction1_2()
{

	static const TArray<float> v0 = { 0.00770387,  0.00218314, -0.01661217,  0.00298352, -0.00219161,
		-0.02005762,  0.00402867,  0.02519479,  0.00435388,  0.00275955,
		-0.00480834,  0.0032804 , -0.01691159, -0.02281635, -0.00879496,
		 0.0123305 , -0.02542779,  0.01434533,  0.08551638, -0.0201368 };

	static const TArray<float> v1 = { 0.00293369, -0.00445558,  0.01156788,  0.0037544 , -0.0068742 ,
		 0.00635001,  0.00158256,  0.00053681, -0.0017034 , -0.01899333,
		-0.02450427,  0.00657068,  0.01072418,  0.00746389,  0.01304591,
		-0.00661206,  0.0356206 , -0.00926744, -0.0178086 ,  0.02079913 };

	static const TArray<float> v2 = { 0.01169005, -0.00353247, -0.01808944,  0.00837355,  0.01324141,
		-0.01285798,  0.02478394,  0.00407167, -0.0051491 ,  0.01621025,
		-0.02012969, -0.00781178,  0.00363734, -0.01449219,  0.01613673,
		 0.01537146,  0.0067195 ,  0.00010758, -0.02240324, -0.01242975 };

	static const TArray<float> v3 = { -0.00235862,  0.01456304,  0.00033475, -0.02283328, -0.00296364,
		 0.00358182, -0.00449948,  0.00286644,  0.01360741,  0.00378512,
		 0.01730666, -0.00687429,  0.01407835, -0.01269894, -0.02589384,
		 0.02061724,  0.00610378, -0.00940299, -0.04350994,  0.00140479 };

	static const TArray<float> v4 = { -0.01996898, -0.00875812,  0.02279899,  0.00772181, -0.00121196,
		 0.02298377, -0.02589569, -0.03266971, -0.01110879, -0.00376158,
		 0.03213564,  0.00483498, -0.01152828,  0.04254358,  0.00550616,
		-0.04170714, -0.02301609,  0.0042175 , -0.0017946 ,  0.01036263 };

	if (PlayerLocationArray.Num() != 10)
		return ESCENETOOLTYPE::UNKNOWN;

	//Intercept
	TArray<float> sum = { 0.00071966, -0.00851626, -0.00986904, -0.02048042,  0.03814606 };

	for (int32 i = 0; i < 10; ++i) {
		sum[0] += PlayerLocationArray[i].X * v0[2 * i];
		sum[0] += PlayerLocationArray[i].Y * v0[2 * i + 1];
		sum[1] += PlayerLocationArray[i].X * v1[2 * i];
		sum[1] += PlayerLocationArray[i].Y * v1[2 * i + 1];
		sum[2] += PlayerLocationArray[i].X * v2[2 * i];
		sum[2] += PlayerLocationArray[i].Y * v2[2 * i + 1];
		sum[3] += PlayerLocationArray[i].X * v3[2 * i];
		sum[3] += PlayerLocationArray[i].Y * v3[2 * i + 1];
		sum[4] += PlayerLocationArray[i].X * v4[2 * i];
		sum[4] += PlayerLocationArray[i].Y * v4[2 * i + 1];
	}

	int32 largest_index = 0;
	float largest_value = -100000.0f;
	for (int32 i = 0; i < 5; ++i) {
		if (sum[i] > largest_value) {
			largest_index = i;
			largest_value = sum[i];
		}
	}

	switch (largest_index)
	{
		case 0:
			return ESCENETOOLTYPE::TABLE;
		case 1:
			return ESCENETOOLTYPE::CABINET;
		case 2:
			return ESCENETOOLTYPE::SENDER;
		case 3:
			return ESCENETOOLTYPE::CUTBOARD;
		default:
			break;
	}
	
	return ESCENETOOLTYPE::UNKNOWN;
}

void ATaskPawn::SetSuggestionTime()
{
	SuggestionTime = SuggestionTime.Now();
	RecordResponseTime = true;
}

void ATaskPawn::LRecordResponseTime()
{
	if (!RecordResponseTime)
		return;

	const FString RelativeDirectory("PlayerRecords");
	/*
	FString FileName("Record_response_time_");
	FileName.Append(GameName);
	FileName.Append(".txt");
	FString TextString("Suggestion Time: ");
	TextString.Append(FString::FromInt(SuggestionTime.GetMinute()) + " min " +
		FString::FromInt(SuggestionTime.GetSecond()) + " second\n Respond Time: ");

	SuggestionTime = SuggestionTime.Now();
	TextString.Append(FString::FromInt(SuggestionTime.GetMinute()) + " min " +
		FString::FromInt(SuggestionTime.GetSecond()) + " second\n");*/
	SuggestionTimeRecordMinArray.Add(SuggestionTime.GetMinute());
	SuggestionTimeRecordSecArray.Add(SuggestionTime.GetSecond());

	SuggestionTime = SuggestionTime.Now();

	ResponseTimeRecordMinArray.Add(SuggestionTime.GetMinute());
	ResponseTimeRecordSecArray.Add(SuggestionTime.GetSecond());

	RecordResponseTime = false;

	//VerifyOrCreateDirectory(RelativeDirectory);
	//WriteStringtoFile(RelativeDirectory, FileName, TextString);
}

