
#include "piece.h"
#ifndef KNIGHT_H
#define KNIGHT_H


class knight:public piece{
public:
	knight(int, int ,bool);
	~knight();

	void setMoves();

private:


};

#endif