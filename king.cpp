#include "king.h"
#include "board.h"


king::king(int x, int y,bool team):piece(x,y,team){
	setType(KING);
}
king::king(const king& kin) : piece(kin.x,kin.y,kin.team)
{
	setType(KING);
}

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
				else
					continue;
				
			}
			if(inbounds(x,y))
			{
				addMove(x,y);
			}
		}
	}


	//CASTLING

	int newx = getX() + 2;
	int newy = getY();
	if(!hasmoved && inbounds(newx, newy) && inbounds(newx+1,newy) && bin -> isOccupied(newx+1,newy) && bin -> get(newx+1,newy) -> getType() == ROOK && bin->get(newx+1,newy) -> hasMoved() == false)
	{
		addMove(newx,newy);
	}

	newx = getX() - 2;
	newy = getY();
	if(!hasmoved && inbounds(newx, newy) && inbounds(newx-2,newy) && bin -> isOccupied(newx-2,newy) && bin -> get(newx-2,newy) -> getType() == ROOK && bin->get(newx-2,newy) -> hasMoved() == false)
	{
		addMove(newx,newy);
	}


}
void king::setAttacks(board* bin)
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
			if(inbounds(x,y))
			{
				addAttack(x,y);
			}
		}
	}
}
