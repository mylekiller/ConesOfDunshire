#include <string.h>
#include "game.h"
#include "bishop.h"
#include "pawn.h"
#include <iostream>

//extern size_t hashvalues[12][8][8];

int* stomove(std::string, game&);
/*
size_t testHash(const board& val)
{
		size_t result = 0;
		for(int i = 0; i<8;i++)
		{
			for(int j = 0; j<8;j++)
			{
				if(val.get(i,j))
					result = result ^ hashvalues[val.get(i,j) -> getType()*(val.get(i,j) -> getTeam() ? 1 : 2)][i][j];
			}

		}
		return result;
}
*/
int main()
{
	game g;

	bool done = false;

	/*board b;
	b.addPiece(new bishop(3,3,false));
	board b2;
	b2.addPiece(new bishop(3,3,false));
	std::cout<<testHash(b)<<"\n";
	std::cout<<testHash(b2)<<"\n";
	std::cout<<(b == b2)<<"\n";
	bishop bish1(3,3,false);
	bishop bish2(3,3,false);
	std::cout<<(bish1==bish2)<<"\n";
	pawn p1(2,2,true);
	pawn p2(2,2,true);
	std::cout<<(p1 == p2)<<"\n";

	b.addPiece(&p1);
	b2.addPiece(&p2);

	std::cout<<testHash(b)<<"\n";
	std::cout<<testHash(b2)<<"\n";
	std::cout<<(b == b2)<<"\n";
	std:*/
	do
	{
		g.print();
		int * moveind;
		if(g.getTurn())
		{
			std::cout<<"White to move:  ";
			
			

			std::string input;
			std::getline(std::cin,input);
			if (input == "q") {
				std::cout << "Are you sure you want to quit? Press y for yes, press n to continue playing:    " ;
				std::cout << std::endl;
				std::string input2;
				std::getline(std::cin, input2);
				if (input2 == "y") {
					done = true;
					std::cout << "Thanks for playing!";
					std::cout << std::endl;
					break;
				}
				else if(input2 == "n" ) {
					done = false;
					continue;
				}
			} 
		
			
			moveind = stomove(input , g);
		}	
		else
		{
			std::pair<std::pair<int,int>, std::pair<int,int> > move = g.getAIMove();
			moveind = new int[4];
			moveind[0] = move.first.first;
			moveind[1] = move.first.second;
			moveind[2] = move.second.first;
			moveind[3] = move.second.second;
		}
		piece * temp = g.getpiece(moveind[0],moveind[1]);

	

		for(int i = 0; i< 4; i++)
		{
			std::cout<<moveind[i] << " | ";
		}
		std::cout<<"\n";
		if(!g.trymove(moveind[0],moveind[1],moveind[2],moveind[3]))
		{
			std::cout<<"Invalid move!\n";
		}

		delete [] moveind;
	}while(!done);

}

int* stomove(std::string input , game& g)
{
	int * result = new int[4];
	for(int i = 0; i< 4; i++)
		result[i] = 0;

	int j = 0;
	for(int i = 0; i<4;i++)
	{
		int start = j;
		while(input[j]!= ' ' && j < input.size()  )
		{
			j++;
		}
		result[i] = stoi(input.substr(start,j-start));
		j++;
	}

	
	return result;
}

