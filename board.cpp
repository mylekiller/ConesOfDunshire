
#include "board.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "knight.h"

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
	for(int t = 0; t<=1; t++)
	{
		for(int i = 0;i<8;i++)
		{
			for(int j = 0; j<8; j++)
			{
				attacks[t][i][j] =false;
			}
		}
	}
}
board::board(const board& bin)
{

	for(int i = 0 ;i<8;i++)
	{
		for(int j = 0 ;j < 8;j++)
		{
			gameboard[i][j] = nullptr;
		}
	}
	
	for(int i = 0;i<8;i++)
	{
		for(int j = 0; j<8; j++)
		{
			if(bin.gameboard[i][j])
			{
				gameboard[i][j] = copypiece(bin.gameboard[i][j]);
				
			}
		}
	}
	for(int t = 0; t<=1; t++)
	{
		for(int i = 0;i<8;i++)
		{
			for(int j = 0; j<8; j++)
			{
				attacks[t][i][j] = bin.attacks[t][i][j];
			}
		}
	}
	update();

}	

board::~board(){
	for(int i = 0; i<8; i++)
	{
		for(int j =0;j<8;j++)
		{
			if(gameboard[i][j])
			{
				delete gameboard[i][j];
			}
		}
	}
}


piece* board::copypiece(piece* p)
{
	switch(p -> getType())
	{
		case PAWN:
			return new pawn(*((pawn*)(p)));
			break;
		case KNIGHT:
			return new knight(*((knight*)(p)));
			break;
		case BISHOP:
			return new bishop(*((bishop*)(p)));
			break;
		case QUEEN:
			return new queen(*((queen*)(p)));
			break;
		case ROOK:
			return new rook(*((rook*)(p)));
			break;
		case KING:
			return new king(*((king*)(p)));
			break;
	}
}


void board::printAttacks()
{
	std::cout<<"\n";
	for(int i =0; i<20;i++)
		std::cout<<"-";
	std::cout<<"\n";
	for(int i = 7; i >= 0 ;i--)
	{
		for(int j = 0;j <8;j++)
		{
			if(attacks[0][j][i])
			{
				std::cout<<"*";
			}
			else
			{
				std::cout<<"X";
			}
		}
		std::cout<<"\n";
	}

	for(int i =0; i<20;i++)
		std::cout<<"-";
	std::cout<<"\n";
}
bool board::getTeam(int x, int y)
{
	if(isOccupied(x,y))
	{
		return gameboard[x][y] -> getTeam();
	}
	return false;
}


void board::addPiece(piece* pin)
{
	gameboard[pin->getX()][pin->getY()] = pin;
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


void board::execmove(piece * p, int x, int y )
{
	if(p -> getType() == PAWN) //check for an enpassant capture
	{
		int teamval = p->getTeam() ? 1 : -1;
		if((x == p->getX() +1 || x==p->getX() -1)&& y == p->getY() + teamval && !isOccupied(x,y) )
		{
			delete gameboard[x][y-teamval];
			gameboard[x][y] = p;


			
			gameboard[p->getX()][p->getY()] = NULL;

			gameboard[x][y]->move(x,y);
			update();
			return;
		} 
	}
	if(p -> getType() == KING)
	{
		//do the castling check
	}
	if(isOccupied(x,y))
	{
		delete gameboard[x][y];
	}



	gameboard[x][y] = p;


	int tempx = p->getX();
	int tempy = p->getY();

	
	gameboard[p->getX()][p->getY()] = NULL;

	gameboard[x][y]->move(x,y);

	update();

}
void board::update()
{

	for(int t = 0; t<=1; t++)
	{
		for(int i = 0;i<8;i++)
		{
			for(int j = 0; j<8; j++)
			{
				attacks[t][i][j] =false;
			}
		}
	}

	for(int i = 0; i< 8; i++)
	{
		for(int j = 0;j<8;j++)
		{
			
			if(gameboard[i][j] != nullptr)
			{
				
				gameboard[i][j] -> reset();

			}
		}
	}

	
	for(int i = 0; i< 8; i++)
	{
		for(int j = 0;j<8;j++)
		{
			if(gameboard[i][j] != nullptr)
				gameboard[i][j] -> update(this);
		}
	}


	for(int i = 0; i< 8; i++)
	{
		for(int j = 0; j<8; j++)
		{
		
			if(isOccupied(i,j))
			{
				
				std::vector<int*>* temp = gameboard[i][j] -> getAttacks();
				
				for(auto it = temp -> begin() ; it != temp -> end() ; it++)
				{
					int teamnum = gameboard[i][j] -> getTeam() ? 1 : 0;
					if(!inbounds((*it)[0],(*it)[1]))
					{
						for(int i = 0; i<100;i++) std::cout<<"!";
						std::cout<<"\n";
					}

 					attacks[teamnum][(*it)[0]][(*it)[1]] = true;
				
				}
			}
		}
	}

}
bool board::inbounds(int x, int y)
{
	return x>=0 && x<8 && y>=0 && y<8;
}
piece* board::get(int x, int y)
{
	return gameboard[x][y];
}

int board::check(bool team)
{
	for(int i = 0; i<8;i++)
	{
		for(int j = 0; j<8;j++)
		{
			if(isOccupied(i,j) && gameboard[i][j] -> getType() == KING  && gameboard[i][j] -> getTeam() == team )
			{
				
				if(attacks[team ? 0 : 1][i][j])
				{
					return 1;
				}
				return 0;
			}	
		}
	}
	return 0; 
}
bool board::checkEnPassant( int x, int y, bool team)
{
	
	
	int checkx = x;
	int checky = team ? y+1 : y-1;

	if(inbounds(checkx,checky) && isOccupied(checkx,checky) && gameboard[checkx][checky] -> getTeam() != team && gameboard[checkx][checky] -> getType() == PAWN && ((pawn*)(gameboard[checkx][checky])) -> movedTwo())
		return true;
	return false;

}