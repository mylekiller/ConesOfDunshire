#include "bishop.h"
#include "board.h"
//Implementation of Bishop class, includes functions that get all possible moves for the rook (based on how to piece is allowed to move following the conventional rules of chess)
void bishop::setMoves(board* bin) //gets possible moves
{
	for( int xdir = -1; xdir <= 1; xdir +=2 )
	{
		for( int ydir = -1; ydir <= 1; ydir +=2 )
		{
			int x, y;

			for( int dis = 1; dis <= 7; dis++ )
			{
				x = getX() + xdir * dis; //bishops move diagonally
				y = getY() + ydir * dis;

				if(inbounds(x,y) && bin -> isOccupied(x,y))
				{
					if(bin -> getTeam(x,y) != getTeam())
					{
						addMove(x,y); //adds move if open and in bounds
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
void bishop::setAttacks(board* bin) //gets all possible attacks
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
					
					addAttack(x,y);
					
					break;
				}
				if(inbounds(x,y))
				{
					addAttack(x,y);
				}
				else
				{
					break;
				}
			}
		}
	}
}

void bishop::print() //prints out the piece
{
	if(!getTeam())
		std::cout<<'b';
	else
		std::cout<<'B';
}

bool bishop::operator==(const piece& pin) const
{
	if(pin.getType() == BISHOP)
	{
		bishop* p = (bishop*) (&pin);
		if(p -> x == x && p->y == y && p->team==team && p->hasmoved == hasmoved)
			return true;
	}
	return false;
}
bishop::bishop(int x, int y, bool team) : piece(x,y,team) //constructor
{
	setType(BISHOP);
}
bishop::bishop(const bishop& bin) : piece(bin.x,bin.y,bin.team)
{
	setType(BISHOP);
	copyData((piece*)(&bin));
}
bishop::~bishop(){} //deconstructor
