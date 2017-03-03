#include "bishop.h"
#include "board.h"

void bishop::setMoves(board* bin)
{
	for( int xdir = -1; xdir <= 1; xdir +=2 )
	{
		for( int ydir = -1; ydir <= 1; ydir +=2 )
		{
			int x, y;

			for( int dis = 1; dis <= 7; dis++ )
			{
				x = getX() + xdir * dis;
				y = getY() + ydir * dis;

				if(inbounds(x,y) && bin -> isOccupied(x,y))
				{
					addMove(x,y);
					break;
				}

				//DOES NOT ACCOUTN FOR PIECES BLOCKING

				if( inbounds(x,y) )
				{
					addMove(x,y);
				}
			}
		}
	}
}

void bishop::print()
{
	if(getTeam())
		std::cout<<'b';
	else
		std::cout<<'B';
}
std::vector<int*>* bishop::getAttacks()
{
	return getMoves();
}

bishop::bishop(int x, int y, bool team) : piece(x,y,team)
{

}
bishop::~bishop(){}
