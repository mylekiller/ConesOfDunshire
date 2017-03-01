#include "piece.h"

piece::piece(int x, int y,bool team){
	this -> x = x;
	this -> y = y;
	this -> team = team;

}

piece::~piece()
{
	for(int i = 0; i<moves.size();i++)
	{
		delete [] moves[i];
	}
}

std::vector<int*>* piece::getMoves()
{
	return &moves;
}
int piece::getX()
{
	return x;
}
int piece::getY()
{
	return y;
}

void piece::addMove(int x, int y)
{
	int* move = new int[2];
	move[0] = x;
	move[1] = y;
	moves.push_back(move);
}
bool piece::inbounds(int x, int y)
{
	return x>=0 && x<8 && y>=0 && y<8;
}