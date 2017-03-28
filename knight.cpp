 #include "board.h"
 #include "knight.h"

void knight::setMoves(board* bin)
{
	for(int xdir = -1;xdir<=1;xdir+=2)
	{
		for(int ydir = -1;ydir<=1;ydir+=2)
		{
			int x = getX() + xdir*2;
			int y = getY() + ydir;

			if(inbounds(x,y) && (! bin -> isOccupied(x,y) || bin -> getTeam(x,y) != getTeam()))
			{
				addMove(x,y);
 			}

 			x = getX() + xdir;
 			y = getY() + ydir*2;
			if(inbounds(x,y) && (! bin -> isOccupied(x,y) || bin -> getTeam(x,y) != getTeam()))
 			{
 				addMove(x,y);
 			}
		}
	}
}

void knight::print()
{
	if(!getTeam())
		std::cout<<'n';
	else 
		std::cout<<'N';
}

std::vector<int*>* knight::getAttacks()
{
	return getMoves();
}

knight::knight(int x, int y, bool team) : piece(x,y,team)
{
}
knight::~knight(){}
