
#include "piece.h"
#ifndef KNIGHT_H
#define KNIGHT_H


class knight:public piece
{
	public:
		knight(int, int, bool);   //default constructor; args: x postion, y position, team
		knight(const knight&);
		~knight();   //destructor
		void setMoves(board* bin);
		void setAttacks(board*);
		void print();
	private:

};

#endif
