
#include "piece.h"
#ifndef BISHOP_H
#define BISHOP_H


class bishop:public piece
{
	public:
		bishop(int, int, bool);   //default constructor; args: x position, y position, team
		bishop(const bishop&);
		~bishop();   //destructor
		void setMoves(board*);   //fils vector of "moves" with all possible moves
		void setAttacks(board*);


		void print();
	private:

};

#endif
