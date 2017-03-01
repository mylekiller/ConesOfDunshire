#include "knight.h"

//sets the possible moves of the knight based on where it currently is
void knight::setMoves()
{
	for(int xdir = -1;xdir<=1;xdir+=2)   //iterates through the x directions: -1,1
	{
		for(int ydir = -1;ydir<=1;ydir+=2)   //iterates through the y directions: -1,1
		{
			//handles moving two spaces in the x direction
			int x = getX() + xdir*2;   //x is two spaces in the x direction from the current x
			int y = getY() + ydir;   //y is one space in the y direction from the current y

			if(board::inBounds(x,y))   //if x and y are on the board
			{
				addMove(x,y);   //adds the move to the current list of moves
 			}

			//handles moving two spaces in the y direction
 			x = getX() + xdir;   //x is one space in the x direction from the current x
 			y = getY() + ydir*2;   //y is two spces in the y direction from the current y

 			if(board::inBounds(x,y))   //if x and y are on the board
 			{
 				addMove(x,y);   //adds the move to the curren list of moves
 			}
		}
	}
}

//default constructor; inherited from piece
knight::knight(int x, int y, bool team) : piece(x,y,team){}

//destructor
knight::~knight(){}
