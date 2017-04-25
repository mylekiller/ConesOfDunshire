#include "board.h"
#include "piece.h"
#include <stdint.h>
#include <cstdint>
#include <climits>
#include <unordered_map>

#ifndef AI_H
#define AI_H



static size_t hashvalues[12][8][8];


struct boardHash{
	std::size_t operator() (const board& val) const
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

};
class AI{
public:
	AI();
	~AI();
	std::pair<std::pair<int,int>,std::pair<int,int> > minimax(board&, bool, int);
	int minSearch(board&, int , int ,int );
	int maxSearch(board&, int, int ,int );
	int evaluate(board&);    //evaluates board state; number is pieces in favor of white
	int getPieceValue(enum piecetype);    //returns value of a piece

	
private:
	std::unordered_map<board ,  int,  boardHash>  transpositions;



};

#endif
