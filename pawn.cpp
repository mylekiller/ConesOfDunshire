
#include "pawn.h"
#include "board.h"
//constructor; args: x position, y position, team
pawn::pawn(int x, int y,bool team):piece(x,y,team){
	setType(PAWN);
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
	for( int i = 0; i < attacks.size(); i++)   //iterates through the vector of moves
	{
		delete [] attacks[i];   //deletes each array fo integers
	}

	auto it = attacks.begin();
	while( it != attacks.end() )
	{
		attacks.erase(it);
		it = attacks.begin();
	}

	std::cout<<"Done resetting moves.... \n";
}
void pawn::setMoves(board* board)
{

	std::cout<<"Setting moves... \n";
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
		std::cout<<"CheckingEnPassant...\n";
		if(board -> checkEnPassant(newx,newy,getTeam()))	
		{

			addMove(newx,newy);
			continue;
		}
		if(!inbounds(newx,newy) || ! (board -> isOccupied(newx,newy)) ||  board -> getTeam(newx,newy) == getTeam())
		{
			continue;
		}	

		addMove(newx,newy);
	}

	std::cout<<"Done checking ENPassant... \n";
	
	for(int delx = -1 ;delx<=1;delx+=2)
	{

		int* move = new int[2];
		move[0] = getX() + delx;
		move[1] = getY();


		if(inbounds(move[0],move[1]))
				attacks.push_back(move);
	}
	
	std::cout<<"Done setting moves... \n";

}

//returns pointer to vector of pointer based integer arrays representing what spaces this pawn is attacking
std::vector<int*>* pawn::getAttacks()
{
	return &attacks;
}
bool pawn::movedTwo()
{
	return movedtwo;
}
