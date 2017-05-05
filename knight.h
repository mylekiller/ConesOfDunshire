
#include "piece.h"
#ifndef KNIGHT_H
#define KNIGHT_H

//Header file for the knight class, modeled after all the different piece classes, inherits from the overall piece class
class knight:public piece
{
	public:
		knight(int, int, bool);   //default constructor; args: x postion, y position, team
		knight(const knight&);
		~knight();   //destructor
		void setMoves(board* bin);
		void setAttacks(board*); //gets attacks for the piece
		void print(); //uses the print board function

		bool operator==(const piece& pin) const;
	private:

};

#endif
