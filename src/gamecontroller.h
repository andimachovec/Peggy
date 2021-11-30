#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <array>


typedef std::array<int, 4> combination_t;


class GameController {
public:
	GameController();
	void EvaluateActiveRow(combination_t guess);
	bool CombinationGuessed();
	combination_t GetCombination();

private:
	bool 							init_combination();

	bool							combination_guessed;
	int 							active_row;
	combination_t					combination;
	std::array<combination_t, 9> 	GameRows;
};


#endif