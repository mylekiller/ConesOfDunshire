#include "board.h"

#ifndef GAME_H
#define GAME_H


class game{
public:
	game();
	~game();

	bool trymove(int,int,int,int);

private:
	board board;
	bool turn; //again white = true black = false


};

#endif