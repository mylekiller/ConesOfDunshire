
#include "piece.h"
#ifndef BISHOP_H
#define BISHOP_H


class bishop:public piece
{
	public:
		bishop(int, int, bool);   //default constructor; args: x position, y position, team
		~bishop();   //destructor
		void setMoves(board*);   //fils vector of "moves" with all possible moves
		std::vector<int*>* getAttacks();   //returns all spaces this piece is attacking
		void print();
	private:

};

#endif
