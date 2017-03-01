
#include "board.h"

bool board::inBounds(int x, int y)
{
	return x>= 0 && x<8 && y>=0 && y<8;
}