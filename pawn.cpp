
#include "pawn.h"

//constructor; args: x position, y position, team
pawn::pawn(int x, int y,bool team):piece(x,y,team){}

//destructor
pawn::~pawn(){}


void pawn::setMoves()
{

}

//returns pointer to vector of pointer based integer arrays representing what spaces this pawn is attacking
std::vector<int*>* pawn::getAttacks()
{
	std::vector<int*> result;
	return &result;
}
