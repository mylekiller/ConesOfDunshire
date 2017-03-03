
#include "knight.h"
#include "bishop.h"
#include "board.h"
#include <iostream>

int main()
{
	board bo;

	bishop b(0,0,true);
	bishop b2(4,4,true);

	bo.addPiece(&b,0,0);
	bo.addPiece(&b2,4,4);

	bo.printBoard();


	std::cout<<"\n\n";

	b.setMoves(&bo);
	std::cout<<b.getMoves() -> size()<<"\n";
	for(int i = 0 ; i< b.getMoves()->size();i++)
	{
		std::cout<<((*b.getMoves())[i] == nullptr)<<"\n";
		std::cout<<(*b.getMoves())[i][0]<<","<<(*b.getMoves())[i][1]<<"\n";
		std::cout<<b.getMoves() -> size()<<"\n";
	}

}

