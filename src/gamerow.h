#ifndef GAMEROW_H
#define GAMEROW_H


#include<array>


class GameRow {
public:
	GameRow();
	int GetPegColor(int pos);
	void SetPegColor(int pos, int color);
	int GetResultBlack();
	int	GetResultWhite();
	void SetResult(int number_of_blacks, int number_of_whites);

private:
	int result_black;
	int result_white;
	std::array<int, 4> pegs;
};


#endif
