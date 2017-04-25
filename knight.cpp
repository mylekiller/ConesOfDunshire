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
void knight::setAttacks(board* bin)
{
	for(int xdir = -1;xdir<=1;xdir+=2)
	{
		for(int ydir = -1;ydir<=1;ydir+=2)
		{
			int x = getX() + xdir*2;
			int y = getY() + ydir;

			if(inbounds(x,y) )
			{
				addAttack(x,y);
 			}

 			x = getX() + xdir;
 			y = getY() + ydir*2;
			if(inbounds(x,y) )
 			{
 				addAttack(x,y);
 			}
		}
	}
}

bool knight::operator==(const piece& pin) const 
{
	if(pin.getType() == KNIGHT)
	{
		knight* p = (knight*) (&pin);
		if( p -> x == x && p->y == y && p->team==team && p->hasmoved == hasmoved)
			return true;
	}
	return false;
}

void knight::print()
{
	if(!getTeam())
		std::cout<<'n';
	else 
		std::cout<<'N';
}

knight::knight(int x, int y, bool team) : piece(x,y,team)
{
	setType(KNIGHT);
}
knight::knight(const knight& kin) : piece(kin.x,kin.y,kin.team)
{
	setType(KNIGHT);
	copyData((piece*)(&kin));
}
knight::~knight(){}
