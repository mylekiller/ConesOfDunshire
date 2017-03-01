
#include "piece.h"
#ifndef PAWN_H
#define PAWN_H


class pawn:public piece{
public:
	pawn(int, int ,bool);
	~pawn();

	void setMoves();
	std::vector<int*>* getAttacks();

private:


};

#endif