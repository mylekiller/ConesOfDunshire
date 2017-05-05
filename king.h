

#include "piece.h"
#ifndef KING_H
#define KING_H

//Header file for the King class, modeled after all the different piece classes, inherits from the overall piece class

class king:public piece
{
	public:
		king(int, int ,bool);   //consturctor; args: x, y, team
		king(const king&);
		~king();   //destructor
		void setMoves(board*); //fils vector of "moves" with all possible moves
		void setAttacks(board*);   //returns pointer to vector of pointer based integer arrays representing sqaures that are attacked by this pawn
		void print();

		bool operator==(const piece& pin) const;
	private:

};

#endif
