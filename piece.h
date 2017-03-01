#include <vector>
#include "board.h"


#ifndef PIECE_H
#define	PIECE_H

class piece{
	public:
		piece(int, int, bool);   //defualt constructor; args: x position, y position, team (black/white)
		~piece();   //default constructor
		virtual void setMoves() = 0;   //setter function; sets the moves possible for the piece
		std::vector<int*>* getMoves();   //getter function; returns pointer to vector of possible moves
		int getX();   //getter function; gets the current x position of the piece
		int getY();   //getter function; gets the current y position of the piece
		bool getTeam();   //getter function; gets the team of the current piece
	protected:
		std::vector<int*> moves;   //vector of pointers to integers arrays; represents the possible moves
		void addMove(int , int);   //adds the possibility of a move to a specific space
	private:
		int x;   //piece's current x position
		int y;   //piece's current y position
		bool team;   //piece's team; whether piece is white (true=white, false=black)
};

#endif
