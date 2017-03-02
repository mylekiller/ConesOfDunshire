
#include "piece.h"
#ifndef PAWN_H
#define PAWN_H


class pawn:public piece
{
	public:
		pawn(int, int ,bool);   //consturctorl; args: x, y, team
		~pawn();   //destructor
		void setMoves();
		std::vector<int*>* getAttacks();   //returns pointer to vector of pointer based integer arrays representing sqaures that are attacked by this pawn
	private:

};

#endif
