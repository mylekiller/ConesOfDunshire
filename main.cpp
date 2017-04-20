
#include "game.h"
#include <iostream>

int* stomove(std::string, game&);
int main()
{
	game g;
	bool done;
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



	}while(!done);

}

int* stomove(std::string, game&)
{
	int * result = new int[4];
	for(int i = 0; i< 4; i++)
		result[i] = 0;


}

