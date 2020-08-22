// Fill out your copyright notice in the Description page of Project Settings.


#include "Planner.h"

APlanner1::APlanner1() {
}

void APlanner1::Record(int32 kk, int32 x_pos, int32 y_pos, int32 apple1_status, int32 apple2_status, int32 apple3_status, 
	int32 bowl_status, int32 time_x, int32 time_y, int32 last_x_pos, int32 last_y_pos, int32 last_apple1_status, int32 last_apple2_status, int32 last_apple3_status, 
	int32 last_bowl_status, int32 last_kind)
{
	A[kk][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status] = time_x;
	B[kk][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status] = time_y;
	rec[kk][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status].x_pos = last_x_pos;
	rec[kk][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status].y_pos = last_y_pos;
	rec[kk][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status].apple1_status = last_apple1_status;
	rec[kk][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status].apple2_status = last_apple2_status;
	rec[kk][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status].apple3_status = last_apple3_status;
	rec[kk][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status].bowl_status = last_bowl_status;
	rec[kk][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status].kind = last_kind;
}

void APlanner1::find_solutions(int32 ans_xpos, int32 ans_ypos, int32 ans_apple1, int32 ans_apple2, int32 ans_apple3, int32 ans_bowl, int32 ans_kind)
{
	
	if (ans_xpos == ans_xpos_terminal && ans_ypos == ans_ypos_terminal && ans_apple1 == ans_apple1_terminal &&
		ans_apple2 == ans_apple2_terminal && ans_apple3 == ans_apple3_terminal && ans_bowl == ans_bowl_terminal) return;

	int new_xpos, new_ypos, new_apple1, new_apple2, new_apple3, new_bowl, new_kind;
	old_flag = 1;
	new_xpos = rec[ans_kind][ans_xpos][ans_ypos][ans_apple1][ans_apple2][ans_apple3][ans_bowl].x_pos;
	new_ypos = rec[ans_kind][ans_xpos][ans_ypos][ans_apple1][ans_apple2][ans_apple3][ans_bowl].y_pos;
	new_apple1 = rec[ans_kind][ans_xpos][ans_ypos][ans_apple1][ans_apple2][ans_apple3][ans_bowl].apple1_status;
	new_apple2 = rec[ans_kind][ans_xpos][ans_ypos][ans_apple1][ans_apple2][ans_apple3][ans_bowl].apple2_status;
	new_apple3 = rec[ans_kind][ans_xpos][ans_ypos][ans_apple1][ans_apple2][ans_apple3][ans_bowl].apple3_status;
	new_bowl = rec[ans_kind][ans_xpos][ans_ypos][ans_apple1][ans_apple2][ans_apple3][ans_bowl].bowl_status;
	new_kind = rec[ans_kind][ans_xpos][ans_ypos][ans_apple1][ans_apple2][ans_apple3][ans_bowl].kind;

	if (new_apple1 != ans_apple1)
	{
		if (new_apple1 == 0)
		{
			line_output++;
			output_planner.Add("Getting Apple1");
			output_planner.Add("Robot");
		}


		if (new_apple1 == 1)
		{
			line_output++;
			output_planner.Add("Preparing Apple1");
			output_planner.Add("Player");
		}
		if (new_apple1 == 2)
		{
			line_output++;
			output_planner.Add("Handing over Apple1");
			output_planner.Add("Player");
		}
		if (new_apple1 == 3)
		{
			line_output++;
			output_planner.Add("Getting Apple Slices1");
			output_planner.Add("Robot");
		}
		if (new_apple1 == 4)
		{
			line_output++;
			output_planner.Add("Using Juicer");
			output_planner.Add("Robot");
		}
		line_output++;
		output_planner.Add("Apple1");
	}
	if (new_apple2 != ans_apple2)
	{
		if (new_apple2 == 0)
		{
			line_output++;
			output_planner.Add("Getting Apple2");
			output_planner.Add("Robot");
		}


		if (new_apple2 == 1)
		{
			line_output++;
			output_planner.Add( "Preparing Apple2");
			output_planner.Add("Player");
		}
		if (new_apple2 == 2)
		{
			line_output++;
			output_planner.Add("Handing over Apple2");
			output_planner.Add("Player");

		}
		if (new_apple2 == 3)
		{
			line_output++;
			output_planner.Add( "Getting Apple Slices2");
			output_planner.Add("Robot");
		}
		if (new_apple2 == 4)
		{
			line_output++;

			output_planner.Add( "Using Juicer");
			output_planner.Add("Robot");
		}
		line_output++;

		output_planner.Add("Apple2");
	}
	if (new_apple3 != ans_apple3)
	{

		if (new_apple3 == 0)
		{
			line_output++;
			output_planner .Add( FString("Getting Apple3"));
			output_planner.Add("Robot");
		}


		if (new_apple3 == 1)
		{
			line_output++;
			output_planner.Add(FString("Preparing Apple3"));
			output_planner.Add("Player");
		}
		if (new_apple3 == 2)
		{
			line_output++;
			output_planner.Add(FString("Handing over Apple3"));
			output_planner.Add("Player");
		}
		if (new_apple3 == 3)
		{
			line_output++;
			output_planner.Add(FString("Getting Apple Slices3"));
			output_planner.Add("Robot");
		}
		if (new_apple3 == 4)
		{
			line_output++;
			output_planner.Add(FString("Using Juicer"));
			output_planner.Add("Robot");
		}
		line_output++;
	
		output_planner.Add(FString("Apple3"));
	}
	if (new_bowl != ans_bowl)
	{

		if (new_bowl == 0)
		{
			line_output++;
			output_planner.Add(FString("Handing Over Bowl"));
			output_planner.Add("Player");
		}
		if (new_bowl == 1)
		{
			line_output++;
			output_planner.Add(FString("Handing Over Juice"));
			output_planner.Add("Robot");
		}
		if (new_bowl == 2)
		{
			line_output++;
			output_planner.Add(FString("Getting Juice"));
			output_planner.Add("Robot");
		}

		if (new_bowl == 3)
		{
			line_output++;
			output_planner.Add(FString("Delivering Juice"));
			output_planner.Add("Player");
		}
		line_output++;
	
		output_planner.Add(FString("bowl"));
	}

	old_xpos = ans_xpos;
	old_ypos = ans_ypos;
	old_apple1 = ans_apple1;
	old_apple2 = ans_apple2;
	old_apple3 = ans_apple3;
	old_bowl = ans_bowl;
	old_kind = ans_kind;
	//	printf("new : kind = %d, x_pos = %d, y_pos = %d, apple1_status = %d, bowl_status = %d", new_kind, new_xpos, new_ypos, new_apple, new_bowl);
	find_solutions(new_xpos, new_ypos, new_apple1, new_apple2, new_apple3, new_bowl, new_kind);
}


void APlanner1::dfs(int32 x_pos, int32 y_pos, int32 apple1_status, int32 apple2_status, int32 apple3_status, int32 bowl_status,
	int32 time_x, int32 time_y, int32 apple1_now, int32 apple2_now, int32 apple3_now, int32 bowl_now, int32 last_x_pos, int32 last_y_pos, int32 last_apple1_status,
	int32 last_apple2_status, int32 last_apple3_status, int32 last_bowl_status, int32 last_kind)
{
	int kind = 0;
	if (time_x < A[1][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status])
	{
		Record(1, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, time_x, time_y, last_x_pos, last_y_pos, last_apple1_status, last_apple2_status, last_apple3_status, last_bowl_status, last_kind);
		kind = 1;
	}
	if (time_y < B[2][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status])
	{
		Record(2, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, time_x, time_y, last_x_pos, last_y_pos, last_apple1_status, last_apple2_status, last_apple3_status, last_bowl_status, last_kind);
		kind = 2;
	}
	if (maxi(time_x, time_y) < maxi(A[3][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status], B[3][x_pos][y_pos][apple1_status][apple2_status][apple3_status][bowl_status]))
	{
		Record(3, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, time_x, time_y, last_x_pos, last_y_pos, last_apple1_status, last_apple2_status, last_apple3_status, last_bowl_status, last_kind);
		kind = 3;
	}
	/*if(maxi(time_x, time_y) < maxi(A4[x_pos][y_pos][apple1_status][bowl_status], B4[x_pos][y_pos][apple1_status][bowl_status]))
	{
		A4[x_pos][y_pos][apple1_status][bowl_status] = time_x;
		B4[x_pos][y_pos][apple1_status][bowl_status] = time_y;
		flag_continue = true;
	}*/
	if (!kind) return;
	if (bowl_status == 4) return;

	// action on apple1
	if (apple1_status == 0)
	{
		dfs(1, y_pos, 1, apple2_status, apple3_status, bowl_status, maxi(time_x, apple1_now) + disX[x_pos][0] + disX[0][1] + time_apple[0], time_y, maxi(time_x, apple1_now) + disX[x_pos][0] + disX[0][1] + time_apple[0], apple2_now, apple3_now, bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (apple1_status == 1)
	{
		dfs(x_pos, 1, 2, apple2_status, apple3_status, bowl_status, time_x, maxi(time_y, apple1_now) + disY[y_pos][0] + disY[0][1] + time_apple[1], maxi(time_y, apple1_now) + disY[y_pos][0] + disY[0][1] + time_apple[1], apple2_now, apple3_now, bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (apple1_status == 2)
	{
		dfs(x_pos, 0, 3, apple2_status, apple3_status, bowl_status, time_x, maxi(time_y, apple1_now) + disY[y_pos][1] + disY[1][0] + time_apple[2], maxi(time_y, apple1_now) + disY[y_pos][1] + disY[1][0] + time_apple[2], apple2_now, apple3_now, bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (apple1_status == 3)
	{
		dfs(2, y_pos, 4, apple2_status, apple3_status, bowl_status, maxi(time_x, apple1_now) + disX[x_pos][1] + disX[1][2] + time_apple[3], time_y, maxi(time_x, apple1_now) + disX[x_pos][1] + disX[1][2] + time_apple[3], apple2_now, apple3_now, bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	// action on apple2
	if (apple2_status == 0)
	{
		dfs(1, y_pos, apple1_status, 1, apple3_status, bowl_status, maxi(time_x, apple2_now) + disX[x_pos][0] + disX[0][1] + time_apple[0], time_y, apple1_now, maxi(time_x, apple2_now) + disX[x_pos][0] + disX[0][1] + time_apple[0], apple3_now, bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (apple2_status == 1)
	{
		dfs(x_pos, 1, apple1_status, 2, apple3_status, bowl_status, time_x, maxi(time_y, apple2_now) + disY[y_pos][0] + disY[0][1] + time_apple[1], apple1_now, maxi(time_y, apple2_now) + disY[y_pos][0] + disY[0][1] + time_apple[1], apple3_now, bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (apple2_status == 2)
	{
		dfs(x_pos, 0, apple1_status, 3, apple3_status, bowl_status, time_x, maxi(time_y, apple2_now) + disY[y_pos][1] + disY[1][0] + time_apple[2], apple1_now, maxi(time_y, apple2_now) + disY[y_pos][1] + disY[1][0] + time_apple[2], apple3_now, bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (apple2_status == 3)
	{
		dfs(2, y_pos, apple1_status, 4, apple3_status, bowl_status, maxi(time_x, apple2_now) + disX[x_pos][1] + disX[1][2] + time_apple[3], time_y, apple1_now, maxi(time_x, apple2_now) + disX[x_pos][1] + disX[1][2] + time_apple[3], apple3_now, bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	// action on apple3
	if (apple3_status == 0)
	{
		dfs(1, y_pos, apple1_status, apple2_status, 1, bowl_status, maxi(time_x, apple3_now) + disX[x_pos][0] + disX[0][1] + time_apple[0], time_y, apple1_now, apple2_now, maxi(time_x, apple3_now) + disX[x_pos][0] + disX[0][1] + time_apple[0], bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (apple3_status == 1)
	{
		dfs(x_pos, 1, apple1_status, apple2_status, 2, bowl_status, time_x, maxi(time_y, apple3_now) + disY[y_pos][0] + disY[0][1] + time_apple[1], apple1_now, apple2_now, maxi(time_y, apple3_now) + disY[y_pos][0] + disY[0][1] + time_apple[1], bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (apple3_status == 2)
	{
		dfs(x_pos, 0, apple1_status, apple2_status, 3, bowl_status, time_x, maxi(time_y, apple3_now) + disY[y_pos][1] + disY[1][0] + time_apple[2], apple1_now, apple2_now, maxi(time_y, apple3_now) + disY[y_pos][1] + disY[1][0] + time_apple[2], bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (apple3_status == 3)
	{
		dfs(2, y_pos, apple1_status, apple2_status, 4, bowl_status, maxi(time_x, apple3_now) + disX[x_pos][1] + disX[1][2] + time_apple[3], time_y, apple1_now, apple2_now, maxi(time_x, apple3_now) + disX[x_pos][1] + disX[1][2] + time_apple[3], bowl_now, x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}

	// action on juicer 
	if (apple1_status == 4 && apple2_status == 4 && apple3_status == 4)
	{
		int32 time_of_juice;
		time_of_juice = maxi(time_x, maxi(apple1_now, maxi(apple2_now, apple3_now))) + disX[x_pos][2] + time_apple[4];
		dfs(2, y_pos, 5, 5, 5, bowl_status, time_of_juice, time_y, time_of_juice, time_of_juice, time_of_juice, bowl_now, x_pos, y_pos, 4, 4, 4, bowl_status, kind);
	}

	// action on bowl
	if (bowl_status == 0)
	{
		dfs(x_pos, 0, apple1_status, apple2_status, apple3_status, 1, time_x, maxi(time_y, bowl_now) + disY[y_pos][2] + disY[2][0] + time_bowl[0], apple1_now, apple2_now, apple3_now, maxi(time_y, bowl_now) + disY[y_pos][2] + disY[2][0] + time_bowl[0], x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (bowl_status == 1)
	{
		if (apple1_status == 5 && apple2_status == 5 && apple3_status == 5)
			dfs(2, y_pos, apple1_status, apple2_status, apple3_status, 2, maxi(time_x, bowl_now) + disX[x_pos][1] + disX[1][2] + time_bowl[1], time_y, apple1_now, apple2_now, apple3_now, maxi(time_x, bowl_now) + disX[x_pos][1] + disX[1][2] + time_bowl[1], x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (bowl_status == 2)
	{
		dfs(1, y_pos, apple1_status, apple2_status, apple3_status, 3, maxi(time_x, bowl_now) + disX[x_pos][2] + disX[2][1] + time_bowl[2], time_y, apple1_now, apple2_now, apple3_now, maxi(time_x, bowl_now) + disX[x_pos][2] + disX[2][1] + time_bowl[2], x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
	if (bowl_status == 3)
	{
		dfs(x_pos, 3, apple1_status, apple2_status, apple3_status, 4, time_x, maxi(time_y, bowl_now) + disY[y_pos][0] + disY[0][3] + time_bowl[3], apple1_now, apple2_now, apple3_now, maxi(time_y, bowl_now) + disY[y_pos][0] + disY[0][3] + time_bowl[3], x_pos, y_pos, apple1_status, apple2_status, apple3_status, bowl_status, kind);
	}
}


FString APlanner1::solve(int32 ans_xpos_cur, int32 ans_ypos_cur, int32 ans_apple1_cur, int32 ans_apple2_cur, int32 ans_apple3_cur, int32 ans_bowl_cur, int32 ans_kind_cur, int32 current_time)
{
	ans_xpos_terminal = ans_xpos_cur;
	ans_ypos_terminal = ans_ypos_cur;
	ans_apple1_terminal = ans_apple1_cur;
	ans_apple2_terminal = ans_apple2_cur;
	ans_apple3_terminal = ans_apple3_cur; 
	ans_bowl_terminal = ans_bowl_cur;
	ans_kind_terminal = ans_kind_cur;
	ans_current_time_terminal = current_time;
	output_planner.Empty();
	for (int32 ix = 0; ix <= 2; ix++)
		for (int32 iy = 0; iy <= 3; iy++)
			for (int32 iapple1 = 0; iapple1 < NUM_APPLE_STATUS; iapple1++)
				for (int32 iapple2 = 0; iapple2 < NUM_APPLE_STATUS; iapple2++)
					for (int32 iapple3 = 0; iapple3 < NUM_APPLE_STATUS; iapple3++)
						for (int32 ibowl = 0; ibowl < NUM_BOWL_STATUS; ibowl++)
							for (int32 kk = 1; kk <= 3; kk++)
							{
								A[kk][ix][iy][iapple1][iapple2][iapple3][ibowl] = MAX;
								B[kk][ix][iy][iapple1][iapple2][iapple3][ibowl] = MAX;
								/*A4[ix][iy][iapple][ibowl] = MAX;
								B4[ix][iy][iapple][ibowl] = MAX;*/
							}

	dfs(ans_xpos_cur, ans_ypos_cur, ans_apple1_cur, ans_apple2_cur, ans_apple3_cur, ans_bowl_cur, current_time,
		current_time, current_time, current_time, current_time, current_time, ans_xpos_cur,
		ans_ypos_cur, ans_apple1_cur, ans_apple2_cur, ans_apple3_cur, ans_bowl_cur, 1);

	int ans = MAX, ans_xpos, ans_ypos, ans_apple1, ans_apple2, ans_apple3, ans_bowl, ans_kind;
	for (int32 ix = 0; ix <= 2; ix++)
		for (int32 iy = 0; iy <= 3; iy++)
			for (int32 iapple1 = 0; iapple1 < NUM_APPLE_STATUS; iapple1++)
				for (int32 iapple2 = 0; iapple2 < NUM_APPLE_STATUS; iapple2++)
					for (int32 iapple3 = 0; iapple3 < NUM_APPLE_STATUS; iapple3++)
						for (int32 kk = 1; kk <= 3; kk++)
							if (maxi(A[kk][ix][iy][iapple1][iapple2][iapple3][4], B[kk][ix][iy][iapple1][iapple2][iapple3][4]) < ans)
							{
								ans = maxi(A[kk][ix][iy][iapple1][iapple2][iapple3][4], B[kk][ix][iy][iapple1][iapple2][iapple3][4]);
								ans_xpos = ix;
								ans_ypos = iy;
								ans_apple1 = iapple1;
								ans_apple2 = iapple2;
								ans_apple3 = iapple3;
								ans_bowl = 4;
								ans_kind = kk;
							}

	line_output = 0;
	find_solutions(ans_xpos, ans_ypos, ans_apple1, ans_apple2, ans_apple3, ans_bowl, ans_kind);


	//for (int ix = 0; ix <= 2; ix++)
	//	for (int iy = 0; iy <= 3; iy++)
	//		for (int iapple1 = 0; iapple1 < 6; iapple1++)
	//			for (int iapple2 = 0; iapple2 < 6; iapple2++)
	//				for (int iapple3 = 0; iapple3 < 6; iapple3++)
	//					for (int ibowl = 0; ibowl < 5; ibowl++)
	//						for (int kk = 1; kk <= 3; kk++)
	//						{
	//							A[kk][ix][iy][iapple1][iapple2][iapple3][ibowl] = 99999;
	//							B[kk][ix][iy][iapple1][iapple2][iapple3][ibowl] = 99999;
	//							/*A4[ix][iy][iapple][ibowl] = MAX;
	//							B4[ix][iy][iapple][ibowl] = MAX;*/
	//						}
	//
	//dfs(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
	//
	//int ans = 99999, ans_xpos, ans_ypos, ans_apple1, ans_apple2, ans_apple3, ans_bowl, ans_kind;
	//for (int ix = 0; ix <= 2; ix++)
	//	for (int iy = 0; iy <= 3; iy++)
	//		for (int iapple1 = 0; iapple1 < 6; iapple1++)
	//			for (int iapple2 = 0; iapple2 < 6; iapple2++)
	//				for (int iapple3 = 0; iapple3 < 6; iapple3++)
	//					for (int kk = 1; kk <= 3; kk++)
	//						if (maxi(A[kk][ix][iy][iapple1][iapple2][iapple3][4], B[kk][ix][iy][iapple1][iapple2][iapple3][4]) < ans)
	//						{
	//							ans = maxi(A[kk][ix][iy][iapple1][iapple2][iapple3][4], B[kk][ix][iy][iapple1][iapple2][iapple3][4]);
	//							ans_xpos = ix;
	//							ans_ypos = iy;
	//							ans_apple1 = iapple1;
	//							ans_apple2 = iapple2;
	//							ans_apple3 = iapple3;
	//							ans_bowl = 4;
	//							ans_kind = kk;
	//						}

	//line_output = 0;

	//find_solutions(ans_xpos, ans_ypos, ans_apple1, ans_apple2, ans_apple3, ans_bowl, ans_kind);

	return FString("");
}

