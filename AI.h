#include "board.h"
#include "piece.h"
#include <stdint.h>
#include <cstdint>
#include <climits>

#ifndef AI_H
#define AI_H

class AI{
public:
	AI();
	~AI();
	std::pair<std::pair<int,int>,std::pair<int,int>> minimax(board&, bool, int);
	int minSearch(board&, int);
	int maxSearch(board&, int);
	int evaluate(board&);    //evaluates board state; number is pieces in favor of white
	int getPieceValue(enum piecetype);    //returns value of a piece
private:

};

#endif
