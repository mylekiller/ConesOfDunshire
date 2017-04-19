
#include "board.h"
#include "pawn.h"

bool board::isOccupied(int x, int y)
{
	return gameboard[x][y] != nullptr;
}

board::board(){
	for(int i = 0 ;i<8;i++)
	{
		for(int j = 0 ;j < 8;j++)
		{
			gameboard[i][j] = nullptr;
		}
	}
}

board::~board(){}

bool board::getTeam(int x, int y)
{
	if(isOccupied(x,y))
	{
		return gameboard[x][y] -> getTeam();
	}
	return false;
}

void board::updateMoves()
{
	for(int i = 0; i< 8; i++)
	{
		for(int j = 0;j<8;j++)
		{
			if(gameboard[i][j] != nullptr)
				gameboard[i][j] -> setMoves(this);
		}
	}
}
void board::addPiece(piece* pin,int x, int y)
{
	gameboard[x][y] = pin;
}
void board::printBoard()
{
	for(int j = 0; j<8;j++)
	{
		for(int i =0 ; i<8;i++)
		{
			if(gameboard[i][j] != nullptr)
			{
				gameboard[i][j] -> print();
			}
			else
			{
				std::cout<<"*";
			}
		}
		std::cout<<'\n';
	}
}

void board::updateAttacks()
{

	for(int t = 0; t<=1; t++)
	{
		for(int i = 0; i<8;i++)
		{
			for(int j = 0; j<8;j++)
			{
				attacks[t][i][j] = false;
			}
		}
	}
	for(int i = 0; i< 8; i++)
	{
		for(int j = 0; j<8; j++)
		{
			if(isOccupied(i,j))
			{
				std::vector<int*>* attacks = gameboard[i][j] -> getAttacks();
				for(auto it = attacks -> begin() ; it != attacks -> end() ; it++)
				{
					int teamnum = gameboard[i][j] -> getTeam() ? 1 : 0;
					attacks[teamnum][(*it)[0]][(*it)[1]] = true;
				}
			}
		}
	}


}
void board::execmove(piece * p, int x, int y )
{
	if(p -> getType() == PAWN)
	{
		int teamval = p->getTeam() ? 1 : -1;
		if(true)
			return;
	}
}

bool board::inbounds(int x, int y)
{
	return x>=0 && x<8 && y>=0 && y<8;
}
bool board::checkEnPassant(int x, int y, bool team)
{
	int checkx = x;
	int checky = team ? y+1 : y-1;

	if(inbounds(checkx,checky) && isOccupied(checkx,checky) && gameboard[checkx][checky] -> getTeam() != team && gameboard[checkx][checky] -> getType() == PAWN && ((pawn*)(gameboard[x][y])) -> movedTwo())
		return true;
	return false;
}