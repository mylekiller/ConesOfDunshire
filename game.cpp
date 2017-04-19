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
}