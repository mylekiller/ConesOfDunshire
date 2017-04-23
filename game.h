#include "board.h"

#ifndef GAME_H
#define GAME_H


class game{
public:
	game();
	~game();
	void print();
	bool trymove(int,int,int,int);
	piece* getpiece(int,int);
	bool getTurn();
	int inCheck(bool team);
private:
	board boardGame;
	bool turn; //again white = true black = false


};

#endif
