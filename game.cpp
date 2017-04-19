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

	boardGame.addPiece(new rook(0,7,true));
	boardGame.addPiece(new knight(1,7,true));
	boardGame.addPiece(new bishop(2,7,true));
	boardGame.addPiece(new queen(3,7,true));
	boardGame.addPiece(new king(4,7,true));
	boardGame.addPiece(new bishop(5,7,true));
	boardGame.addPiece(new knight(6,7,true));
	boardGame.addPiece(new rook(7,7,true));
	for(int i = 0;i<8;i++)
	{
		boardGame.addPiece(new pawn(i,6,true));
	}

}
game::~game(){}

void game::print()
{
	boardGame.printBoard();
}
