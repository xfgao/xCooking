// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlanner.h"
//#include "Planner.generated.h"

static struct record
{
	int32 x_pos, y_pos;
	int32 apple1_status, apple2_status, apple3_status;
	int32 bowl_status;
	int32 kind;
};

static const int32 MAX = 99999;
static const int32 NUM_APPLE_STATUS = 6;
static const int32 NUM_BOWL_STATUS = 5;

//UCLASS()
class SIMPLEOVERCOOKED_API APlanner1: public BasePlanner
{
	//GENERATED_BODY()
	
public:	

	int32 mini(int32 a, int32 b)
	{
		if (a > b) return b;
		return a;
	}
	int32 maxi(int32 a, int32 b)
	{
		if (a > b) return a;
		return b;
	}

	int32 b_status[25], b_new_status[25];


	// x_pos: 0_basket, 1_counter, 2_juicer
	// y_pos: 0_counter, 1_cutboard, 2_box, 3_window
	// apple_status: 0_basket, 1_counter, 2_cutboard, 3_counter&sliced, 4_juicer&sliced
	// juicer_status: 0_none, 1_1apple, 2_juice
	// bowl_status: 0_box, 1_counter, 2_juicer&full, 3_counter_full, 4_window&full
	int32 time_apple[NUM_APPLE_STATUS] = { 5, 5, 35, 5, 30, 0 }; // time for changing current apple status to next status
	int32 time_bowl[NUM_BOWL_STATUS] = { 5, 5, 5, 5, 0 };		   // time for changing current bowl status to next status
	int32 disX[3][3] = { {0, 10, 15},				// disX[i][j]: time for X moving from position[i] to position[j] 
					  {10, 0, 15},
					  {15, 15, 0} };
	int32 disY[4][4] = { {0, 15, 20, 20 },		// disY[i][j]: time for Y moving from position[i] to position[j]
					  {15, 0, 20, 20},
					  {20, 20, 0, 30},
					  {20, 20, 30, 0} };
	int32 A[4][3][4][NUM_APPLE_STATUS][NUM_APPLE_STATUS][NUM_APPLE_STATUS][NUM_BOWL_STATUS], B[4][3][4][NUM_APPLE_STATUS][NUM_APPLE_STATUS][NUM_APPLE_STATUS][NUM_BOWL_STATUS]; 		// X_time minimize
	//	A4[3][4][5][5], B4[3][4][5][5];			// max(X_time, Y_time) minimize && try to maintain Y_time as small as possible

	int32 old_xpos, old_ypos, old_apple1, old_apple2, old_apple3, old_bowl, old_kind, old_flag;

	int32 ans_xpos_terminal, ans_ypos_terminal, ans_apple1_terminal, ans_apple2_terminal,
		ans_apple3_terminal, ans_bowl_terminal, ans_kind_terminal, ans_current_time_terminal;


	// Sets default values for this actor's properties
	APlanner1();

public:	

	TArray<FString> results_planner;
	int32 line_output;
	//TArray<FString> output_planner;
	
	record rec[4][3][4][6][6][6][5];

	void find_solutions(int32 ans_xpos, int32 ans_ypos, int32 ans_apple1, int32 ans_apple2, int32 ans_apple3, int32 ans_bowl, int32 ans_kind);

	void Record(int32 kk, int32 x_pos, int32 y_pos, int32 apple1_status, int32 apple2_status, int32 apple3_status,
		int32 bowl_status, int32 time_x, int32 time_y, int32 last_x_pos, int32 last_y_pos, int32 last_apple1_status,
		int32 last_apple2_status, int32 last_apple3_status, int32 last_bowl_status, int32 last_kind);


	void dfs(int32 x_pos, int32 y_pos, int32 apple1_status, int32 apple2_status, int32 apple3_status,
		int32 bowl_status, int32 time_x, int32 time_y, int32 apple1_now, int32 apple2_now, int32 apple3_now, int32 bowl_now,
		int32 last_x_pos, int32 last_y_pos, int32 last_apple1_status, int32 last_apple2_status, int32 last_apple3_status, int32 last_bowl_status, int32 last_kind);



	FString solve(int32 ans_xpos, int32 ans_ypos, int32 ans_apple1, int32 ans_apple2, int32 ans_apple3, int32 ans_bowl, int32 ans_kind, int32 current_time);

	~APlanner1() {}

};
