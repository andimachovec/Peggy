#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include "gamerow.h"
#include <array>


typedef std::array<int, 4> combination_t;


class GameController {
public:
	GameController();
	void EvaluateCurrentRow();
	void NextRow();
	int GetCurrentRowNumber();
	GameRow *GetCurrentRow();
	bool IsFinished();
	combination_t GetCombination();

private:
	bool 					init_combination();

	bool					game_finished;
	int 					current_row;
	combination_t			combination;
	std::array<GameRow*, 9> GameRows;
};


#endif