#include "gamerow.h"


GameRow::GameRow()
{

	for (int i=0;i<4;++i)
	{
		pegs[i]=-1;
	}

}


int
GameRow::GetPegColor(int pos)
{

	return pegs[pos];

}


void
GameRow::SetPegColor(int pos,int color)
{

	pegs[pos]=color;

}


int
GameRow::GetResultBlack()
{

	return result_black;

}


int
GameRow::GetResultWhite()
{

	return result_white;

}


void
GameRow::SetResult(int number_of_blacks,int number_of_whites)
{

	result_black=number_of_blacks;
	result_white=number_of_whites;

}

