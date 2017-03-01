#include "piece.h"

#ifndef	BOARD_H
#define BOARD_H


class board{
public: 
	bool isAttacked(int,int);
	board();
	~board();
	bool isOccupied(int, int);

private:
	piece* gameboard[8][8];

};

#endif