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
	board.addPiece(new rook(0,0,true));
	board.addPiece(new knight(1,0,true));
	board.addPiece(new bishop(2,0,true));
	board.addPiece(new queen(3,0,true));
	board.addPiece(new king(4,0,true));
	board.addPiece(new bishop(5,0,true));
	board.addPiece(new knight(6,0,true));
	board.addPiece(new rook(7,0,true));
	for(int i = 0;i<8;i++)
	{
		board.addPiece(new pawn(i,1,true));
	}

	board.addPiece(new rook(0,7,true));
	board.addPiece(new knight(1,7,true));
	board.addPiece(new bishop(2,7,true));
	board.addPiece(new queen(3,7,true));
	board.addPiece(new king(4,7,true));
	board.addPiece(new bishop(5,7,true));
	board.addPiece(new knight(6,7,true));
	board.addPiece(new rook(7,7,true));
	for(int i = 0;i<8;i++)
	{
		board.addPiece(new pawn(i,6,true));
	}

}
game::~game(){}

void game::print()
{
	board.printBoard();
}