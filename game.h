#include "board.h"
#include "AI.h"

#ifndef GAME_H
#define GAME_H

//Header file for the game class 
class game{
public:
	game(); //constructor
	~game(); //deconstructor
	void print();
	bool trymove(int,int,int,int, enum piecetype = QUEEN); 
	piece* getpiece(int,int);
	bool getTurn(); //gets which player's turn it is
	int inCheck(bool team); //checks to see if King is in check
	bool checkPromotion(int,int,int,int); //checks if promotion is possible
	std::pair<std::pair<int,int> , std::pair<int,int> > getAIMove(); //implements AI
private:
	board boardGame;
	bool turn; //again white = true black = false
	AI ai;


};

#endif
