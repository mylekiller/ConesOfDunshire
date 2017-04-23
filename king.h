

#include "piece.h"
#ifndef KING_H
#define KING_H


class king:public piece
{
	public:
		king(int, int ,bool);   //consturctor; args: x, y, team
		king(const king&);
		~king();   //destructor
		void setMoves(board*);
		std::vector<int*>* getAttacks();   //returns pointer to vector of pointer based integer arrays representing sqaures that are attacked by this pawn
		void print();
	private:

};

#endif
