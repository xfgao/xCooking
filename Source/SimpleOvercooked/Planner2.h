// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePlanner.h"
//#include "Planner.generated.h"

#define num_bowl_status 5*2*2*2*2 



static struct recor
{
	short x_pos, y_pos;
	short obj1_status, obj2_status, obj3_status, obj4_status, obj5_status;
	short kind;
};

static const int NUM_LETTUCE_STATUS = 3;
static const int NUM_TOMATO_STATUS = 3;
static const int NUM_BUN_STATUS = 2;
static const int NUM_BEEF_STATUS = 4;

//static const int NUM_BOWL_STATUS = 5 * 2 * 2 * 2 * 2;

//UCLASS()
class SIMPLEOVERCOOKED_API APlanner2: public BasePlanner
{
	//GENERATED_BODY()
	
public:	
	int b_status[25], b_new_status[25];
	int dis[6][6] = { {0, 50, 110, 110, 70, 60},				// disX[i][j]: time for X, Y moving from position[i] to position[j] 
			  {50, 0, 50, 50, 50, 110},
			  {110, 50, 0, 40, 40, 130},
			  {110, 50, 40, 0, 40, 130},
			  {70, 50, 40, 40, 0, 40},
			  {60, 110, 40, 130, 40, 0} };

	int loc[5][4] = { {7, 7, 7, 7},
				 {0, 1, 4, 7},
				 {0, 1, 4, 7},
				 {0, 4, 7, 7},
				 {0, 1, 2, 4}
	};
	int tx_obj[5][4] = { {0,0,0,0},
					{100, 10, 0, 0},
					{100, 10, 0, 0},
					{10, 0, 0, 0},
					{100, 100, 10, 0} };
	int ty_obj[5][4] = { {0,0,0,0},
					{100, 10, 0, 0},
					{100, 10, 0, 0},
					{10, 0, 0, 0},
					{100, 100, 10, 0} };
	int time_pick_up = 10;
	int A[4][7][7][NUM_LETTUCE_STATUS + 5][NUM_TOMATO_STATUS + 5][NUM_BUN_STATUS + 5][NUM_BEEF_STATUS + 5][num_bowl_status + 5], B[4][6][6][NUM_LETTUCE_STATUS + 5][NUM_TOMATO_STATUS + 5][NUM_BUN_STATUS + 5][NUM_BEEF_STATUS + 5][num_bowl_status + 5]; 		// X_time minimize

	int old_xpos, old_ypos, old_obj1, old_obj2, old_obj3, old_obj4, old_obj5, old_kind, old_flag;
	int ans_xpos_terminal, ans_ypos_terminal, ans_obj1_terminal, ans_obj2_terminal,
		ans_obj3_terminal, ans_obj4_terminal, ans_obj5_terminal;

	recor rec[4][7][7][NUM_LETTUCE_STATUS + 5][NUM_TOMATO_STATUS + 5][NUM_BUN_STATUS + 5][NUM_BEEF_STATUS + 5][80 + 5];


	APlanner2();

public:
	
	TArray<FString> output_planner;
	int line_output;

	int DecimalToBinary(int num);
	int BinaryToDecimal(int loc, int in_bowl[]);
	int find_bowl_loc(int b0, int b1, int b2);
	int mini(int a, int b);
	int maxi(int a, int b);
	void Record(int kk, int x_pos, int y_pos, int obj1_status, int obj2_status, int obj3_status, int obj4_status, int obj5_status, int time_x, int time_y, int last_x_pos, int last_y_pos, int last_obj1_status, int last_obj2_status, int last_obj3_status, int last_obj4_status, int last_obj5_status, int last_kind);
	void dfs(int x_pos, int y_pos, int obj1_status, int obj2_status, int obj3_status, int obj4_status, int obj5_status, int time_x, int time_y, int obj1_now, int obj2_now, int obj3_now, int obj4_now, int obj5_now, int last_x_pos, int last_y_pos, int last_obj1_status, int last_obj2_status, int last_obj3_status, int last_obj4_status, int last_obj5_status, int last_kind);
	void find_solution(int ans_xpos, int ans_ypos, int ans_obj1, int ans_obj2, int ans_obj3, int ans_obj4, int ans_obj5, int ans_kind);

	FString solve(int x_pos, int y_pos, int obj1_status, int obj2_status, int obj3_status, int obj4_status, int obj5_status, int last_kind, int cur_time);

};
