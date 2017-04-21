
#include "piece.h"
#ifndef PAWN_H
#define PAWN_H


class pawn:public piece
{
	public:
		pawn(int, int ,bool);   //consturctorl; args: x, y, team
		~pawn();   //destructor

		void print();
		void setMoves(board*);
		std::vector<int*>* getAttacks();   //returns pointer to vector of pointer based integer arrays representing sqaures that are attacked by this pawn
		void resetMoves();
		bool movedTwo();


	private:
		bool movedtwo;
		std::vector<int*> attacks;
};

#endif
