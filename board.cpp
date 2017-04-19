
#include "board.h"


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