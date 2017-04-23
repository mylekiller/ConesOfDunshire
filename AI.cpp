#include <vector>
#include "AI.h"

AI::AI()
{

}

AI::~AI()
{

}

pair<pair<int,int>,pair<int,int>> AI::minimax(board currentBoard, bool team, int depth)
{
	int i,j;
	int bestValue = -INT_MAX;
	pair<pair<int,int>,pair<int,int>> bestMove;

	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j) && currentBoard.get(i,j)->getTeam() == team)
			{
				auto moves = currentBoard.get(i,j)->getMoves();
				for(auto it = moves.begin(); it != moves.end(); ++it)
				{
				
				}
			}
			else if(currentBoard.isOccupied(i,j) && currentBoard.get(i,j)->getTeam != team)
			{
				auto moves = currentBoard.get(i,j)->getMoves();
				for(auto it = moves.begin(); it != moves.end(); ++it)
				{
				
				}
			}
		}
	}

}

int AI::minSearch(board currentBoard, int depth)
{
	if(depth == 0)
	{
		return evaluate(board);
	}

	int bestValue = INT_MAX;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0;  j < 8; ++j)
		{
			auto moves = currentBoard.get(i,j)->getMoves();
			for(auto it = moves.begin(); it != moves.end(); ++it)
			{
				//copy board into new board
				//make the move
				//set value to maxsearch on depth-1 and new board
				//if value < bestValue set bestValue to value
			}
		}
	}
	return bestValue;
}

int AI::maxSearch(board currentBoard, int depth)
{
	if(depth == 0)
	{
		return evaluate(board);
	}

	int bestValue = -INT_MAX;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			auto moves = currentBoard.get(i,j)->getMoves();
			for(auto it - moves.begin(); it != moves.end(); ++it)
			{
				//WIP
			}
		}
	}
}

int AI::evaluate(board currentBoard)
{
	int value;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j))
			{
				if(currentBoard.getTeam(i,j) == true)
				{
					if(currentBoard.get(i,j)->getType() == KING && currentBoard.get(i,j)->getMoves()->size() == 0)
					{
						return -INT_MAX;
					}
					value += getPieceValue(currentBoard.get(i,j)->getType());
				}
				else
				{
					if(currentBoard.get(i,j)->getType() == KING && currentBoard.get(i,j)->getMoves()->size() == 0)
					{
						return INT_MAX;
					}
					value -= getPieceValue(currentBoard.get(i,j)->getType());
				}
			}
		}
	}
}

int AI::getPieceValue(enum piecetype type)
{
	switch(type)
	{
		case PAWN:
			return 1;
			break;
		case KNIGHT:
			return 3;
			break;
		case BISHOP:
			return 3;
			break;
		case ROOK:
			return 5;
			break;
		case QUEEN:
			return 9;
			break;
		case KING:
			return 0;
			break;
	}
}
