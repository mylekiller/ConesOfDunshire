
#include "pawn.h"
#include "board.h"
//constructor; args: x position, y position, team
pawn::pawn(int x, int y,bool team):piece(x,y,team){
	movedtwo = false;
	setType(PAWN);
}
pawn::pawn(const pawn& pin) : piece(pin.x,pin.y,pin.team)
{
	movedtwo = pin.movedtwo;
	setType(PAWN);
	copyData((piece*)(&pin));
}
//destructor
pawn::~pawn(){}


void pawn::print()
{
	if(getTeam())
		std::cout<<'P';
	else
		std::cout<<'p';
}
void pawn::resetMoves()
{	
	piece::resetMoves();
}


bool pawn::operator==(const piece& pin) const
{
	if(pin.getType() == PAWN)
	{
		pawn* p = (pawn*) (&pin);
		if(p->movedtwo == movedtwo && p -> x == x && p->y == y && p->team==team && p->hasmoved == hasmoved)
			return true;
	}
	return false;
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
		//En passant check
		if(board -> checkEnPassant(newx,newy,getTeam()))	
		{
			addMove(newx,newy);
			if(newx == getX() && newy == getY() + teammult)
			{
				std::cout<<"!!!!!!!!!!\n!!!!!!!!!!!\n!!!!!!!!!!!!\n!!!!!!!!!!!!!!!\n!!!!!!!!!!!!!!\n!!!!!!!!!!!!!\n";
			}
			continue;
		}
		if(!inbounds(newx,newy) || ! (board -> isOccupied(newx,newy)) ||  board -> getTeam(newx,newy) == getTeam())
		{
			continue;
		}	

		addMove(newx,newy);
		if(newx == getX() && newy == getY() + teammult)
		{
			std::cout<<"!!!!!!!!!!\n!!!!!!!!!!!\n!!!!!!!!!!!!\n!!!!!!!!!!!!!!!\n!!!!!!!!!!!!!!\n!!!!!!!!!!!!!\n";
		}
	}

}

void pawn::setMovedTwo(bool in)
{
	movedtwo = in;
}
void pawn::setAttacks(board * bin)
{
	int teammult = getTeam() ? 1 : -1;
	for(int delx = -1 ;delx<=1;delx+=2)
	{
		int newx = getX() + delx;
		int newy = getY() + teammult;

		if(inbounds(newx,newy))
				addAttack(newx,newy);
	}
}

bool pawn::movedTwo()
{
	return movedtwo;
}
