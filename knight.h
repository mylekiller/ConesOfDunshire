
#include "piece.h"
#ifndef KNIGHT_H
#define KNIGHT_H


class knight:public piece
{
	public:
		knight(int, int, bool);   //default constructor; args: x postion, y position, team
		~knight();   //destructor
		void setMoves(board* bin);
		std::vector<int*>* getAttacks();
		void print();
	private:

};

#endif
