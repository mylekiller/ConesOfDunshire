
#include "piece.h"
#ifndef PAWN_H
#define PAWN_H


class pawn:public piece
{
	public:
		pawn(int, int ,bool);   //consturctorl; args: x, y, team
		pawn(const pawn&);
		~pawn();   //destructor

		void print();
		void setMoves(board*);
		void setAttacks(board*);
		void resetMoves();
		bool movedTwo();
		void setMovedTwo(bool);


	private:
		bool movedtwo;
};

#endif
