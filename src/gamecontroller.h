#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "gamerow.h"


class GameController {
public:
	GameController();
	bool EvaluateCurrentRow();
	bool NextRow();
	int GetCurrentRowNumber();
	GameRow *GetCurrentRow();
	bool IsFinished();
	int *GetCombination();

private:
	bool 		init_combination();		//initialize the combination with random numbers
	bool		game_finished;				//Flag that indicates if the game is finished or not
	int 		current_row;				//current row number (starting at 0)
	int			combination[4];				// 4-number(color) combination that the player must guess
	GameRow		*GameRows[NUMBER_OF_ROWS];	// Array of GameRow Objects for each row
};


#endif