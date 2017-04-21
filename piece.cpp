
#include <iostream>

#include "piece.h"




//defautl constructor
piece::piece(int x, int y, bool team)
{
	setX(x);
	setY(y);
	setTeam(team);
	hasmoved = false;
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

//clears the vector moves; allows setmoves to correctly update the moves
void piece::resetMoves()
{
	std::cout<<"YOOOO!\n\n";
	for( size_t i = 0; i < moves.size(); i++)   //iterates through the vector of moves
	{
		delete [] moves[i];   //deletes each array fo integers
	}


	std::cout<<"HIIII!\n\n";
	auto it = moves.begin();
	while( it != moves.end() )
	{
		moves.erase(it);
		it = moves.begin();
	}


}

bool piece::hasMoved()
{
	return hasmoved;
}

//setter function; sets the current x position
void piece::setX(int x)
{
	this -> x = x;
}

//getter function; returns the current x position
int piece::getX()
{
	return x;
}

//setter function; sets the current y position
void piece::setY(int y)
{
	this -> y = y;
}

//getter function; returns the current y position
int piece::getY()
{
	return y;
}

//setter function; sets the team
void piece::setTeam(bool team)
{
	this -> team = team;
}

//"moves" this piece to the space (x,y)
void piece::move(int x, int y)
{
	setX(x);
	setY(y);
	resetMoves();
}

//getter fucntion; gets the team TRUE = WHITE FALSE = BLACK
bool piece::getTeam()
{
	return team;
}

//adds the move to the space (x,y) to the vector of possible moves "moves"
void piece::addMove(int x, int y)
{

	int* move = new int[2];   //creates new pointer based integer array
	move[0] = x;   //first element contains x position of possible move
	move[1] = y;   //second element contains y position of possible move
	moves.push_back(move);   //adds the new pointer based array to the vector of possible moves "moves"
}

//returns if a space (x,y) is on the board
bool piece::inbounds(int x, int y)
{
	return x>=0 && x<8 && y>=0 && y<8;
}
piecetype piece::getType()
{
	std::cout<<"Getting type...  :" <<&type << "\n";
	return type;
}
void piece::setType(enum piecetype tin)
{
	type = tin;
}


