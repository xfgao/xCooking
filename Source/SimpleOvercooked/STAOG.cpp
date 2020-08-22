// Fill out your copyright notice in the Description page of Project Settings.


#include "STAOG.h"

//STAOG::STAOG()
//{
//}
//
//STAOG::~STAOG()
//{
//}

//USTRUCT()
//struct AOGNode {
//	GENERATED_BODY();
//
//	UPROPERTY()
//		int32 SampleInt32;
//};

//UTaskAOG::UTaskAOG()
//{
//	TaskName = FString("my godness");
//}
//
//void UTaskAOG::SetTask(FString taskName)
//{
//	TaskName = taskName;
//	if (TaskName.Equals(FString("Mixed Apple Bowl"))) {
//		//FAOGNode root(FString("root"), FString("Mixed Apple Bowl"), 0, EAOGNodeType::OR_NODE);
//		//RootNode = &root;
//
//		//FAOGNode LeftChild;
//		//root.AddChild(&LeftChild);
//		//*RootNode = root;
//	}
//}

TaskTree::TaskTree()
{
	TaskName = FString("TaskTreeAAAAA");
}

TaskTree::TaskTree(FString task)
{
	TaskName = task;
	TaskDescriptions.Add(FString("Welcome to VRKitchen-SimpleOvercooked environment. You are in a virtual kitchen, there are some tasks(i.e. some dishes) to make."));
	if (TaskName.Equals(FString("Mixed Apple Bowl"))) {
		//Define task description
		TaskDescriptions.Add(FString("In this task, you are going to make a mixed-apple-bowl, which is a dish with a red apple and a green apple."));
		TaskDescriptions.Add(FString("In details to make the mixed-apple-bowl, you will find one red and one green apple, get them cut and put in a bowl, and finally send them to designated place."));

		//Define AOG nodes
		RobotRootNode = TSharedPtr<FAOGNode>(new FAOGNode(FString("root"), FString("Mixed Sliced Apple Bowl"), 0, EAOGNodeType::OR_NODE));
		FKitchenItem required_item_0;
		required_item_0.item_type = EItemType::ITEM_BOWL;
		required_item_0.item_name = "A bowl with a sliced red apple and a sliced green apple";
		required_item_0.item_attributes = { EItemType::ITEM_SLICED_APPLE_GREEN, EItemType::ITEM_SLICED_APPLE_RED };
		RobotRootNode->item_lists.Add(required_item_0);

		TSharedPtr<FAOGNode> Dummy1(new FAOGNode(FString("child"), FString("Sliced Red Apple Bowl + Sliced Green Apple"), -1, EAOGNodeType::AND_NODE));
		TSharedPtr<FAOGNode> Dummy2(new FAOGNode(FString("child"), FString("Sliced Green Apple Bowl + Sliced Red Apple"), -2,EAOGNodeType::AND_NODE));

		TSharedPtr<FAOGNode> Node1(new FAOGNode(FString("child"), FString("Sliced Red Apple Bowl"), 1, EAOGNodeType::AND_NODE));
		FKitchenItem required_item_1;
		required_item_1.item_type = EItemType::ITEM_BOWL;
		required_item_1.item_name = "A bowl with a sliced red apple";
		required_item_1.item_attributes = {EItemType::ITEM_SLICED_APPLE_RED};
		Node1->item_lists.Add(required_item_1);

		Dummy1->item_lists.Add(required_item_1);

		TSharedPtr<FAOGNode> Node2(new FAOGNode(FString("child"), FString("Sliced Green Apple Bowl"), 2, EAOGNodeType::AND_NODE));
		FKitchenItem required_item_2;
		required_item_2.item_type = EItemType::ITEM_BOWL;
		required_item_2.item_name = "A bowl with a sliced green apple";
		required_item_2.item_attributes = { EItemType::ITEM_SLICED_APPLE_GREEN };
		Node2->item_lists.Add(required_item_2);

		Dummy2->item_lists.Add(required_item_2);

		TSharedPtr<FAOGNode> Node3(new FAOGNode(FString("child"), FString("Sliced Red Apple"), 3, EAOGNodeType::AND_NODE));
		FKitchenItem required_item_3;
		required_item_3.item_type = EItemType::ITEM_SLICED_APPLE_RED;
		required_item_3.item_name = "A sliced red apple";
		Node3->item_lists.Add(required_item_3);
		Node3->is_casual = true;

		Dummy2->item_lists.Add(required_item_3);

		TSharedPtr<FAOGNode> Node4(new FAOGNode(FString("child"), FString("Sliced Green Apple"), 4, EAOGNodeType::AND_NODE));
		FKitchenItem required_item_4;
		required_item_4.item_type = EItemType::ITEM_SLICED_APPLE_GREEN;
		required_item_4.item_name = "A sliced green apple";
		Node4->item_lists.Add(required_item_4);
		Node4->is_casual = true;

		Dummy1->item_lists.Add(required_item_4);


		TSharedPtr<FAOGNode> Node5(new FAOGNode(FString("child"), FString("Red Apple"), 5, EAOGNodeType::TERMINAL_NODE));
		FKitchenItem required_item_5;
		required_item_5.item_type = EItemType::ITEM_APPLE_RED;
		required_item_5.item_name = "A red apple";
		Node5->item_lists.Add(required_item_5);

		TSharedPtr<FAOGNode> Node6(new FAOGNode(FString("child"), FString("Green Apple"), 6, EAOGNodeType::TERMINAL_NODE));
		FKitchenItem required_item_6;
		required_item_6.item_type = EItemType::ITEM_APPLE_GREEN;
		required_item_6.item_name = "A green apple";
		Node6->item_lists.Add(required_item_6);

		TSharedPtr<FAOGNode> Node7(new FAOGNode(FString("child"), FString("Bowl"), 7, EAOGNodeType::TERMINAL_NODE));
		FKitchenItem required_item_7;
		required_item_7.item_type = EItemType::ITEM_BOWL;
		required_item_7.item_name = "A bowl";
		Node7->item_lists.Add(required_item_7);

		//Add links
		RobotRootNode->AddChild(Dummy1);
		Dummy1->AddParent(RobotRootNode);

		RobotRootNode->AddChild(Dummy2);
		Dummy2->AddParent(RobotRootNode);

		Dummy1->AddChild(Node1);
		Node1->AddParent(Dummy1);

		Dummy1->AddChild(Node4);
		Node4->AddParent(Dummy1);

		Node1->AddChild(Node3);
		Node3->AddParent(Node1);

		Node1->AddChild(Node7); //Terminal
		Node7->AddParent(Node1); 

		Node3->AddChild(Node5); //Terminal
		Node5->AddParent(Node3);

		Node4->AddChild(Node6); //Terminal
		Node6->AddParent(Node4);

		Dummy2->AddChild(Node2);
		Node2->AddParent(Dummy2);

		Dummy2->AddChild(Node3);
		Node3->AddParent(Dummy2);

		Node2->AddChild(Node4);
		Node4->AddParent(Node2);

		Node2->AddChild(Node7); //Terminal
		Node7->AddParent(Node2);

	}
	
	else if (TaskName.Equals(FString("Green Apple Juice"))) {
		//Define task description
		TaskDescriptions.Add(FString("In this task, you are going to make some green apple juice. You need to get and cut apples first, then make juice."));
		TaskDescriptions.Add(FString("In details to make the green apple juice, you will get three green apples, cut them and put them in the juicer, and finally send juice to designated place in a bowl"));

		FinishNode = TSharedPtr<FAOGNode>(new FAOGNode(FString("send"), FString("Good job! Please send the dish....."), -2, EAOGNodeType::TERMINAL_NODE));
		FinishNode->AddActionPair(EAIAction::MOVE_TO, FString("bowl green apple juice"));
		FinishNode->AddActionPair(EAIAction::PICK_UP_DROP, FString("bowl green apple juice"));
		FinishNode->AddActionPair(EAIAction::MOVE_TO, FString("sender"));
		FKitchenItem required_item_f;
		required_item_f.item_name = "Send the juice";
		FinishNode->item_lists.Add(required_item_f);
		FinishNode->AddActionPair(EAIAction::PICK_UP_DROP, FString());
		FinishNode->Planer = ECOOKTYPE::PLAYER;
		FinishNode->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		FinishNode->valid_scenetools.Add(ESCENETOOLTYPE::SENDER);

		//Define AOG nodes for robot
		RobotRootNode = TSharedPtr<FAOGNode>(new FAOGNode(FString("root"), FString("Making Apple Juice Robot Plan"), 0, EAOGNodeType::ROOT_NODE));
		

		TSharedPtr<FAOGNode> Node_d1(new FAOGNode(FString("child"), FString("Getting Apple1"), -1, EAOGNodeType::AND_NODE, false, true));
		Node_d1->valid_scenetools.Add(ESCENETOOLTYPE::BASKET);
		Node_d1->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d1->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_APPLE_GREEN, EAbstractLocation::ON_TABLE));
		Node_d1->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_APPLE_GREEN, EAbstractLocation::ON_CUTBOARD));
		Node_d1->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::ANY));
		Node_d1->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));

		TSharedPtr<FAOGNode> Node_d2(new FAOGNode(FString("child"), FString("Getting Apple2"), -1, EAOGNodeType::AND_NODE, false, true));
		Node_d2->valid_scenetools.Add(ESCENETOOLTYPE::BASKET);
		Node_d2->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d2->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_APPLE_GREEN, EAbstractLocation::ON_TABLE));
		Node_d2->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_APPLE_GREEN, EAbstractLocation::ON_CUTBOARD));
		Node_d2->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::ANY));
		Node_d2->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));

		TSharedPtr<FAOGNode> Node_d3(new FAOGNode(FString("child"), FString("Getting Apple3"), -1, EAOGNodeType::AND_NODE, false, true));
		Node_d3->valid_scenetools.Add(ESCENETOOLTYPE::BASKET);
		Node_d3->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d3->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_APPLE_GREEN, EAbstractLocation::ON_TABLE));
		Node_d3->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_APPLE_GREEN, EAbstractLocation::ON_CUTBOARD));
		Node_d3->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::ANY));
		Node_d3->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));

		TSharedPtr<FAOGNode> Node_d4(new FAOGNode(FString("child"), FString("Getting Apple Slices1"), -1, EAOGNodeType::AND_NODE, false, true));
		Node_d4->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		Node_d4->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d4->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::IN_JUCIER));
		Node_d4->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));

		TSharedPtr<FAOGNode> Node_d5(new FAOGNode(FString("child"), FString("Getting Apple Slices2"), -1, EAOGNodeType::AND_NODE, false, true));
		Node_d5->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		Node_d5->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d5->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::IN_JUCIER));
		Node_d5->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));
	

		TSharedPtr<FAOGNode> Node_d6(new FAOGNode(FString("child"), FString("Getting Apple Slices3"), -1, EAOGNodeType::AND_NODE, false, true));
		Node_d6->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		Node_d6->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d6->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::IN_JUCIER));
		Node_d6->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));


		TSharedPtr<FAOGNode> Node_d7(new FAOGNode(FString("child"), FString("Using Juicer"), -1, EAOGNodeType::AND_NODE, false, true));
		Node_d7->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		Node_d7->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));


		TSharedPtr<FAOGNode> Node_d8(new FAOGNode(FString("child"), FString("Handing Over Juice"), -1, EAOGNodeType::AND_NODE, false, true));
		Node_d8->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		Node_d8->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d8->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ON_TABLE));


		/////////////////////////////////


		

		TSharedPtr<FAOGNode> Node_d9(new FAOGNode(FString("child"), FString("Taking Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d9->valid_scenetools.Add(ESCENETOOLTYPE::BASKET);
		Node_d9->AddActionPair(EAIAction::MOVE_TO, FString("green apple basket"));
		Node_d9->AddActionPair(EAIAction::PICK_UP_DROP, FString("green apple"));
		Node_d9->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::IN_BASKET,
			(int8)EAbstractLocation::BE_HOLD);

		

		TSharedPtr<FAOGNode> Node_d10(new FAOGNode(FString("child"), FString("Placing Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d10->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d10->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
		Node_d10->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		Node_d10->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_TABLE);


		TSharedPtr<FAOGNode> Node_d11(new FAOGNode(FString("child"), FString("Taking Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d11->valid_scenetools.Add(ESCENETOOLTYPE::BASKET);
		Node_d11->AddActionPair(EAIAction::MOVE_TO, FString("green apple basket"));
		Node_d11->AddActionPair(EAIAction::PICK_UP_DROP, FString("green apple"));
		Node_d11->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::IN_BASKET,
			(int8)EAbstractLocation::BE_HOLD);


		TSharedPtr<FAOGNode> Node_d12(new FAOGNode(FString("child"), FString("Placing Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d12->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d12->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
		Node_d12->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		Node_d12->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_TABLE);

		TSharedPtr<FAOGNode> Node_d13(new FAOGNode(FString("child"), FString("Taking Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d13->valid_scenetools.Add(ESCENETOOLTYPE::BASKET);
		Node_d13->AddActionPair(EAIAction::MOVE_TO, FString("green apple basket"));
		Node_d13->AddActionPair(EAIAction::PICK_UP_DROP, FString("green apple"));
		Node_d13->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::IN_BASKET,
			(int8)EAbstractLocation::BE_HOLD);

		TSharedPtr<FAOGNode> Node_d14(new FAOGNode(FString("child"), FString("Placing Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d14->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d14->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
		Node_d14->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		Node_d14->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_TABLE);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		TSharedPtr<FAOGNode> Node_d15(new FAOGNode(FString("child"), FString("Taking Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d15->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d15->AddActionPair(EAIAction::MOVE_TO, FString("sliced green apple"));
		Node_d15->AddActionPair(EAIAction::PICK_UP_DROP, FString("sliced green apple"));
		Node_d15->setFluentChanges("Apple", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::ON_TABLE,
			(int8)EAbstractLocation::BE_HOLD);


		TSharedPtr<FAOGNode> Node_d16(new FAOGNode(FString("child"), FString("Placing Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d16->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d16->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		Node_d16->AddActionPair(EAIAction::MOVE_TO, FString("juicer"));
		Node_d16->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		Node_d16->setFluentChanges("Apple", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::IN_JUCIER);
		Node_d16->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);

		TSharedPtr<FAOGNode> Node_d17(new FAOGNode(FString("child"), FString("Taking Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d17->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d17->AddActionPair(EAIAction::MOVE_TO, FString("sliced green apple"));
		Node_d17->AddActionPair(EAIAction::PICK_UP_DROP, FString("sliced green apple"));
		Node_d17->setFluentChanges("Apple", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::ON_TABLE,
			(int8)EAbstractLocation::BE_HOLD);

		TSharedPtr<FAOGNode> Node_d18(new FAOGNode(FString("child"), FString("Placing Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d18->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d18->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		Node_d18->AddActionPair(EAIAction::MOVE_TO, FString("juicer"));
		Node_d18->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		Node_d18->setFluentChanges("Apple", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::IN_JUCIER);
		Node_d18->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);

		TSharedPtr<FAOGNode> Node_d19(new FAOGNode(FString("child"), FString("Taking Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d19->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d19->AddActionPair(EAIAction::MOVE_TO, FString("sliced green apple"));
		Node_d19->AddActionPair(EAIAction::PICK_UP_DROP, FString("sliced green apple"));
		Node_d19->setFluentChanges("Apple", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::ON_TABLE,
			(int8)EAbstractLocation::BE_HOLD);

		TSharedPtr<FAOGNode> Node_d20(new FAOGNode(FString("child"), FString("Placing Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d20->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d20->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		Node_d20->AddActionPair(EAIAction::MOVE_TO, FString("juicer"));
		Node_d20->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		Node_d20->setFluentChanges("Apple", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::IN_JUCIER);
		Node_d20->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		//////////////////////////////////////////////////////////////////////////////
		TSharedPtr<FAOGNode> Node_d21(new FAOGNode(FString("child"), FString("Using Juicer"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d21->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		Node_d21->AddActionPair(EAIAction::MOVE_TO, FString("juicer"));
		Node_d21->AddActionPair(EAIAction::INSPECT, FString("juicer"));
		Node_d21->setFluentChanges("Apple", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_JUICE_APPLE_GREEN, (int8)EAbstractLocation::IN_JUCIER,
			(int8)EAbstractLocation::IN_JUCIER);
		///////////////////////////////////////////////////////////////////////////////
		TSharedPtr<FAOGNode> Node_d22(new FAOGNode(FString("child"), FString("Taking Bowl"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d22->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d22->AddActionPair(EAIAction::MOVE_TO, FString("bowl"));
		Node_d22->AddActionPair(EAIAction::PICK_UP_DROP, FString("bowl"));
		Node_d22->setFluentChanges("Apple", (int8)EItemType::ITEM_BOWL, (int8)EItemType::ITEM_BOWL, (int8)EAbstractLocation::ON_TABLE,
			(int8)EAbstractLocation::BE_HOLD);

		TSharedPtr<FAOGNode> Node_d23(new FAOGNode(FString("child"), FString("Pouring Juice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d23->valid_scenetools.Add(ESCENETOOLTYPE::JUICER);
		Node_d23->AddActionPair(EAIAction::MOVE_TO, FString("juicer"));
		Node_d23->AddActionPair(EAIAction::PICK_UP_DROP, FString("bowl green apple juice"));
		Node_d23->setFluentChanges("Apple", (int8)EItemType::ITEM_BOWL, (int8)EItemType::ITEM_BOWL, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::BE_HOLD);
		
		TSharedPtr<FAOGNode> Node_d24(new FAOGNode(FString("child"), FString("Placing Juice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		Node_d24->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		Node_d24->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
		Node_d24->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		Node_d24->setFluentChanges("Apple", (int8)EItemType::ITEM_BOWL, (int8)EItemType::ITEM_BOWL, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_TABLE);

		Node_d1->Planer = ECOOKTYPE::ROBOT;
		Node_d2->Planer = ECOOKTYPE::ROBOT;
		Node_d3->Planer = ECOOKTYPE::ROBOT;
		Node_d4->Planer = ECOOKTYPE::ROBOT;
		Node_d5->Planer = ECOOKTYPE::ROBOT;
		Node_d6->Planer = ECOOKTYPE::ROBOT;
		Node_d7->Planer = ECOOKTYPE::ROBOT;
		Node_d8->Planer = ECOOKTYPE::ROBOT;
		Node_d9->Planer = ECOOKTYPE::ROBOT;
		Node_d10->Planer = ECOOKTYPE::ROBOT;
		Node_d11->Planer = ECOOKTYPE::ROBOT;
		Node_d12->Planer = ECOOKTYPE::ROBOT;
		Node_d13->Planer = ECOOKTYPE::ROBOT;
		Node_d14->Planer = ECOOKTYPE::ROBOT;
		Node_d15->Planer = ECOOKTYPE::ROBOT;
		Node_d16->Planer = ECOOKTYPE::ROBOT;
		Node_d17->Planer = ECOOKTYPE::ROBOT;

		Node_d18->Planer = ECOOKTYPE::ROBOT;
		Node_d19->Planer = ECOOKTYPE::ROBOT;
		Node_d20->Planer = ECOOKTYPE::ROBOT;
		Node_d21->Planer = ECOOKTYPE::ROBOT;
		Node_d22->Planer = ECOOKTYPE::ROBOT;
		Node_d23->Planer = ECOOKTYPE::ROBOT;
		Node_d24->Planer = ECOOKTYPE::ROBOT;
	

		RobotRootNode->AddChild(Node_d1);
		
		RobotRootNode->AddChild(Node_d2);
		RobotRootNode->AddChild(Node_d3);
		RobotRootNode->AddChild(Node_d4);
		RobotRootNode->AddChild(Node_d5);
		RobotRootNode->AddChild(Node_d6);
		RobotRootNode->AddChild(Node_d7);
		RobotRootNode->AddChild(Node_d8);
		
		Node_d1->AddParent(RobotRootNode);
		
		
		Node_d2->AddParent(RobotRootNode);
		Node_d3->AddParent(RobotRootNode);
		Node_d4->AddParent(RobotRootNode);
		Node_d5->AddParent(RobotRootNode);
		Node_d6->AddParent(RobotRootNode);
		Node_d7->AddParent(RobotRootNode);
		Node_d8->AddParent(RobotRootNode);
		
		
		Node_d1->AddChild(Node_d9);
		Node_d9->AddParent(Node_d1);

		Node_d1->AddChild(Node_d10);
		Node_d10->AddParent(Node_d1);

		
		Node_d2->AddChild(Node_d11);
		Node_d11->AddParent(Node_d2);

		Node_d2->AddChild(Node_d12);
		Node_d12->AddParent(Node_d2);

		
		Node_d3->AddChild(Node_d13);
		Node_d13->AddParent(Node_d3);

		Node_d3->AddChild(Node_d14);
		Node_d14->AddParent(Node_d3);

		Node_d4->AddChild(Node_d15);
		Node_d15->AddParent(Node_d4);

		Node_d4->AddChild(Node_d16);
		Node_d16->AddParent(Node_d4);

		Node_d5->AddChild(Node_d17);
		Node_d17->AddParent(Node_d5);

		Node_d5->AddChild(Node_d18);
		Node_d18->AddParent(Node_d5);

		Node_d6->AddChild(Node_d19);
		Node_d19->AddParent(Node_d6);

		Node_d6->AddChild(Node_d20);
		Node_d20->AddParent(Node_d6);

		Node_d7->AddChild(Node_d21);
		Node_d21->AddParent(Node_d7);

		Node_d8->AddChild(Node_d22);
		Node_d22->AddParent(Node_d8);

		Node_d8->AddChild(Node_d23);
		Node_d23->AddParent(Node_d8);

		Node_d8->AddChild(Node_d24);
		Node_d24->AddParent(Node_d8);
		
		//define AOG nodes for Human
		HumanRootNode = TSharedPtr<FAOGNode>(new FAOGNode(FString("root"), FString("Making Orange Human Plan"), 0, EAOGNodeType::ROOT_NODE));
		TSharedPtr<FAOGNode> hNode_d1(new FAOGNode(FString("child"), FString("Preparing Apple1"), -1, EAOGNodeType::AND_NODE, false, true));
		hNode_d1->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		hNode_d1->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);
		hNode_d1->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_APPLE_GREEN, EAbstractLocation::ON_CUTBOARD));
		hNode_d1->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::ANY));
		hNode_d1->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));
		

		TSharedPtr<FAOGNode> hNode_d2(new FAOGNode(FString("child"), FString("Handing Over Apple1"), -1, EAOGNodeType::AND_NODE, false, true));
		hNode_d2->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		hNode_d2->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);
		hNode_d2->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::ON_TABLE));
		hNode_d2->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));


		TSharedPtr<FAOGNode> hNode_d3(new FAOGNode(FString("child"), FString("Preparing Apple2"), -1, EAOGNodeType::AND_NODE, false, true));
		hNode_d3->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		hNode_d3->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);
		hNode_d3->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_APPLE_GREEN, EAbstractLocation::ON_CUTBOARD));
		hNode_d3->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::ANY));
		hNode_d3->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));


		TSharedPtr<FAOGNode> hNode_d4(new FAOGNode(FString("child"), FString("Handing Over Apple2"), -1, EAOGNodeType::AND_NODE, false, true));
		hNode_d4->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		hNode_d4->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);
		hNode_d4->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::ON_TABLE));
		hNode_d4->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));
	


		TSharedPtr<FAOGNode> hNode_d5(new FAOGNode(FString("child"), FString("Preparing Apple3"), -1, EAOGNodeType::AND_NODE, false, true));
		hNode_d5->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		hNode_d5->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);
		hNode_d5->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_APPLE_GREEN, EAbstractLocation::ON_CUTBOARD));
		hNode_d5->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::ANY));
		hNode_d5->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));
	

		TSharedPtr<FAOGNode> hNode_d6(new FAOGNode(FString("child"), FString("Handing Over Apple3"), -1, EAOGNodeType::AND_NODE, false, true));
		hNode_d6->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		hNode_d6->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);
		hNode_d6->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_APPLE_GREEN, EAbstractLocation::ON_TABLE));
		hNode_d6->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));
	

		TSharedPtr<FAOGNode> hNode_d7(new FAOGNode(FString("child"), FString("Handing Over Bowl"), -1, EAOGNodeType::AND_NODE, false, true));
		hNode_d7->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		hNode_d7->valid_scenetools.Add(ESCENETOOLTYPE::CABINET);
		hNode_d7->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_BOWL, EAbstractLocation::ON_TABLE));
		hNode_d7->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_JUICE_APPLE_GREEN, EAbstractLocation::ANY));

		

		TSharedPtr<FAOGNode> hNode_d8(new FAOGNode(FString("child"), FString("Delivering Juice"), -1, EAOGNodeType::AND_NODE, false, true));
		hNode_d8->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		hNode_d8->valid_scenetools.Add(ESCENETOOLTYPE::SENDER);

		////////////////////////////////////
		// set up subtasks 
		// the ordering is important. This is based on dependencies
		///////////////////////////

		subTasks.Add(hNode_d8);
		subTasks.Add(Node_d8);
		subTasks.Add(Node_d7);
		subTasks.Add(hNode_d7);
		subTasks.Add(Node_d4);
		subTasks.Add(Node_d5);
		subTasks.Add(Node_d6);
		subTasks.Add(hNode_d6);
		subTasks.Add(hNode_d4);
		subTasks.Add(hNode_d2);
		subTasks.Add(hNode_d1);
		subTasks.Add(hNode_d3);
		subTasks.Add(hNode_d5);
		subTasks.Add(Node_d1);
		subTasks.Add(Node_d2);
		subTasks.Add(Node_d3);


		//////////////////////////////
		TSharedPtr<FAOGNode> hNode_d9(new FAOGNode(FString("child"), FString("Taking Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d9->AddActionPair(EAIAction::MOVE_TO, FString("green apple"));
		hNode_d9->AddActionPair(EAIAction::PICK_UP_DROP, FString("green apple"));
		hNode_d9->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::ON_TABLE,
			(int8)EAbstractLocation::BE_HOLD);
		hNode_d9->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		

		TSharedPtr<FAOGNode> hNode_d10(new FAOGNode(FString("child"), FString("Placing Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d10->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
		hNode_d10->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		hNode_d10->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_CUTBOARD);
		hNode_d10->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);


		TSharedPtr<FAOGNode> hNode_d11(new FAOGNode(FString("child"), FString("Taking Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d11->AddActionPair(EAIAction::MOVE_TO, FString("green apple"));
		hNode_d11->AddActionPair(EAIAction::PICK_UP_DROP, FString("green apple"));
		hNode_d11->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::ON_TABLE,
			(int8)EAbstractLocation::BE_HOLD);
		hNode_d11->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);

		TSharedPtr<FAOGNode> hNode_d12(new FAOGNode(FString("child"), FString("Placing Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d12->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
		hNode_d12->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		hNode_d12->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_CUTBOARD);
		hNode_d12->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);

		TSharedPtr<FAOGNode> hNode_d13(new FAOGNode(FString("child"), FString("Taking Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d13->AddActionPair(EAIAction::MOVE_TO, FString("green apple"));
		hNode_d13->AddActionPair(EAIAction::PICK_UP_DROP, FString("green  apple"));
		hNode_d13->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::ON_TABLE,
			(int8)EAbstractLocation::BE_HOLD);
		hNode_d13->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);

		TSharedPtr<FAOGNode> hNode_d14(new FAOGNode(FString("child"), FString("Placing Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d14->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
		hNode_d14->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		hNode_d14->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_CUTBOARD);
		hNode_d14->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);

		//////////////////////////////////////////////////////////////////////////////////////
		TSharedPtr<FAOGNode> hNode_d15(new FAOGNode(FString("child"), FString("Slicing Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d15->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
		hNode_d15->AddActionPair(EAIAction::INSPECT , FString(""));
		hNode_d15->setFluentChanges("Apple", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::ON_CUTBOARD,
			(int8)EAbstractLocation::ON_CUTBOARD);
		hNode_d15->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);


		TSharedPtr<FAOGNode> hNode_d16(new FAOGNode(FString("child"), FString("Taking Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d16->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
		hNode_d16->AddActionPair(EAIAction::PICK_UP_DROP, FString("sliced green apple"));
		hNode_d16->setFluentChanges("Apple", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::ON_CUTBOARD,
			(int8)EAbstractLocation::BE_HOLD);
		hNode_d16->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);



		TSharedPtr<FAOGNode> hNode_d17(new FAOGNode(FString("child"), FString("Placing Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d17->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
		hNode_d17->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		hNode_d17->setFluentChanges("Apple Slice", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_TABLE);
		hNode_d17->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);

		TSharedPtr<FAOGNode> hNode_d18(new FAOGNode(FString("child"), FString("Slicing Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d18->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
		hNode_d18->AddActionPair(EAIAction::INSPECT, FString(""));
		hNode_d18->setFluentChanges("Apple Slice", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::ON_CUTBOARD,
			(int8)EAbstractLocation::ON_CUTBOARD);
		hNode_d18->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);

		TSharedPtr<FAOGNode> hNode_d19(new FAOGNode(FString("child"), FString("Taking Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d19->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
		hNode_d19->AddActionPair(EAIAction::PICK_UP_DROP, FString("sliced green apple"));
		hNode_d19->setFluentChanges("Apple Slice", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::ON_CUTBOARD,
			(int8)EAbstractLocation::BE_HOLD);
		hNode_d19->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);

		TSharedPtr<FAOGNode> hNode_d20(new FAOGNode(FString("child"), FString("Placing Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d20->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
		hNode_d20->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		hNode_d20->setFluentChanges("Apple Slice", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_TABLE);
		hNode_d20->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);


		TSharedPtr<FAOGNode> hNode_d21(new FAOGNode(FString("child"), FString("Slicing Apple"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d21->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
		hNode_d21->AddActionPair(EAIAction::INSPECT, FString(""));
		hNode_d21->setFluentChanges("Apple Slice", (int8)EItemType::ITEM_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::ON_CUTBOARD,
			(int8)EAbstractLocation::ON_CUTBOARD);
		hNode_d21->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);


		TSharedPtr<FAOGNode> hNode_d22(new FAOGNode(FString("child"), FString("Taking Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d22->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
		hNode_d22->AddActionPair(EAIAction::PICK_UP_DROP, FString("sliced green apple"));
		hNode_d22->setFluentChanges("Apple Slice", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::ON_CUTBOARD,
			(int8)EAbstractLocation::BE_HOLD);
		hNode_d22->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);

		TSharedPtr<FAOGNode> hNode_d23(new FAOGNode(FString("child"), FString("Placing Apple Slice"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d23->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
		hNode_d23->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		hNode_d23->setFluentChanges("Apple Slice", (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EItemType::ITEM_SLICED_APPLE_GREEN, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_TABLE);
		hNode_d23->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
		/////////////////////////////////////////////////

		TSharedPtr<FAOGNode> hNode_d24(new FAOGNode(FString("child"), FString("Taking Bowl"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d24->AddActionPair(EAIAction::MOVE_TO, FString("cabinet"));
		hNode_d24->AddActionPair(EAIAction::INSPECT, FString("bowl"));
		hNode_d24->setFluentChanges("Bowl", (int8)EItemType::ITEM_BOWL, (int8)EItemType::ITEM_BOWL, (int8)EAbstractLocation::IN_CABINET,
			(int8)EAbstractLocation::BE_HOLD);
		hNode_d24->valid_scenetools.Add(ESCENETOOLTYPE::CABINET);

		TSharedPtr<FAOGNode> hNode_d25(new FAOGNode(FString("child"), FString("Placing Bowl"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d25->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
		hNode_d25->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		hNode_d25->setFluentChanges("Bowl", (int8)EItemType::ITEM_BOWL, (int8)EItemType::ITEM_BOWL, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_TABLE);
		hNode_d25->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);


		TSharedPtr<FAOGNode> hNode_d26(new FAOGNode(FString("child"), FString("Taking Bowl"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d26->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
		hNode_d26->AddActionPair(EAIAction::PICK_UP_DROP, FString("bowl green apple juice"));
		hNode_d26->setFluentChanges("bowl green apple juice", (int8)EItemType::ITEM_BOWL, (int8)EItemType::ITEM_BOWL, (int8)EAbstractLocation::ON_TABLE,
			(int8)EAbstractLocation::BE_HOLD);
		hNode_d26->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);


		TSharedPtr<FAOGNode> hNode_d27(new FAOGNode(FString("child"), FString("Delivery Bowl"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
		hNode_d27->AddActionPair(EAIAction::MOVE_TO, FString("deliery bench"));
		hNode_d27->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
		hNode_d27->setFluentChanges("bowl green apple juice", (int8)EItemType::ITEM_BOWL, (int8)EItemType::ITEM_BOWL, (int8)EAbstractLocation::BE_HOLD,
			(int8)EAbstractLocation::ON_DELIVERY_BENCH);
		hNode_d27->valid_scenetools.Add(ESCENETOOLTYPE::SENDER);

		hNode_d1->Planer = ECOOKTYPE::PLAYER;
		hNode_d2->Planer = ECOOKTYPE::PLAYER;
		hNode_d3->Planer = ECOOKTYPE::PLAYER;
		hNode_d4->Planer = ECOOKTYPE::PLAYER;
		hNode_d5->Planer = ECOOKTYPE::PLAYER;
		hNode_d6->Planer = ECOOKTYPE::PLAYER;

		hNode_d7->Planer = ECOOKTYPE::PLAYER;
		hNode_d8->Planer = ECOOKTYPE::PLAYER;
		hNode_d9->Planer = ECOOKTYPE::PLAYER;
		hNode_d10->Planer = ECOOKTYPE::PLAYER;
		hNode_d11->Planer = ECOOKTYPE::PLAYER;

		hNode_d12->Planer = ECOOKTYPE::PLAYER;
		hNode_d13->Planer = ECOOKTYPE::PLAYER;
		hNode_d14->Planer = ECOOKTYPE::PLAYER;
		hNode_d15->Planer = ECOOKTYPE::PLAYER;
		hNode_d16->Planer = ECOOKTYPE::PLAYER;
		hNode_d17->Planer = ECOOKTYPE::PLAYER;

		hNode_d18->Planer = ECOOKTYPE::PLAYER;
		hNode_d19->Planer = ECOOKTYPE::PLAYER;
		hNode_d20->Planer = ECOOKTYPE::PLAYER;
		hNode_d21->Planer = ECOOKTYPE::PLAYER;
		hNode_d22->Planer = ECOOKTYPE::PLAYER;
		hNode_d23->Planer = ECOOKTYPE::PLAYER;

		hNode_d24->Planer = ECOOKTYPE::PLAYER;
		hNode_d25->Planer = ECOOKTYPE::PLAYER;
		hNode_d26->Planer = ECOOKTYPE::PLAYER;
		hNode_d27->Planer = ECOOKTYPE::PLAYER;




		HumanRootNode->AddChild(hNode_d1);
		HumanRootNode->AddChild(hNode_d2);
		HumanRootNode->AddChild(hNode_d3);
		HumanRootNode->AddChild(hNode_d4);
		HumanRootNode->AddChild(hNode_d5);
		HumanRootNode->AddChild(hNode_d6);
		HumanRootNode->AddChild(hNode_d7);
		HumanRootNode->AddChild(hNode_d8);

		hNode_d1->AddParent(HumanRootNode);
		hNode_d2->AddParent(HumanRootNode);
		hNode_d3->AddParent(HumanRootNode);
		hNode_d4->AddParent(HumanRootNode);
		hNode_d5->AddParent(HumanRootNode);
		hNode_d6->AddParent(HumanRootNode);
		hNode_d7->AddParent(HumanRootNode);
		hNode_d8->AddParent(HumanRootNode);
		////////////////////////////////////
		
		hNode_d1->AddChild(hNode_d9);
		hNode_d9->AddParent(hNode_d1);

		hNode_d1->AddChild(hNode_d10);
		hNode_d10->AddParent(hNode_d1);
		///////////////////////////////////
		hNode_d3->AddChild(hNode_d11);
		hNode_d11->AddParent(hNode_d3);

		hNode_d3->AddChild(hNode_d12);
		hNode_d12->AddParent(hNode_d3);
		//////////////////////////////////
		hNode_d5->AddChild(hNode_d13);
		hNode_d13->AddParent(hNode_d5);

		hNode_d5->AddChild(hNode_d14);
		hNode_d14->AddParent(hNode_d5);
		//////////////////////////////
		hNode_d2->AddChild(hNode_d15);
		hNode_d15->AddParent(hNode_d2);

		hNode_d2->AddChild(hNode_d16);
		hNode_d16->AddParent(hNode_d2);
		
		hNode_d2->AddChild(hNode_d17);
		hNode_d17->AddParent(hNode_d2);
		////////////////////////////////
		hNode_d4->AddChild(hNode_d18);
		hNode_d18->AddParent(hNode_d4);
	
		hNode_d4->AddChild(hNode_d19);
		hNode_d19->AddParent(hNode_d4);

		hNode_d4->AddChild(hNode_d20);
		hNode_d20->AddParent(hNode_d4);
		////////////////////////////////
		hNode_d6->AddChild(hNode_d21);
		hNode_d21->AddParent(hNode_d6);

		hNode_d6->AddChild(hNode_d22);
		hNode_d22->AddParent(hNode_d6);

		hNode_d6->AddChild(hNode_d23);
		hNode_d23->AddParent(hNode_d6);
		////////////////////////////////
		hNode_d7->AddChild(hNode_d24);
		hNode_d24->AddParent(hNode_d7);

		hNode_d7->AddChild(hNode_d25);
		hNode_d25->AddParent(hNode_d7);
		//////////////////////////////
		hNode_d8->AddChild(hNode_d26);
		hNode_d26->AddParent(hNode_d8);

		hNode_d8->AddChild(hNode_d27);
		hNode_d27->AddParent(hNode_d8);

		/////////////////////////////////////////////////////
		// set up dependency preconditions
		/////////////////////////////////////////////////////

		Node_d4->preconditions.Add(hNode_d2);
		Node_d5->preconditions.Add(hNode_d4);
		Node_d6->preconditions.Add(hNode_d6);

		Node_d7->preconditions.Add(Node_d4);
		Node_d7->preconditions.Add(Node_d5);
		Node_d7->preconditions.Add(Node_d6);

		Node_d8->preconditions.Add(Node_d7);
		Node_d8->preconditions.Add(hNode_d7);

		hNode_d1->preconditions.Add(Node_d1);
		hNode_d2->preconditions.Add(hNode_d1);

		hNode_d3->preconditions.Add(Node_d2);
		hNode_d4->preconditions.Add(hNode_d3);

		hNode_d5->preconditions.Add(Node_d3);
		hNode_d6->preconditions.Add(hNode_d5);

		hNode_d8->preconditions.Add(Node_d8);

	}
	else if (TaskName.Equals(FString("Burger"))) {
	// define task plan for robot
	RobotRootNode = TSharedPtr<FAOGNode>(new FAOGNode(FString("root"), FString("Making Burger Robot Plan"), 0, EAOGNodeType::ROOT_NODE));

	TSharedPtr<FAOGNode> Node_d1(new FAOGNode(FString("child"), FString("Preparing Beef"), -1, EAOGNodeType::AND_NODE, false, true));
	Node_d1->valid_scenetools.Add(ESCENETOOLTYPE::BASKET);
	Node_d1->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);
	Node_d1->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_MEAT, EAbstractLocation::ANY));

	TSharedPtr<FAOGNode> Node_d2(new FAOGNode(FString("child"), FString("Cooking Beef"), -1, EAOGNodeType::AND_NODE, false, true));
	Node_d2->valid_scenetools.Add(ESCENETOOLTYPE::PAN);
	Node_d2->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);
	Node_d2->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_COOKED_MEAT, EAbstractLocation::ANY));

	TSharedPtr<FAOGNode> Node_d3(new FAOGNode(FString("child"), FString("Handing Over Beef"), -1, EAOGNodeType::AND_NODE, false, true));
	Node_d3->valid_scenetools.Add(ESCENETOOLTYPE::PAN);
	Node_d3->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
	Node_d3->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_COOKED_MEAT, EAbstractLocation::ON_TABLE));

	TSharedPtr<FAOGNode> Node_d4(new FAOGNode(FString("child"), FString("Preparing Tomato"), -1, EAOGNodeType::AND_NODE, false, true));
	Node_d4->valid_scenetools.Add(ESCENETOOLTYPE::BASKET);
	Node_d4->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);
	Node_d4->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_TOMATO, EAbstractLocation::ANY));

	RobotRootNode->AddChild(Node_d1);
	RobotRootNode->AddChild(Node_d2);
	RobotRootNode->AddChild(Node_d3);
	RobotRootNode->AddChild(Node_d4);

	Node_d1->AddParent(RobotRootNode);
	Node_d2->AddParent(RobotRootNode);
	Node_d3->AddParent(RobotRootNode);
	Node_d4->AddParent(RobotRootNode);

	TSharedPtr<FAOGNode> Node_d5(new FAOGNode(FString("child"), FString("Getting Beef"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d5->AddActionPair(EAIAction::MOVE_TO, FString("beef basket"));
	Node_d5->AddActionPair(EAIAction::PICK_UP_DROP, FString("beef"));
	Node_d5->setFluentChanges("beef", (int8)EItemType::ITEM_MEAT, (int8)EItemType::ITEM_MEAT, (int8)EAbstractLocation::IN_BASKET,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> Node_d6(new FAOGNode(FString("child"), FString("Placing Beef"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d6->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
	Node_d6->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	Node_d6->setFluentChanges("beef", (int8)EItemType::ITEM_MEAT, (int8)EItemType::ITEM_MEAT, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_CUTBOARD);

	TSharedPtr<FAOGNode> Node_d7(new FAOGNode(FString("child"), FString("Cutting Beef"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d7->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
	Node_d7->AddActionPair(EAIAction::INSPECT, FString("cutboard"));
	Node_d7->setFluentChanges("beef", (int8)EItemType::ITEM_MEAT, (int8)EItemType::ITEM_SLICED_MEAT, (int8)EAbstractLocation::ON_CUTBOARD,
		(int8)EAbstractLocation::ON_CUTBOARD);

	Node_d1->AddChild(Node_d5);
	Node_d1->AddChild(Node_d6);
	Node_d1->AddChild(Node_d7);

	Node_d5->AddParent(Node_d1);
	Node_d6->AddParent(Node_d1);
	Node_d7->AddParent(Node_d1);

	TSharedPtr<FAOGNode> Node_d8(new FAOGNode(FString("child"), FString("Taking Beef"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d8->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
	Node_d8->AddActionPair(EAIAction::PICK_UP_DROP, FString("beef"));
	Node_d8->setFluentChanges("beef", (int8)EItemType::ITEM_SLICED_MEAT, (int8)EItemType::ITEM_SLICED_MEAT, (int8)EAbstractLocation::ON_CUTBOARD,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> Node_d9(new FAOGNode(FString("child"), FString("Placing Beef"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d9->AddActionPair(EAIAction::MOVE_TO, FString("pan"));
	Node_d9->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	Node_d9->setFluentChanges("beef", (int8)EItemType::ITEM_SLICED_MEAT, (int8)EItemType::ITEM_SLICED_MEAT, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_PAN);

	TSharedPtr<FAOGNode> Node_d10(new FAOGNode(FString("child"), FString("Frying Beef"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d10->AddActionPair(EAIAction::MOVE_TO, FString("pan"));
	Node_d10->AddActionPair(EAIAction::INSPECT, FString("pan"));
	Node_d10->setFluentChanges("beef", (int8)EItemType::ITEM_SLICED_MEAT, (int8)EItemType::ITEM_COOKED_MEAT, (int8)EAbstractLocation::ON_PAN,
		(int8)EAbstractLocation::ON_PAN);

	Node_d2->AddChild(Node_d8);
	Node_d2->AddChild(Node_d9);
	Node_d2->AddChild(Node_d10);

	Node_d8->AddParent(Node_d2);
	Node_d9->AddParent(Node_d2);
	Node_d10->AddParent(Node_d2);

	TSharedPtr<FAOGNode> Node_d11(new FAOGNode(FString("child"), FString("Handing Over Beef"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d11->AddActionPair(EAIAction::MOVE_TO, FString("pan"));
	Node_d11->AddActionPair(EAIAction::PICK_UP_DROP, FString("beef"));
	Node_d11->setFluentChanges("beef", (int8)EItemType::ITEM_COOKED_MEAT, (int8)EItemType::ITEM_COOKED_MEAT, (int8)EAbstractLocation::ON_PAN,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> Node_d12(new FAOGNode(FString("child"), FString("Placing Beef"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d12->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
	Node_d12->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	Node_d12->setFluentChanges("beef", (int8)EItemType::ITEM_COOKED_MEAT, (int8)EItemType::ITEM_COOKED_MEAT, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_TABLE);

	Node_d3->AddChild(Node_d11);
	Node_d3->AddChild(Node_d12);

	Node_d11->AddParent(Node_d3);
	Node_d12->AddParent(Node_d3);

	TSharedPtr<FAOGNode> Node_d13(new FAOGNode(FString("child"), FString("Getting Tomato"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d13->AddActionPair(EAIAction::MOVE_TO, FString("tomato basket"));
	Node_d13->AddActionPair(EAIAction::PICK_UP_DROP, FString("tomato"));
	Node_d13->setFluentChanges("tomato", (int8)EItemType::ITEM_TOMATO, (int8)EItemType::ITEM_TOMATO, (int8)EAbstractLocation::IN_BASKET,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> Node_d14(new FAOGNode(FString("child"), FString("Placing Tomato"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d14->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
	Node_d14->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	Node_d14->setFluentChanges("tomato", (int8)EItemType::ITEM_TOMATO, (int8)EItemType::ITEM_TOMATO, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_CUTBOARD);

	TSharedPtr<FAOGNode> Node_d15(new FAOGNode(FString("child"), FString("Cutting Tomato"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	Node_d15->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
	Node_d15->AddActionPair(EAIAction::INSPECT, FString("cutboard"));
	Node_d15->setFluentChanges("tomato", (int8)EItemType::ITEM_TOMATO, (int8)EItemType::ITEM_SLICED_TOMATO, (int8)EAbstractLocation::ON_CUTBOARD,
		(int8)EAbstractLocation::ON_CUTBOARD);

	Node_d4->AddChild(Node_d13);
	Node_d4->AddChild(Node_d14);
	Node_d4->AddChild(Node_d15);

	Node_d13->AddParent(Node_d4);
	Node_d14->AddParent(Node_d4);
	Node_d15->AddParent(Node_d4);

	Node_d1->Planer = ECOOKTYPE::ROBOT;
	Node_d2->Planer = ECOOKTYPE::ROBOT;
	Node_d3->Planer = ECOOKTYPE::ROBOT;
	Node_d4->Planer = ECOOKTYPE::ROBOT;
	Node_d5->Planer = ECOOKTYPE::ROBOT;
	Node_d6->Planer = ECOOKTYPE::ROBOT;
	Node_d7->Planer = ECOOKTYPE::ROBOT;
	Node_d8->Planer = ECOOKTYPE::ROBOT;
	Node_d9->Planer = ECOOKTYPE::ROBOT;
	Node_d10->Planer = ECOOKTYPE::ROBOT;
	Node_d11->Planer = ECOOKTYPE::ROBOT;
	Node_d12->Planer = ECOOKTYPE::ROBOT;
	Node_d13->Planer = ECOOKTYPE::ROBOT;
	Node_d14->Planer = ECOOKTYPE::ROBOT;
	Node_d15->Planer = ECOOKTYPE::ROBOT;

	// define task plan for player
	HumanRootNode = TSharedPtr<FAOGNode>(new FAOGNode(FString("root"), FString("Making Burger Human Plan"), 0, EAOGNodeType::ROOT_NODE));

	TSharedPtr<FAOGNode> hNode_d0(new FAOGNode(FString("child"), FString("Handing Over Plate"), -1, EAOGNodeType::AND_NODE, false, true));
	hNode_d0->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
	hNode_d0->valid_scenetools.Add(ESCENETOOLTYPE::CABINET);
	hNode_d0->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_PLATE, EAbstractLocation::ON_TABLE));

	TSharedPtr<FAOGNode> hNode_d1(new FAOGNode(FString("child"), FString("Plating Beef"), -1, EAOGNodeType::AND_NODE, false, true));
	hNode_d1->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
	hNode_d1->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_COOKED_MEAT, EAbstractLocation::ON_PLATE));

	TSharedPtr<FAOGNode> hNode_d2(new FAOGNode(FString("child"), FString("Preparing Lettuce"), -1, EAOGNodeType::AND_NODE, false, true));
	hNode_d2->valid_scenetools.Add(ESCENETOOLTYPE::CUTBOARD);
	hNode_d2->valid_scenetools.Add(ESCENETOOLTYPE::BASKET);
	hNode_d2->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_LETTUCE, EAbstractLocation::ANY));

	TSharedPtr<FAOGNode> hNode_d3(new FAOGNode(FString("child"), FString("Handing Over Bun"), -1, EAOGNodeType::AND_NODE, false, true));
	hNode_d3->valid_scenetools.Add(ESCENETOOLTYPE::BASKET);
	hNode_d3->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
	hNode_d3->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_BREAD, EAbstractLocation::ON_TABLE));

	TSharedPtr<FAOGNode> hNode_d4(new FAOGNode(FString("child"), FString("Plating Lettuce"), -1, EAOGNodeType::AND_NODE, false, true));
	hNode_d4->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
	hNode_d4->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_LETTUCE, EAbstractLocation::ON_PLATE));

	TSharedPtr<FAOGNode> hNode_d5(new FAOGNode(FString("child"), FString("Plating Tomato"), -1, EAOGNodeType::AND_NODE, false, true));
	hNode_d5->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
	hNode_d5->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_SLICED_TOMATO, EAbstractLocation::ON_PLATE));

	TSharedPtr<FAOGNode> hNode_d6(new FAOGNode(FString("child"), FString("Plating Bun"), -1, EAOGNodeType::AND_NODE, false, true));
	hNode_d6->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
	hNode_d6->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_BREAD, EAbstractLocation::ON_PLATE));
	hNode_d6->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_HAMBERGER, EAbstractLocation::ANY));

	TSharedPtr<FAOGNode> hNode_d7(new FAOGNode(FString("child"), FString("Delivering Burger"), -1, EAOGNodeType::AND_NODE, false, true));
	hNode_d7->valid_scenetools.Add(ESCENETOOLTYPE::TABLE);
	hNode_d7->valid_scenetools.Add(ESCENETOOLTYPE::SENDER);
	hNode_d7->completionCriterion.Add(TPair<EItemType, EAbstractLocation>(EItemType::ITEM_HAMBERGER, EAbstractLocation::ON_DELIVERY_BENCH));

	HumanRootNode->AddChild(hNode_d0);
	HumanRootNode->AddChild(hNode_d1);
	HumanRootNode->AddChild(hNode_d2);
	HumanRootNode->AddChild(hNode_d3);
	HumanRootNode->AddChild(hNode_d4);
	HumanRootNode->AddChild(hNode_d5);
	HumanRootNode->AddChild(hNode_d6);
	HumanRootNode->AddChild(hNode_d7);

	hNode_d0->AddParent(HumanRootNode);
	hNode_d1->AddParent(HumanRootNode);
	hNode_d2->AddParent(HumanRootNode);
	hNode_d3->AddParent(HumanRootNode);
	hNode_d4->AddParent(HumanRootNode);
	hNode_d5->AddParent(HumanRootNode);
	hNode_d6->AddParent(HumanRootNode);
	hNode_d7->AddParent(HumanRootNode);

	TSharedPtr<FAOGNode> hNode_d8(new FAOGNode(FString("child"), FString("Getting Plate"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d8->AddActionPair(EAIAction::MOVE_TO, FString("cabinet"));
	hNode_d8->AddActionPair(EAIAction::PICK_UP_DROP, FString("plate"));
	hNode_d8->setFluentChanges("plate", (int8)EItemType::ITEM_PLATE, (int8)EItemType::ITEM_PLATE, (int8)EAbstractLocation::IN_CABINET,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> hNode_d9(new FAOGNode(FString("child"), FString("Placing Plate"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d9->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
	hNode_d9->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	hNode_d9->setFluentChanges("plate", (int8)EItemType::ITEM_PLATE, (int8)EItemType::ITEM_PLATE, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_TABLE);

	hNode_d0->AddChild(hNode_d8);
	hNode_d0->AddChild(hNode_d9);

	hNode_d8->AddParent(hNode_d0);
	hNode_d9->AddParent(hNode_d0);

	TSharedPtr<FAOGNode> hNode_d10(new FAOGNode(FString("child"), FString("Taking Beef"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d10->AddActionPair(EAIAction::MOVE_TO, FString("beef basket"));
	hNode_d10->AddActionPair(EAIAction::PICK_UP_DROP, FString("beef"));
	hNode_d10->setFluentChanges("beef", (int8)EItemType::ITEM_COOKED_MEAT, (int8)EItemType::ITEM_COOKED_MEAT, (int8)EAbstractLocation::ON_TABLE,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> hNode_d11(new FAOGNode(FString("child"), FString("Placing Beef"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d11->AddActionPair(EAIAction::MOVE_TO, FString("middle table plate")); //plate
	hNode_d11->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	hNode_d11->setFluentChanges("beef", (int8)EItemType::ITEM_COOKED_MEAT, (int8)EItemType::ITEM_COOKED_MEAT, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_PLATE);

	hNode_d1->AddChild(hNode_d10);
	hNode_d1->AddChild(hNode_d11);

	hNode_d10->AddParent(hNode_d1);
	hNode_d11->AddParent(hNode_d1);

	TSharedPtr<FAOGNode> hNode_d12(new FAOGNode(FString("child"), FString("Getting Lettuce"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d12->AddActionPair(EAIAction::MOVE_TO, FString("lettuce basket"));
	hNode_d12->AddActionPair(EAIAction::PICK_UP_DROP, FString("lettuce"));
	hNode_d12->setFluentChanges("lettuce", (int8)EItemType::ITEM_LETTUCE, (int8)EItemType::ITEM_LETTUCE, (int8)EAbstractLocation::IN_BASKET,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> hNode_d13(new FAOGNode(FString("child"), FString("Placing Lettuce"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d13->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
	hNode_d13->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	hNode_d13->setFluentChanges("lettuce", (int8)EItemType::ITEM_LETTUCE, (int8)EItemType::ITEM_LETTUCE, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_CUTBOARD);

	TSharedPtr<FAOGNode> hNode_d14(new FAOGNode(FString("child"), FString("Cutting Lettuce"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d14->AddActionPair(EAIAction::MOVE_TO, FString("cutboard"));
	hNode_d14->AddActionPair(EAIAction::INSPECT, FString("cutboard"));
	hNode_d14->setFluentChanges("lettuce", (int8)EItemType::ITEM_LETTUCE, (int8)EItemType::ITEM_SLICED_LETTUCE, (int8)EAbstractLocation::ON_CUTBOARD,
		(int8)EAbstractLocation::ON_CUTBOARD);

	hNode_d2->AddChild(hNode_d12);
	hNode_d2->AddChild(hNode_d13);
	hNode_d2->AddChild(hNode_d14);

	hNode_d12->AddParent(hNode_d2);
	hNode_d13->AddParent(hNode_d2);
	hNode_d14->AddParent(hNode_d2);

	TSharedPtr<FAOGNode> hNode_d15(new FAOGNode(FString("child"), FString("Getting Bun"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d15->AddActionPair(EAIAction::MOVE_TO, FString("bun basket"));
	hNode_d15->AddActionPair(EAIAction::PICK_UP_DROP, FString("bun"));
	hNode_d15->setFluentChanges("bun", (int8)EItemType::ITEM_BREAD, (int8)EItemType::ITEM_BREAD, (int8)EAbstractLocation::IN_BASKET,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> hNode_d16(new FAOGNode(FString("child"), FString("Placing Bun"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d16->AddActionPair(EAIAction::MOVE_TO, FString("middle table"));
	hNode_d16->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	hNode_d16->setFluentChanges("bun", (int8)EItemType::ITEM_BREAD, (int8)EItemType::ITEM_BREAD, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_TABLE);

	hNode_d3->AddChild(hNode_d15);
	hNode_d3->AddChild(hNode_d16);

	hNode_d15->AddParent(hNode_d3);
	hNode_d15->AddParent(hNode_d3);

	TSharedPtr<FAOGNode> hNode_d17(new FAOGNode(FString("child"), FString("Taking Lettuce"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d17->AddActionPair(EAIAction::MOVE_TO, FString("table"));
	hNode_d17->AddActionPair(EAIAction::PICK_UP_DROP, FString("lettuce"));
	hNode_d17->setFluentChanges("lettuce", (int8)EItemType::ITEM_SLICED_LETTUCE, (int8)EItemType::ITEM_SLICED_LETTUCE, (int8)EAbstractLocation::ON_TABLE,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> hNode_d18(new FAOGNode(FString("child"), FString("Placing Lettuce"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d18->AddActionPair(EAIAction::MOVE_TO, FString("plate"));
	hNode_d18->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	hNode_d18->setFluentChanges("lettuce", (int8)EItemType::ITEM_SLICED_LETTUCE, (int8)EItemType::ITEM_SLICED_LETTUCE, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_PLATE);

	hNode_d4->AddChild(hNode_d17);
	hNode_d4->AddChild(hNode_d18);

	hNode_d17->AddParent(hNode_d4);
	hNode_d18->AddParent(hNode_d4);

	TSharedPtr<FAOGNode> hNode_d19(new FAOGNode(FString("child"), FString("Taking Tomato"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d19->AddActionPair(EAIAction::MOVE_TO, FString("table"));
	hNode_d19->AddActionPair(EAIAction::PICK_UP_DROP, FString("tomato"));
	hNode_d19->setFluentChanges("tomato", (int8)EItemType::ITEM_SLICED_TOMATO, (int8)EItemType::ITEM_SLICED_TOMATO, (int8)EAbstractLocation::ON_TABLE,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> hNode_d20(new FAOGNode(FString("child"), FString("Placing Tomato"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d20->AddActionPair(EAIAction::MOVE_TO, FString("plate"));
	hNode_d20->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	hNode_d20->setFluentChanges("tomato", (int8)EItemType::ITEM_SLICED_TOMATO, (int8)EItemType::ITEM_SLICED_TOMATO, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_PLATE);

	hNode_d5->AddChild(hNode_d19);
	hNode_d5->AddChild(hNode_d20);

	hNode_d19->AddParent(hNode_d5);
	hNode_d20->AddParent(hNode_d5);

	TSharedPtr<FAOGNode> hNode_d21(new FAOGNode(FString("child"), FString("Taking Bun"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d21->AddActionPair(EAIAction::MOVE_TO, FString("table"));
	hNode_d21->AddActionPair(EAIAction::PICK_UP_DROP, FString("bun"));
	hNode_d21->setFluentChanges("bun", (int8)EItemType::ITEM_BREAD, (int8)EItemType::ITEM_BREAD, (int8)EAbstractLocation::ON_TABLE,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> hNode_d22(new FAOGNode(FString("child"), FString("Placing Bun"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d22->AddActionPair(EAIAction::MOVE_TO, FString("plate"));
	hNode_d22->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	hNode_d22->setFluentChanges("bun", (int8)EItemType::ITEM_BREAD, (int8)EItemType::ITEM_BREAD, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_PLATE);

	hNode_d6->AddChild(hNode_d21);
	hNode_d6->AddChild(hNode_d22);

	hNode_d21->AddParent(hNode_d6);
	hNode_d22->AddParent(hNode_d6);

	TSharedPtr<FAOGNode> hNode_d23(new FAOGNode(FString("child"), FString("Taking Burger"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d23->AddActionPair(EAIAction::MOVE_TO, FString("table"));
	hNode_d23->AddActionPair(EAIAction::PICK_UP_DROP, FString("burger"));
	hNode_d23->setFluentChanges("burger", (int8)EItemType::ITEM_HAMBERGER, (int8)EItemType::ITEM_HAMBERGER, (int8)EAbstractLocation::ON_TABLE,
		(int8)EAbstractLocation::BE_HOLD);

	TSharedPtr<FAOGNode> hNode_d24(new FAOGNode(FString("child"), FString("Placing Burger"), -1, EAOGNodeType::TERMINAL_NODE, false, true));
	hNode_d24->AddActionPair(EAIAction::MOVE_TO, FString("table"));
	hNode_d24->AddActionPair(EAIAction::PICK_UP_DROP, FString(""));
	hNode_d24->setFluentChanges("burger", (int8)EItemType::ITEM_HAMBERGER, (int8)EItemType::ITEM_HAMBERGER, (int8)EAbstractLocation::BE_HOLD,
		(int8)EAbstractLocation::ON_DELIVERY_BENCH);

	hNode_d7->AddChild(hNode_d23);
	hNode_d7->AddChild(hNode_d24);

	hNode_d23->AddParent(hNode_d7);
	hNode_d24->AddParent(hNode_d7);

	hNode_d0->Planer = ECOOKTYPE::PLAYER;
	hNode_d1->Planer = ECOOKTYPE::PLAYER;
	hNode_d2->Planer = ECOOKTYPE::PLAYER;
	hNode_d3->Planer = ECOOKTYPE::PLAYER;
	hNode_d4->Planer = ECOOKTYPE::PLAYER;
	hNode_d5->Planer = ECOOKTYPE::PLAYER;
	hNode_d6->Planer = ECOOKTYPE::PLAYER;
	hNode_d7->Planer = ECOOKTYPE::PLAYER;
	hNode_d8->Planer = ECOOKTYPE::PLAYER;
	hNode_d9->Planer = ECOOKTYPE::PLAYER;
	hNode_d10->Planer = ECOOKTYPE::PLAYER;
	hNode_d11->Planer = ECOOKTYPE::PLAYER;
	hNode_d12->Planer = ECOOKTYPE::PLAYER;
	hNode_d13->Planer = ECOOKTYPE::PLAYER;
	hNode_d14->Planer = ECOOKTYPE::PLAYER;
	hNode_d15->Planer = ECOOKTYPE::PLAYER;
	hNode_d16->Planer = ECOOKTYPE::PLAYER;
	hNode_d17->Planer = ECOOKTYPE::PLAYER;
	hNode_d18->Planer = ECOOKTYPE::PLAYER;
	hNode_d19->Planer = ECOOKTYPE::PLAYER;
	hNode_d20->Planer = ECOOKTYPE::PLAYER;
	hNode_d21->Planer = ECOOKTYPE::PLAYER;
	hNode_d22->Planer = ECOOKTYPE::PLAYER;
	hNode_d23->Planer = ECOOKTYPE::PLAYER;
	hNode_d24->Planer = ECOOKTYPE::PLAYER;

	}
	else 
		RobotRootNode = TSharedPtr<FAOGNode>(new FAOGNode());
}
