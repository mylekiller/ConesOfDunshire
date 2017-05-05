
#include "piece.h"
#ifndef PAWN_H
#define PAWN_H

//Header file for the pawn class, modeled after all the different piece classes, inherits from the overall piece class
class pawn:public piece
{
	public:
		pawn(int, int ,bool);   //consturctorl; args: x, y, team
		pawn(const pawn&);
		~pawn();   //destructor

		void print(); //prints board
		void setMoves(board*);  //fils vector of "moves" with all possible moves
		void setAttacks(board*); //gets vector of possible attacks
		void resetMoves();
		bool movedTwo();  
		void setMovedTwo(bool);//allows pawns the ability to move two spots

		bool operator==(const piece& pin) const;


	private:
		bool movedtwo; //true if pawn moved two spots
};

#endif
