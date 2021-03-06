//Format for the Board, 7 by 7 array of arrays to represent all the spaces on a common chess board
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

//Board header file, includes functions for creating the chess board, printing the board, gettings attacks, checking if occupied or attacked, etc.
class board
{
	public:

		board();   //default constructor
		board(const board&);
		~board();   //default destructor
		bool isAttacked(int,int);   //returns whether a space (x,y) is attacked
		bool isOccupied(int, int);   //returns whether a space (x,y) is occupied
		bool getTeam(int, int); //returns team of the piece at (x,y) or false if no piece is there (should not be used without checking isOccupied)
		void addPiece(piece*);
		void printBoard(); //prints the board
		void printAttacks(); //prints the possible attacks
		bool checkEnPassant(int, int,bool); //checks if en passant is available
		bool inbounds(int,int); //checks to make sure move is in bounds of the board
		void execmove(piece *, int, int,enum piecetype = QUEEN);
		bool isAllowed(piece *, int, int,bool);
		void update(bool);
		void printMovedTwo(); //for pawns that moved two spaces
		int check(bool); // returns 0 if no check -1 if black in check 1 if white in check
		bool inCheck(bool);
		bool operator==(const board& ) const; 
		bool toMove();
		piece* get(int,int) const ;

	private:

		bool tomove;
		piece* gameboard[8][8];   //pointer based 2d array of pointers to pieces
		bool attacks[2][8][8]; //shows the squares that are attacked to check for check/checkmate/castling 1 = white 0 = black
		piece* copypiece(piece*);

		bool hasMove(bool);

};

#endif
