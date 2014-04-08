#include "score.h"

points::points()
{
	line_count[0] = 10;
	line_count[1] = 1000;
	line_count[2] = 2500;
	line_count[3] = 4500;
	line_count[4] = 8000;

	for(int i=0; i<6; i++)
	{
		score_arr[i]=0;
	}
	score_int=0;
}

void points::convert_score()
{
	int temp_score = score_int;
	for(int i=5; i>=0; i--)
	{
		score_arr[i] = temp_score % 10;
		temp_score /= 10;
	}
}

int points::get_score(int a)
{
	return score_arr[a];
}

void points::calc_score(int lines)
{
	score_int = score_int + line_count[lines];
	convert_score();
}
