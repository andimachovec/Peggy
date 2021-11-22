#include "gamecontroller.h"




//----------------------------------------------------------------------------
GameController::GameController(void)
//----------------------------------------------------------------------------
{
	
	//initialize GameRow objects
	for (int i=0; i<NUMBER_OF_ROWS; ++i)
	{
		GameRows[i] = new GameRow();
	}
	
	current_row=0;
	
	init_combination();
	
	game_finished=false;
	
	
	#ifdef GAMECONTROLLER_DEBUG
		
		std::cout << "Neues Spiel:" << std::endl;
		std::cout << "Kombination: " << combination[0] << "-" << combination[1] << "-" << combination[2] << "-" << combination[3] << "-" << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
			
	#endif
}



//----------------------------------------------------------------------------
bool GameController::EvaluateCurrentRow(void)
//----------------------------------------------------------------------------
{


	int counter1,counter2;	//	loop counters
	int count_black=0;		//	feedback peg counters
	int count_white=0;

	int chk_combination[4];  	// the combination to be guessed
	int chk_guess[4];			// current guess



	//Fill the work arrays with the values from the game
	for (int i=0; i<4; ++i) 
	{
		chk_combination[i]=combination[i];
		chk_guess[i]=GetCurrentRow()->GetPegColor(i);
		
	}


	//original C-algorithm
	
		
	// check for black pegs and mark the places with -1
	for (counter1=0;counter1<=3;++counter1) {
	
		if (chk_guess[counter1] == chk_combination[counter1] ){
			++count_black;
			chk_guess[counter1]=-1;
			chk_combination[counter1]=-1;
		}
	
	}
	
	//check for white pegs
	for (counter1=0;counter1<=3;++counter1) {
	
		if (chk_guess[counter1] != -1) {
			
			for (counter2=0;counter2<=3;++counter2) {
				
				if (chk_guess[counter1] == chk_combination[counter2]) {
					++count_white;
					chk_combination[counter2]=-1;
					counter2=4;
				}
			}
		}
	}


	// original C-algorithm end


	
	//write the black and white peg numbers into the GameRow object
	GetCurrentRow()->SetResult(count_black,count_white);

	if ((count_black == 4) || (current_row == (NUMBER_OF_ROWS - 1)))
	{
		game_finished=true;
	}	


	return true;
}

//----------------------------------------------------------------------------
bool GameController::NextRow(void)
//----------------------------------------------------------------------------
{

	++current_row;
	
	return true;
}

//----------------------------------------------------------------------------
int GameController::GetCurrentRowNumber(void)
//----------------------------------------------------------------------------
{

	return current_row;

}

//----------------------------------------------------------------------------
GameRow *GameController::GetCurrentRow(void)
//----------------------------------------------------------------------------
{

	

	return GameRows[current_row];

}




//----------------------------------------------------------------------------
bool GameController::init_combination(void)
//----------------------------------------------------------------------------
{

	int counter;
	
	
	srand(time(NULL));
	
	for (counter=0; counter<=3; counter++)
	{	
		combination[counter]=(rand() % 6);
		
	}
	
	
	return true;
}


//----------------------------------------------------------------------------
bool GameController::IsFinished(void)
//----------------------------------------------------------------------------
{

	return game_finished;

}

//----------------------------------------------------------------------------
int *GameController::GetCombination(void)
//----------------------------------------------------------------------------
{

	return combination;

}
