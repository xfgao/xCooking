#include "Planner2.h"

#define max 999999

APlanner2::APlanner2() {
}

int APlanner2::DecimalToBinary(int num)
{											//might be useful in the future status decoding
	int i = 0;
	for (int kk = 0; kk <= 6; kk++)
		b_status[kk] = 0;
	while (num != 0)
	{

		b_status[i] = num % 2;
		i++;
		num /= 2;
	}
	//	printf("In DecimalToBinary:\n");
	//	for(int j = 5; j >= 0; j--)printf("%d", b_status[j]);
	//	printf("\n");
	return i;
}
int APlanner2::BinaryToDecimal(int loc, int in_bowl[])				//might be useful in the future status encoding
	//										 as the number of objects increases, the status will increase, then it will be hard to represent all status in the form of array
{
	if (loc == 1) {
		b_new_status[6] = 0;
		b_new_status[5] = 0;
		b_new_status[4] = 0;
	}
	if (loc == 2) {
		b_new_status[6] = 0;
		b_new_status[5] = 0;
		b_new_status[4] = 1;
	}
	if (loc == 3) {
		b_new_status[6] = 0;
		b_new_status[5] = 1;
		b_new_status[4] = 0;
	}
	if (loc == 4) {
		b_new_status[6] = 0;
		b_new_status[5] = 1;
		b_new_status[4] = 1;
	}
	if (loc == 5) {
		b_new_status[6] = 1;
		b_new_status[6] = 1;
		b_new_status[5] = 0;
		b_new_status[4] = 0;
	}
	//	printf("in BinaryToDec: %d \n", loc);
	for (int i = 3; i >= 0; i--)
	{

		b_new_status[i] = in_bowl[i + 1];

	}
	int num = 0, power = 1;

	for (int i = 0; i <= 6; i++)
	{
		num += power * b_new_status[i];
		power *= 2;
	}
	//	 for(int i = 5; i >= 0; i--)
	//	 	printf("b_new_status[%d] = %d\n", i, b_new_status[i]);
	//	printf("num = %d\n", num);
	return num;
}

int APlanner2::find_bowl_loc(int b0, int b1, int b2)
{
	if (b0 == 1)return 5;
	if (b1 == 0 && b2 == 0)	return 1;
	if (b1 == 0 && b2 == 1)  return 2;
	if (b1 == 1 && b2 == 0)  return 3;
	if (b1 == 1 && b2 == 1)  return 4;

	return 0;
}
int APlanner2::mini(int a, int b)
{
	if (a > b) return b;
	return a;
}
int APlanner2::maxi(int a, int b)
{
	if (a > b) return a;
	return b;
}
void APlanner2::Record(int kk, int x_pos, int y_pos, int obj1_status, int obj2_status, int obj3_status, int obj4_status, int obj5_status, int time_x, int time_y, int last_x_pos, int last_y_pos, int last_obj1_status, int last_obj2_status, int last_obj3_status, int last_obj4_status, int last_obj5_status, int last_kind)
{
	A[kk][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status] = time_x;
	B[kk][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status] = time_y;
	rec[kk][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status].x_pos = last_x_pos;
	rec[kk][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status].y_pos = last_y_pos;
	rec[kk][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status].obj1_status = last_obj1_status;
	rec[kk][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status].obj2_status = last_obj2_status;
	rec[kk][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status].obj3_status = last_obj3_status;
	rec[kk][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status].obj4_status = last_obj4_status;
	rec[kk][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status].obj5_status = last_obj5_status;
	rec[kk][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status].kind = last_kind;
}
void APlanner2::dfs(int x_pos, int y_pos, int obj1_status, int obj2_status, int obj3_status, int obj4_status, int obj5_status, int time_x, int time_y, int obj1_now, int obj2_now, int obj3_now, int obj4_now, int obj5_now, int last_x_pos, int last_y_pos, int last_obj1_status, int last_obj2_status, int last_obj3_status, int last_obj4_status, int last_obj5_status, int last_kind)
{
	int kind = 0;
	if (time_x < A[1][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status])
	{
		Record(1, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, time_x, time_y, last_x_pos, last_y_pos, last_obj1_status, last_obj2_status, last_obj3_status, last_obj4_status, last_obj5_status, last_kind);
		kind = 1;
	}
	if (time_y < B[2][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status])
	{
		Record(2, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, time_x, time_y, last_x_pos, last_y_pos, last_obj1_status, last_obj2_status, last_obj3_status, last_obj4_status, last_obj5_status, last_kind);
		kind = 2;
	}
	if (maxi(time_x, time_y) < maxi(A[3][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status], B[3][x_pos][y_pos][obj1_status][obj2_status][obj3_status][obj4_status][obj5_status]))
	{
		Record(3, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, time_x, time_y, last_x_pos, last_y_pos, last_obj1_status, last_obj2_status, last_obj3_status, last_obj4_status, last_obj5_status, last_kind);
		kind = 3;
	}
	/*if(maxi(time_x, time_y) < maxi(A4[x_pos][y_pos][obj1_status][obj5_status], B4[x_pos][y_pos][obj1_status][obj5_status]))
	{
		A4[x_pos][y_pos][obj1_status][obj5_status] = time_x;
		B4[x_pos][y_pos][obj1_status][obj5_status] = time_y;
		flag_continue = true;
	}*/
	int in_bowl[5], bowl_code[7];    // describe whether each item is in the bowl

	DecimalToBinary(obj5_status);
	for (int ii = 0; ii <= 6; ii++)
		bowl_code[ii] = b_status[ii];

	for (int ii = 1; ii <= 4; ii++)
		in_bowl[ii] = bowl_code[ii - 1];
	//	printf("In dfs:\n");
	//	printf("bowl_status = %d, %d %d %d %d \n", obj5_status, in_bowl[1], in_bowl[2], in_bowl[3], in_bowl[4]);
	//	printf("x_pos = %d, y_pos = %d, obj1 = %d, obj2 = %d, obj3 = %d, obj4 = %d \n", x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status);

	if (!kind) {//printf("haha\n"); 
		return;
	}

	if (bowl_code[6] == 1 && in_bowl[1] && in_bowl[2] && in_bowl[3] && in_bowl[4]) return;

	// action on obj1
	if (in_bowl[1] == 0)
	{
		for (int sta1 = 0; sta1 < 2; sta1++)
			if (obj1_status == sta1)
			{
				if (sta1 == 0)
				{
					int co = 0;
					if (obj1_status == 1) co++;
					if (obj2_status == 1) co++;
					if (obj4_status == 1) co++;
					if (co == 2)
						continue;
				}
				// x performs an action
				int ct;
				ct = maxi(time_x, obj1_now) + dis[x_pos][loc[1][sta1]] + dis[loc[1][sta1]][loc[1][sta1 + 1]] + tx_obj[1][sta1];
				dfs(loc[1][sta1 + 1], y_pos, sta1 + 1, obj2_status, obj3_status, obj4_status, obj5_status, ct, time_y, ct, obj2_now, obj3_now, obj4_now, obj5_now, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

				// y performs an action
				ct = maxi(time_y, obj1_now) + dis[y_pos][loc[1][sta1]] + dis[loc[1][sta1]][loc[1][sta1 + 1]] + ty_obj[1][sta1];
				dfs(x_pos, loc[1][sta1 + 1], sta1 + 1, obj2_status, obj3_status, obj4_status, obj5_status, time_x, ct, ct, obj2_now, obj3_now, obj4_now, obj5_now, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

			}
	}
	// action on obj2
	if (in_bowl[2] == 0)
	{
		for (int sta2 = 0; sta2 < 2; sta2++)
			if (obj2_status == sta2)
			{
				if (sta2 == 0)
				{
					int co = 0;
					if (obj1_status == 1) co++;
					if (obj2_status == 1) co++;
					if (obj4_status == 1) co++;
					if (co == 2)
						continue;
				}
				// x performs an action
				int ct;
				ct = maxi(time_x, obj2_now) + dis[x_pos][loc[2][sta2]] + dis[loc[2][sta2]][loc[2][sta2 + 1]] + tx_obj[2][sta2];
				dfs(loc[2][sta2 + 1], y_pos, obj1_status, sta2 + 1, obj3_status, obj4_status, obj5_status, ct, time_y, obj1_now, ct, obj3_now, obj4_now, obj5_now, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

				// y performs an action
				ct = maxi(time_y, obj2_now) + dis[y_pos][loc[2][sta2]] + dis[loc[2][sta2]][loc[2][sta2 + 1]] + ty_obj[2][sta2];
				dfs(x_pos, loc[2][sta2 + 1], obj1_status, sta2 + 1, obj3_status, obj4_status, obj5_status, time_x, ct, obj1_now, ct, obj3_now, obj4_now, obj5_now, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

			}
	}
	// action on obj3
	if (in_bowl[3] == 0)
	{
		for (int sta3 = 0; sta3 < 1; sta3++)
			if (obj3_status == sta3)
			{
				// x performs an action
				int ct;
				ct = maxi(time_x, obj3_now) + dis[x_pos][loc[3][sta3]] + dis[loc[3][sta3]][loc[3][sta3 + 1]] + tx_obj[3][sta3];
				dfs(loc[3][sta3 + 1], y_pos, obj1_status, obj2_status, sta3 + 1, obj4_status, obj5_status, ct, time_y, obj1_now, obj2_now, ct, obj4_now, obj5_now, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

				// y performs an action
				ct = maxi(time_y, obj3_now) + dis[y_pos][loc[3][sta3]] + dis[loc[3][sta3]][loc[3][sta3 + 1]] + ty_obj[3][sta3];
				dfs(x_pos, loc[3][sta3 + 1], obj1_status, obj2_status, sta3 + 1, obj4_status, obj5_status, time_x, ct, obj1_now, obj2_now, ct, obj4_now, obj5_now, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

			}
	}
	// action on obj4
	if (in_bowl[4] == 0)
	{
		for (int sta4 = 0; sta4 < 3; sta4++)
			if (obj4_status == sta4)
			{
				if (sta4 == 0)
				{
					int co = 0;
					if (obj1_status == 1) co++;
					if (obj2_status == 1) co++;
					if (obj4_status == 1) co++;
					if (co == 2)
						continue;
				}
				// x performs an action
				int ct;
				ct = maxi(time_x, obj4_now) + dis[x_pos][loc[4][sta4]] + dis[loc[4][sta4]][loc[4][sta4 + 1]] + tx_obj[4][sta4];
				dfs(loc[4][sta4 + 1], y_pos, obj1_status, obj2_status, obj3_status, sta4 + 1, obj5_status, ct, time_y, obj1_now, obj2_now, obj3_now, ct, obj5_now, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

				// y performs an action
				ct = maxi(time_y, obj4_now) + dis[y_pos][loc[4][sta4]] + dis[loc[4][sta4]][loc[4][sta4 + 1]] + ty_obj[4][sta4];
				dfs(x_pos, loc[4][sta4 + 1], obj1_status, obj2_status, obj3_status, sta4 + 1, obj5_status, time_x, ct, obj1_now, obj2_now, obj3_now, ct, obj5_now, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);
			}
	}
	//action on bowl
	//printf("again bowl_status = %d, %d %d %d %d \n", obj5_status, in_bowl[1], in_bowl[2], in_bowl[3], in_bowl[4]);
	int loc_bowl, new_bowl_status;
	loc_bowl = find_bowl_loc(bowl_code[6], bowl_code[5], bowl_code[4]);
	if (obj1_status >= 1 && in_bowl[1] == 0)
	{
		//	printf("haha1\n");
		in_bowl[1] = 1;
		//x pick the bowl

		new_bowl_status = BinaryToDecimal(loc[1][obj1_status], in_bowl);
		//	printf("new_bowl = %d\n", new_bowl_status);
		int ct;
		ct = maxi(time_x, obj5_now) + dis[x_pos][loc_bowl] + dis[loc_bowl][loc[1][obj1_status]] + time_pick_up;
		dfs(loc[1][obj1_status], y_pos, obj1_status, obj2_status, obj3_status, obj4_status, new_bowl_status, ct, time_y, obj1_now, obj2_now, obj3_now, obj4_now, ct, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

		//y pick the bowl
		ct = maxi(time_y, obj5_now) + dis[y_pos][loc_bowl] + dis[loc_bowl][loc[1][obj1_status]] + time_pick_up;
		dfs(x_pos, loc[1][obj1_status], obj1_status, obj2_status, obj3_status, obj4_status, new_bowl_status, time_x, ct, obj1_now, obj2_now, obj3_now, obj4_now, ct, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

		in_bowl[1] = 0;
	}

	if (obj2_status >= 1 && in_bowl[2] == 0)
	{
		in_bowl[2] = 1;
		//x pick the bowl
		//	printf("haha2\n");
		new_bowl_status = BinaryToDecimal(loc[2][obj2_status], in_bowl);
		int ct;
		ct = maxi(time_x, obj5_now) + dis[x_pos][loc_bowl] + dis[loc_bowl][loc[2][obj2_status]] + time_pick_up;
		dfs(loc[2][obj2_status], y_pos, obj1_status, obj2_status, obj3_status, obj4_status, new_bowl_status, ct, time_y, obj1_now, obj2_now, obj3_now, obj4_now, ct, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

		//y pick the bowl
		ct = maxi(time_y, obj5_now) + dis[y_pos][loc_bowl] + dis[loc_bowl][loc[2][obj2_status]] + time_pick_up;
		dfs(x_pos, loc[2][obj2_status], obj1_status, obj2_status, obj3_status, obj4_status, new_bowl_status, time_x, ct, obj1_now, obj2_now, obj3_now, obj4_now, ct, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);
		in_bowl[2] = 0;
	}
	if (obj3_status == 1 && in_bowl[3] == 0)
	{
		in_bowl[3] = 1;
		//x pick the bowl
		//	printf("haha3\n");
		new_bowl_status = BinaryToDecimal(loc[3][obj3_status], in_bowl);
		int ct;
		ct = maxi(time_x, obj5_now) + dis[x_pos][loc_bowl] + dis[loc_bowl][loc[3][obj3_status]] + time_pick_up;
		dfs(loc[3][obj3_status], y_pos, obj1_status, obj2_status, obj3_status, obj4_status, new_bowl_status, ct, time_y, obj1_now, obj2_now, obj3_now, obj4_now, ct, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

		//y pick the bowl
		ct = maxi(time_y, obj5_now) + dis[y_pos][loc_bowl] + dis[loc_bowl][loc[3][obj3_status]] + time_pick_up;
		dfs(x_pos, loc[3][obj3_status], obj1_status, obj2_status, obj3_status, obj4_status, new_bowl_status, time_x, ct, obj1_now, obj2_now, obj3_now, obj4_now, ct, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);
		in_bowl[3] = 0;
	}
	if (obj4_status >= 2 && in_bowl[4] == 0)
	{
		in_bowl[4] = 1;
		//x pick the bowl
		//	printf("haha4\n");
		new_bowl_status = BinaryToDecimal(loc[4][obj4_status], in_bowl);
		int ct;
		ct = maxi(time_x, obj5_now) + dis[x_pos][loc_bowl] + dis[loc_bowl][loc[4][obj4_status]] + time_pick_up;
		dfs(loc[4][obj4_status], y_pos, obj1_status, obj2_status, obj3_status, obj4_status, new_bowl_status, ct, time_y, obj1_now, obj2_now, obj3_now, obj4_now, ct, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

		//y pick the bowl
		ct = maxi(time_y, obj5_now) + dis[y_pos][loc_bowl] + dis[loc_bowl][loc[4][obj4_status]] + time_pick_up;
		dfs(x_pos, loc[4][obj4_status], obj1_status, obj2_status, obj3_status, obj4_status, new_bowl_status, time_x, ct, obj1_now, obj2_now, obj3_now, obj4_now, ct, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);
		in_bowl[3] = 0;
	}
	if (in_bowl[1] && in_bowl[2] && in_bowl[3] && in_bowl[4])
	{
		new_bowl_status = BinaryToDecimal(5, in_bowl);
		int ct;
		ct = maxi(time_x, obj5_now) + dis[x_pos][loc_bowl] + dis[loc_bowl][5];
		dfs(5, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, new_bowl_status, ct, time_y, obj1_now, obj2_now, obj3_now, obj4_now, ct, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);

		//y pick the bowl
		ct = maxi(time_y, obj5_now) + dis[y_pos][loc_bowl] + dis[loc_bowl][5];
		dfs(x_pos, 5, obj1_status, obj2_status, obj3_status, obj4_status, new_bowl_status, time_x, ct, obj1_now, obj2_now, obj3_now, obj4_now, ct, x_pos, y_pos, obj1_status, obj2_status, obj3_status, obj4_status, obj5_status, kind);
	}

}
void APlanner2::find_solution(int ans_xpos, int ans_ypos, int ans_obj1, int ans_obj2, int ans_obj3, int ans_obj4, int ans_obj5, int ans_kind)
{
	int timex, timey;
	timex = A[ans_kind][ans_xpos][ans_ypos][ans_obj1][ans_obj2][ans_obj3][ans_obj4][ans_obj5];
	timey = B[ans_kind][ans_xpos][ans_ypos][ans_obj1][ans_obj2][ans_obj3][ans_obj4][ans_obj5];


	if (ans_xpos == ans_xpos_terminal && ans_ypos == ans_ypos_terminal &&
		ans_obj1 == ans_obj1_terminal && ans_obj2 == ans_obj2_terminal && ans_obj3 == ans_obj3_terminal && ans_obj4 == ans_obj4_terminal && ans_obj5 == ans_obj5_terminal) return;


	int new_xpos, new_ypos, new_obj1, new_obj2, new_obj3, new_obj4, new_obj5, new_kind;
	old_flag = 1;
	new_xpos = rec[ans_kind][ans_xpos][ans_ypos][ans_obj1][ans_obj2][ans_obj3][ans_obj4][ans_obj5].x_pos;
	new_ypos = rec[ans_kind][ans_xpos][ans_ypos][ans_obj1][ans_obj2][ans_obj3][ans_obj4][ans_obj5].y_pos;
	new_obj1 = rec[ans_kind][ans_xpos][ans_ypos][ans_obj1][ans_obj2][ans_obj3][ans_obj4][ans_obj5].obj1_status;
	new_obj2 = rec[ans_kind][ans_xpos][ans_ypos][ans_obj1][ans_obj2][ans_obj3][ans_obj4][ans_obj5].obj2_status;
	new_obj3 = rec[ans_kind][ans_xpos][ans_ypos][ans_obj1][ans_obj2][ans_obj3][ans_obj4][ans_obj5].obj3_status;
	new_obj4 = rec[ans_kind][ans_xpos][ans_ypos][ans_obj1][ans_obj2][ans_obj3][ans_obj4][ans_obj5].obj4_status;
	new_obj5 = rec[ans_kind][ans_xpos][ans_ypos][ans_obj1][ans_obj2][ans_obj3][ans_obj4][ans_obj5].obj5_status;
	new_kind = rec[ans_kind][ans_xpos][ans_ypos][ans_obj1][ans_obj2][ans_obj3][ans_obj4][ans_obj5].kind;

	int new_timex, new_timey;
	new_timex = A[new_kind][new_xpos][new_ypos][new_obj1][new_obj2][new_obj3][new_obj4][new_obj5];
	new_timey = B[new_kind][new_xpos][new_ypos][new_obj1][new_obj2][new_obj3][new_obj4][new_obj5];
	if (timex != new_timex)
	{

		line_output++;
		output_planner.Add("X");
	}
	else {
		line_output++;
		output_planner.Add("Y");
	}
	if (new_obj1 != ans_obj1)
	{
		if (new_obj1 == 0)
		{

			line_output++;
			output_planner.Add("Getting Lettuce");
			line_output++;
			output_planner.Add("Preparing Lettuce");
		}

		if (new_obj1 == 1)
		{

			line_output++;
			output_planner.Add("Handing over Lettuce");
		}
		/*	if(new_obj1 == 4)
			{

				printf("Make juice\n");
				line_output++;
				output[line_output] = "Make juice by robot";
			}*/
		line_output++;
		output_planner.Add("Lettuce");
	}
	if (new_obj2 != ans_obj2)
	{

		if (new_obj2 == 0)
		{
			line_output++;
			output_planner.Add("Getting Tomato");
			line_output++;
			output_planner.Add("Preparing Tomato");
		}


		if (new_obj2 == 1)
		{
			line_output++;
			output_planner.Add("Handing over Tomato");
		}

		line_output++;
		output_planner.Add("Tomato");
	}
	if (new_obj3 != ans_obj3)
	{

		if (new_obj3 == 0)
		{
			line_output++;
			output_planner.Add("Getting Bun");
		}

		line_output++;
		output_planner.Add("Bun");
	}

	if (new_obj4 != ans_obj4)
	{
		if (new_obj4 == 0)
		{
			line_output++;
			output_planner.Add("Getting Beef");
			line_output++;
			output_planner.Add("Preparing Beef");
		}
		if (new_obj4 == 1)
		{
			line_output++;
			output_planner.Add("Frying Beef");
		}
		if (new_obj4 == 2)
		{

			line_output++;
			output_planner.Add("Handing over Beef");
		}
		line_output++;
		output_planner.Add("Beef");
	}
	if (new_obj5 != ans_obj5)
	{
		DecimalToBinary(new_obj5);
		int new_bowl_code[6];
		for (int kk = 0; kk <= 5; kk++)
			new_bowl_code[kk] = b_status[kk];
		DecimalToBinary(ans_obj5);
		int old_bowl_code[6];
		for (int kk = 0; kk <= 5; kk++)
			old_bowl_code[kk] = b_status[kk];
		int kk;
		for (kk = 0; kk <= 3; kk++)
			if (new_bowl_code[kk] != old_bowl_code[kk])
				break;
		switch (kk) {
		case 0:
			line_output++;
			output_planner.Add("Putting Lettuce Into Plate");
			break;
		case 1:

			line_output++;
			output_planner.Add("Putting Tomato Into Plate");
			break;
		case 2:
			line_output++;
			output_planner.Add("Putting Bun Into Plate");
			break;
		case 3:
			line_output++;
			output_planner.Add("Putting Beef Into Plate");
			break;
		case 4:
			line_output++;
			output_planner.Add("Delivering Burger");
			break;
		}
	}
	old_xpos = ans_xpos;
	old_ypos = ans_ypos;
	old_obj1 = ans_obj1;
	old_obj2 = ans_obj2;
	old_obj3 = ans_obj3;
	old_obj4 = ans_obj4;
	old_obj5 = ans_obj5;
	old_kind = ans_kind;
	//	printf("new : kind = %d, x_pos = %d, y_pos = %d, obj1_status = %d, obj5_status = %d", new_kind, new_xpos, new_ypos, new_apple, new_obj5);
	find_solution(new_xpos, new_ypos, new_obj1, new_obj2, new_obj3, new_obj4, new_obj5, new_kind);
}

FString APlanner2::solve(int x_pos_cur, int y_pos_cur, int obj1_status_cur, int obj2_status_cur, int obj3_status_cur, int obj4_status_cur, int obj5_status_cur, int kind_cur, int time_cur)
{

	ans_xpos_terminal = x_pos_cur;
	ans_ypos_terminal = y_pos_cur;
	ans_obj1_terminal = obj1_status_cur;
	ans_obj2_terminal = obj2_status_cur;
	ans_obj3_terminal = obj3_status_cur;
	ans_obj4_terminal = obj4_status_cur;
	ans_obj5_terminal = obj5_status_cur;
	output_planner.Empty();
	for (int ix = 0; ix <= 5; ix++)
		for (int iy = 0; iy <= 5; iy++)
			for (int iobj1 = 0; iobj1 < NUM_LETTUCE_STATUS; iobj1++)
				for (int iobj2 = 0; iobj2 < NUM_TOMATO_STATUS; iobj2++)
					for (int iobj3 = 0; iobj3 < NUM_BUN_STATUS; iobj3++)
						for (int iobj4 = 0; iobj4 < NUM_BEEF_STATUS; iobj4++)
							for (int iobj5 = 0; iobj5 < num_bowl_status; iobj5++)
								for (int kk = 1; kk <= 3; kk++)
								{
									A[kk][ix][iy][iobj1][iobj2][iobj3][iobj4][iobj5] = max;
									B[kk][ix][iy][iobj1][iobj2][iobj3][iobj4][iobj5] = max;
									/*A4[ix][iy][iapple][iobj5] = MAX;
									B4[ix][iy][iapple][iobj5] = MAX;*/
								}
	dfs(x_pos_cur, y_pos_cur, obj1_status_cur, obj2_status_cur, obj3_status_cur, obj4_status_cur,
		obj5_status_cur, time_cur, time_cur, time_cur, time_cur, time_cur, time_cur, time_cur,
		x_pos_cur, y_pos_cur, obj1_status_cur, obj2_status_cur, obj3_status_cur, obj4_status_cur, obj5_status_cur, kind_cur);

	int ans = max, ans_xpos, ans_ypos, ans_obj1, ans_obj2, ans_obj3, ans_obj4, ans_obj5, ans_kind;
	for (int ix = 0; ix < 6; ix++)
		for (int iy = 0; iy < 6; iy++)
			for (int iobj1 = 0; iobj1 < NUM_LETTUCE_STATUS; iobj1++)
				for (int iobj2 = 0; iobj2 < NUM_TOMATO_STATUS; iobj2++)
					for (int iobj3 = 0; iobj3 < NUM_BUN_STATUS; iobj3++)
						for (int iobj4 = 0; iobj4 < NUM_BEEF_STATUS; iobj4++)
							for (int kk = 1; kk <= 3; kk++)
							{
								int iobj5 = 79;
								if (maxi(A[kk][ix][iy][iobj1][iobj2][iobj3][iobj4][iobj5], B[kk][ix][iy][iobj1][iobj2][iobj3][iobj4][iobj5]) < ans)
								{
									ans = maxi(A[kk][ix][iy][iobj1][iobj2][iobj3][iobj4][iobj5], B[kk][ix][iy][iobj1][iobj2][iobj3][iobj4][iobj5]);
									ans_xpos = ix;
									ans_ypos = iy;
									ans_obj1 = iobj1;
									ans_obj2 = iobj2;
									ans_obj3 = iobj3;
									ans_obj4 = iobj4;
									ans_obj5 = iobj5;
									ans_kind = kk;
								}
							}
	line_output = 0;
	find_solution(ans_xpos, ans_ypos, ans_obj1, ans_obj2, ans_obj3, ans_obj4, ans_obj5, ans_kind);

	for (int i = output_planner.Num()-1; i >=0; i--) {
		UE_LOG(LogTemp, Error, TEXT("%s"), *FString(output_planner[i]));
	}

	return FString("");
}