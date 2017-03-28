
#include "pawn.h"
#include "board.h"
//constructor; args: x position, y position, team
pawn::pawn(int x, int y,bool team):piece(x,y,team){}

//destructor
pawn::~pawn(){}


void pawn::print()
{
	if(getTeam())
		std::cout<<'P';
	else
		std::cout<<'p';
}
void pawn::setMoves(board* board)
{
	int teammult = getTeam() ? 1 : -1;
	int limit = hasMoved() ? 1 : 2;
	for(int i = 0; i< limit; i++)
	{
		int newy = getY() + teammult * (i+1);
		int newx = getX();
		if(inbounds(newx,newy))
		{
			if(board -> isOccupied(newx,newy))
				break;

			addMove(newx,newy);
		}
	}

	for(int i = -1; i<= 1; i+=2)
	{
		int newy = getY() + teammult;
		int newx = getX() + i;
		if(!inbounds(newx,newy) || ! (board -> isOccupied(newx,newy)) ||  board -> getTeam(newx,newy) == getTeam())
		{
			continue;
		}	
		addMove(newx,newy);
	}
}

//returns pointer to vector of pointer based integer arrays representing what spaces this pawn is attacking
std::vector<int*>* pawn::getAttacks()
{
	std::vector<int*> result;

	for(int delx = -1 ;delx<=1;delx+=2)
	{
		int* move = new int[2];
		move[0] = getX() + delx;
		move[1] = getY();
		result.push_back(move);
	}
	return &result;
}
