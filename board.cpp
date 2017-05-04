
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

	tomove = true;
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

	tomove = bin.tomove;
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


bool board::operator==( const board& bin) const
{
	for(int i = 0; i<8;i++)
	{
		for(int j = 0; j<8;j++)
		{
			if(gameboard[i][j])
			{
				if(bin.gameboard[i][j])
				{
					if((*gameboard[i][j]) == (*bin.gameboard[i][j]))
					{
						continue;
					}
				}
				
				return false;
			}
			else if(bin.gameboard[i][j])
			{
				return false;	
			}
		}
	}
	return true;
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

void board::printMovedTwo()
{
	std::cout<<"\n";
	for(int i =0; i<20;i++)
		std::cout<<"-";
	std::cout<<"\n";
	for(int i = 7; i >= 0 ;i--)
	{
		for(int j = 0;j <8;j++)
		{
			
				if(isOccupied(j,i) && gameboard[j][i] -> getType() == PAWN && ((pawn*)gameboard[j][i]) -> movedTwo())
					std::cout<<"*";
				else
					std::cout<<"X";
			
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
	for(int j = 7; j>=0;j--)
	{
		std::cout<<"|";
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
			std::cout<<"|";
		}
		std::cout<<j;
		std::cout<<"\n";
	}
	std::cout<<" ";
	for(int i =0 ; i<8;i++)
	{
		std::cout<<i;
		if(i != 7)
			std::cout<<" ";
	}
	std::cout<<"\n";
}

bool board::toMove()
{
	return tomove;
}
void board::execmove(piece * p, int x, int y, enum piecetype ptype )
{

	tomove = !tomove;
	bool team = p->getTeam();
	if(p -> getType() == PAWN) //check for an enpassant capture
	{
		int teamval = p->getTeam() ? 1 : -1;
		if((x == p->getX() +1 || x==p->getX() -1)&& y == p->getY() + teamval && !isOccupied(x,y) )
		{
			delete gameboard[x][y-teamval];
			gameboard[x][y-teamval] = NULL;
			gameboard[x][y] = p;


			
			gameboard[p->getX()][p->getY()] = NULL;

			gameboard[x][y]->move(x,y);
			update( p -> getTeam());

			return;
		} 


	}
	if(p -> getType() == KING)
	{
		if(x == p->getX() + 2)
		{
			if(gameboard[x+1][y] -> getType() == ROOK)
			{
				gameboard[x][y] = p;
				gameboard[p->getX()][p->getY()] = NULL;
				gameboard[x-1][y] = gameboard[x+1][y];
				gameboard[x+1][y] = NULL;
				p -> move(x,y);
				gameboard[x-1][y] -> move(x-1,y);
				update(p -> getTeam());
				return;
			}
		}
		if(x == p->getX() - 2)
		{
			if(gameboard[x-2][y] -> getType() == ROOK)
			{
				gameboard[x][y] = p;
				gameboard[p->getX()][p->getY()] = NULL;
				gameboard[x+1][y] = gameboard[x-2][y];
				gameboard[x-2][y] = NULL;
				p -> move(x,y);
				gameboard[x+1][y] -> move(x+1,y);
				update(p -> getTeam());
				return;
			}
		}
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

	if( p->getType() == PAWN && y == (team ? 7 : 0))
	{

		delete gameboard[x][y];
		gameboard[x][y] = NULL;
		switch(ptype)
		{
			case QUEEN:
				addPiece(new queen(x,y,team));
				break;
			case KNIGHT:
				addPiece(new knight(x,y,team));
				break;
			case ROOK:
				addPiece(new rook(x,y,team));
				break;
			case BISHOP:
				addPiece(new bishop(x,y,team));
				break;
		}
	}
	update(team);

}
void board::update(bool team)
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
				if(gameboard[i][j] -> getType() == PAWN && gameboard[i][j] -> getTeam() != team)
				{
					((pawn*)gameboard[i][j]) -> setMovedTwo(false);
				} 
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
piece* board::get(int x, int y) const
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
					if(hasMove(team))
					{
						
						return 1;
					}
					return 2;
				}
				if(!hasMove(team))
				{
					
					return 3;
				}
			
				return 0;
			}	
		}
	}

	if(!hasMove(team))
		return 3;
	return 0; 

}

bool board::inCheck(bool team)
{
	for(int i = 0; i<8;i++)
	{
		for(int j = 0; j<8;j++)
		{
			if(isOccupied(i,j) && gameboard[i][j] -> getType() == KING  && gameboard[i][j] -> getTeam() == team )
			{
				if(attacks[team ? 0 : 1][i][j])
					return true;
				return false;
			}
		}
	}
	return false;
}
bool board::hasMove(bool team)
{

	for(int i = 0; i<8;i++)
	{
		for(int j = 0; j<8;j++)
		{
			if(isOccupied(i,j) && gameboard[i][j] -> getTeam() == team )
			{
		
				auto moves = gameboard[i][j] ->getMoves();
				for(auto it = moves -> begin() ; it!=moves -> end() ; it++)
				{
					
					if(isAllowed(gameboard[i][j], (*it)[0], (*it)[1],team))
					{
			
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool board::isAllowed(piece* p , int x , int y, bool turn)
{


		std::vector<int*>* moves = p -> getMoves();
		for(auto it = moves -> begin(); it!= moves -> end(); it++)
		{
			if((*it)[0] ==x && (*it)[1] == y)
			{
				if(p -> getType() == KING)
				{
					if(x == p ->getX() - 2)
					{
						for(int cx = p->getX()-1; cx > p->getX() - 2 ; cx--)
						{
							if(attacks[p->getTeam() ? 0 : 1][cx][p->getY()] || isOccupied(cx,p->getY()))
							{
					
								return false;
							}
						}
					}
					if(x == p->getX() + 2)
					{
						for(int cx = p->getX()+1; cx < p->getX() + 2 ; cx++)
						{
							if(attacks[p->getTeam() ? 0 : 1][cx][p->getY()] || isOccupied(cx,p->getY()))
							{
								return false;
							}
						}
					}
				}
				board temp(*this);
			
				temp.execmove(temp.get(p->getX(),p->getY()),x,y);

		
				if(!temp.inCheck(turn))
				{
					return true;
				}
			}
		}
	
	return false;
}
bool board::checkEnPassant( int x, int y, bool team)
{	
	int checkx = x;
	int checky = team ? y-1 : y+1;

	if(inbounds(checkx,checky) && isOccupied(checkx,checky) && gameboard[checkx][checky] -> getTeam() != team && gameboard[checkx][checky] -> getType() == PAWN)
	{
	 	if (((pawn*)(gameboard[checkx][checky])) -> movedTwo())
			return true;
	}
	return false;
}