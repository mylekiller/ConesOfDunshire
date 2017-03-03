#include "bishop.h"

void bishop::setMoves()
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

				//DOES NOT ACCOUTN FOR PIECES BLOCKING

				if( inbounds(x,y) )
				{
					addMove(x,y);
				}
			}
		}
	}
}

std::vector<int*>* bishop::getAttacks()
{
	return getMoves();
}

bishop::bishop(int x, int y, bool team) : piece(x,y,team)
{

}
bishop::~bishop(){}
