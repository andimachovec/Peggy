#ifndef GAMEROW_H
#define GAMEROW_H



class GameRow {

	public:
		GameRow(void);
		int GetPegColor(int pos);
		bool SetPegColor(int pos, int color);
		int GetResultBlack();
		int	GetResultWhite();
		bool SetResult(int number_of_blacks, int number_of_whites);
	
	
	private:
		int result_black;
		int result_white;
		int pegs[4]; 


};


#endif
