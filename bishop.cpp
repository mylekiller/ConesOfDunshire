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
					if(bin -> getTeam(x,y) != getTeam())
					{
						addMove(x,y);
					}
					break;
				}
				if(inbounds(x,y))
				{
					addMove(x,y);
				}
				else
				{
					break;
				}
			}
		}
	}
}

void bishop::print()
{
	if(!getTeam())
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
	setType(BISHOP);
}
bishop::bishop(const bishop& bin) : piece(bin.x,bin.y,bin.team)
{
	setType(BISHOP);
}
bishop::~bishop(){}
