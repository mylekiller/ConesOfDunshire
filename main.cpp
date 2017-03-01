#include "knight.h"
#include <iostream>

int main()
{
	knight k(4,4,true);
	k.setMoves();
	std::cout<<"A knight at: "<<k.getX()<<","<<k.getY()<<"\n";
	std::cout<<"Can move to: \n\n";
	for(int i = 0 ; i<k.getMoves() -> size(); i++)
	{
		for(int j = 0; j<2;j++)
		{
			std::cout<<(*(k.getMoves()))[i][j];
			if(j == 0)
				std::cout<<",";
		}
		std::cout<<"\n";
	}
}