
/*
		  BLACK
7 [ ][ ][ ][ ][ ][ ][ ][ ]
6 [ ][ ][ ][ ][ ][ ][ ][ ]
5 [ ][ ][ ][ ][ ][ ][ ][ ]
4 [ ][ ][ ][ ][ ][ ][ ][ ]
3 [ ][ ][ ][ ][ ][ ][ ][ ]
2 [ ][ ][ ][ ][ ][ ][ ][ ]
1 [ ][ ][ ][ ][ ][ ][ ][ ]
0 [ ][ ][ ][ ][ ][ ][ ][ ]
   0  1  2  3  4  5  6  7
   		 WHITE
*/


#include "piece.h"

#ifndef	BOARD_H
#define BOARD_H


class board
{
	public:
		board();   //default constructor
		~board();   //default destructor
		bool isAttacked(int,int);   //returns whether a space (x,y) is attacked
		bool isOccupied(int, int);   //returns whether a space (x,y) is occupied
		bool getTeam(int, int); //returns team of the piece at (x,y) or false if no piece is there (should not be used without checking isOccupied)
		void addPiece(piece*,int,int);
		void printBoard();
		void updateMoves();
	private:
		piece* gameboard[8][8];   //pointer based 2d array of pointers to pieces

};

#endif
