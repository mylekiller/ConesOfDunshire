
#include "pawn.h"
pawn::pawn(int x, int y,bool team):piece(x,y,team){}

pawn::~pawn(){}

void pawn::setMoves()
{

}

std::vector<int*>* pawn::getAttacks()
{
	std::vector<int*> result;
	return &result;
}