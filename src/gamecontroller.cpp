#include "gamecontroller.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>


GameController::GameController()
{

	current_row=0;
	init_combination();

}


void
GameController::EvaluateActiveRow(combination_t guess, int &black, int &white);
{

	black=0;
	white=0;

	combination_t chk_combination;  // the combination to be guessed
	combination_t chk_guess;		// current guess

	//Fill the work arrays with the values from the game
	for (int i=0; i<4; ++i)
	{
		chk_combination[i]=combination[i];
		chk_guess[i]=guess[i];
	}

	// check for black pegs and mark the places with -1
	for (int counter1=0; counter1<4; ++counter1)
	{
		if (chk_guess[counter1] == chk_combination[counter1] )
		{
			++black;
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
					++white;
					chk_combination[counter2]=-1;
					counter2=4;
				}
			}
		}
	}

	if ((black < 4) and (active_row < 8)
	{
		++active_row;
	}
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


combination_t GameController::GetCombination()
{

	return combination;

}
