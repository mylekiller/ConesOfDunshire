
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

void board::addPiece(piece* pin,int x, int y)
{
	gameboard[x][y] = pin;
}
void board::printBoard()
{
	for(int i = 0; i<8;i++)
	{
		for(int j =0 ; j<8;j++)
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