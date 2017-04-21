
#include "game.h"
#include <iostream>

int* stomove(std::string, game&);
int main()
{
	game g;
	bool done = false;
	do
	{
		g.print();
		if(g.getTurn())
		{
			std::cout<<"White to move:  ";
		}
		else
		{
			std::cout<<"Black to move:  ";
		}

		std::string input;
		std::getline(std::cin,input);

		int * moveind = stomove(input , g);
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

