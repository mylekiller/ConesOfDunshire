#include "game.h"
#include "rook.h"
#include "pawn.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "king.h"
game::game()
{
	turn = true;
	boardGame.addPiece(new rook(0,0,true));
	boardGame.addPiece(new knight(1,0,true));
	boardGame.addPiece(new bishop(2,0,true));
	boardGame.addPiece(new queen(3,0,true));
	boardGame.addPiece(new king(4,0,true));
	boardGame.addPiece(new bishop(5,0,true));
	boardGame.addPiece(new knight(6,0,true));
	boardGame.addPiece(new rook(7,0,true));
	for(int i = 0;i<8;i++)
	{
		boardGame.addPiece(new pawn(i,1,true));
	}

	boardGame.addPiece(new rook(0,7,false));
	boardGame.addPiece(new knight(1,7,false));
	boardGame.addPiece(new bishop(2,7,false));
	boardGame.addPiece(new queen(3,7,false));
	boardGame.addPiece(new king(4,7,false));
	boardGame.addPiece(new bishop(5,7,false));
	boardGame.addPiece(new knight(6,7,false));
	boardGame.addPiece(new rook(7,7,false));



	for(int i = 0;i<8;i++)
	{
		boardGame.addPiece(new pawn(i,6,false));
	}
	boardGame.update();

}
game::~game(){}

piece* game::getpiece(int x,int y)
{
	return boardGame.get(x,y);
}
void game::print()
{
	boardGame.printBoard();
}
bool game::getTurn()
{
	return turn;
}
bool game::trymove(int sx,int sy, int tx, int ty)
{
	if(boardGame.isOccupied(sx,sy) && boardGame.getTeam(sx,sy) == turn)
	{
		std::vector<int*>* moves = (boardGame.get(sx,sy)) -> getMoves();
		for(auto it = moves -> begin(); it!= moves -> end(); it++)
		{
			if((*it)[0] ==tx && (*it)[1] == ty)
			{
				//check the check
				boardGame.execmove(boardGame.get(sx,sy),tx,ty);
				turn = !turn;
				return true;
			}
		}
	}
	return false;
}
