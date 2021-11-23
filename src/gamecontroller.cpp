#include "gamecontroller.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>


GameController::GameController()
{

	//initialize GameRow objects
	for (int i=0; i<9; ++i)
	{
		GameRows[i] = new GameRow();
	}

	current_row=0;
	init_combination();
	game_finished=false;

}


void
GameController::EvaluateCurrentRow()
{

	int count_black=0;
	int count_white=0;

	combination_t chk_combination;  // the combination to be guessed
	combination_t chk_guess;				// current guess

	//Fill the work arrays with the values from the game
	for (int i=0; i<4; ++i)
	{
		chk_combination[i]=combination[i];
		chk_guess[i]=GetCurrentRow()->GetPegColor(i);
	}

	// check for black pegs and mark the places with -1
	for (int counter1=0; counter1<4; ++counter1)
	{
		if (chk_guess[counter1] == chk_combination[counter1] )
		{
			++count_black;
			chk_guess[counter1]=-1;
			chk_combination[counter1]=-1;
		}
	}

	//check for white pegs
	for (int counter1=0; counter1<4; ++counter1)
	{
		if (chk_guess[counter1] != -1)
		{
			for (int counter2=0; counter2<4; ++counter2)
			{
				if (chk_guess[counter1] == chk_combination[counter2])
				{
					++count_white;
					chk_combination[counter2]=-1;
					counter2=4;
				}
			}
		}
	}

	//write the black and white peg numbers into the GameRow object
	GetCurrentRow()->SetResult(count_black,count_white);

	if ((count_black == 4) or (current_row == 8))
	{
		game_finished=true;
	}

}


void
GameController::NextRow()
{

	++current_row;

}


int
GameController::GetCurrentRowNumber()
{

	return current_row;

}


GameRow*
GameController::GetCurrentRow()
{

	return GameRows[current_row];

}


bool
GameController::init_combination()
{

	int counter;
	srand(time(NULL));

	for (counter=0; counter<=3; counter++)
	{
		combination[counter]=(rand() % 6);
	}

	return true;

}


bool
GameController::IsFinished()
{

	return game_finished;

}


combination_t GameController::GetCombination()
{

	return combination;

}
