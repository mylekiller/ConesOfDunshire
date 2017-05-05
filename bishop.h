
#include "piece.h"
#ifndef BISHOP_H
#define BISHOP_H

//Header file for the bishop class, modeled after all the different piece classes, inherits from the overall piece class

class bishop:public piece
{
	public:
		bishop(int, int, bool);   //default constructor; args: x position, y position, team
		bishop(const bishop&);
		~bishop();   //destructor
		void setMoves(board*);   //fils vector of "moves" with all possible moves
		void setAttacks(board*); //gets possible attacks
		void print();

		bool operator==(const piece& pin) const;
	private:

};

#endif
