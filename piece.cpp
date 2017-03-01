#include "piece.h"

//defautl constructor
piece::piece(int x, int y, bool team)
{
	this -> x = x;
	this -> y = y;
	this -> team = team;
}

//destructor
piece::~piece()
{
	for(int i = 0; i<moves.size();i++)   //iterates through the vector of moves
	{
		delete [] moves[i];   //deletes each array of integers
	}
}

//getter function; reutnrs pointer to the vecotor of possible moves "moves"
std::vector<int*>* piece::getMoves()
{
	return &moves;
}

//getter function; returns the current x position
int piece::getX()
{
	return x;
}

//getter function; returns the current y position
int piece::getY()
{
	return y;
}

//adds the move to the space (x,y) to the vector of possible moves "moves"
void piece::addMove(int x, int y)
{
	int* move = new int[2];   //creates new pointer based integer array
	move[0] = x;   //first element contains x position of possible move
	move[1] = y;   //second element contains y position of possible move
	moves.push_back(move);   //adds the new pointer based array to the vector of possible moves "moves"
}
