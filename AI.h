#include "board.h"
#include "piece.h"
#include <stdint.h>
#include <cstdint>
#include <climits>
#include <unordered_map>

#ifndef AI_H
#define AI_H



static long long int hashvalues[12][8][8];


typedef std::pair<std::pair<int,int>,std::pair<int,int> > move;

struct refutation
{
	move m;
	int depth;
	bool operator==(const refutation& min) const
	{
		return m.first.first == min.m.first.first && m.first.second == min.m.first.second && m.second.first==min.m.second.first && m.second.second == min.m.second.second && depth == min.depth;
	}
};
struct moveResult{
	move m;
	double value;
	int depth;

	bool operator==(const moveResult& min) const
	{
		return m.first.first == min.m.first.first && m.first.second == min.m.first.second && m.second.first==min.m.second.first && m.second.second == min.m.second.second && value == min.value && depth == min.depth;
	}

};
struct movesHash{
	std::size_t operator() (const refutation& val) const
	{
		size_t result = 0;
		result = result ^ (val.m.first.first * hashvalues[0][0][0]);
		result = result ^ (val.m.first.second * hashvalues[1][0][0]);
		result = result ^ (val.m.second.first * hashvalues[2][0][0]);
		result = result ^ (val.m.second.second * hashvalues[3][0][0]);
		return result;
	}
};
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
	moveResult minimax(board&, bool, int,double,double);
	moveResult iterate(board&, bool, int);
	double minSearch(board&, int , double ,double,int );
	double maxSearch(board&, int, double ,double ,int);
	double evaluate(board&);    //evaluates board state; number is pieces in favor of white
	double getPieceValue(enum piecetype);    //returns value of a piece
	bool isRefutation(int,int,int,int,int);
	void addRefutation(int,int,int,int,int,double);
	void removeRefutation(int ,int,int,int,int,double);

	
private:
	std::unordered_map<board ,  moveResult,  boardHash>  transpositions;

	std::unordered_map<refutation,moveResult,movesHash > refutations;



};

#endif
