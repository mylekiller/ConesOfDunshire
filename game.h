#include "board.h"
#include "AI.h"

#ifndef GAME_H
#define GAME_H


class game{
public:
	game();
	~game();
	void print();
	bool trymove(int,int,int,int, enum piecetype = QUEEN);
	piece* getpiece(int,int);
	bool getTurn();
	int inCheck(bool team);
	bool checkPromotion(int,int,int,int);
	std::pair<std::pair<int,int> , std::pair<int,int> > getAIMove();
private:
	board boardGame;
	bool turn; //again white = true black = false
	AI ai;


};

#endif
