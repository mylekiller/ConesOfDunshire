#include "king.h"
#include "board.h"


king::king(int x, int y,bool team):piece(x,y,team){}

//destructor
king::~king(){}

void king::print()
{
	if(getTeam())
		std::cout<<'K';
	else
		std::cout<<'k';
}

void king::setMoves(board* bin)
{
	for(int xdir = -1 ; xdir <=1;xdir++)
	{
		for(int ydir = -1;ydir<=1;ydir++)
		{
			if(xdir == 0 && ydir == 0)
				continue;
			int x,y;
			x = getX() + xdir;
			y = getY() + ydir;
			if(inbounds(x,y) && bin -> isOccupied(x,y))
			{
				if(bin -> getTeam(x,y) != getTeam())
				{
					addMove(x,y);
				}
				
			}
			if(inbounds(x,y))
			{
				addMove(x,y);
			}
		}
	}

}

std::vector<int*>* king::getAttacks()
{
	return getMoves();
}