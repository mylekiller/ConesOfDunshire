#include <iostream>
#include <vector>
#include "AI.h"
#include <time.h>

AI::AI(){

	srand(time(NULL));
	for(size_t t = 0; t<12 ;t++)
	{
		for(size_t i = 0; i<8;i++)
		{
			for(size_t j = 0; j<8;j++)
			{
				hashvalues[t][i][j] = rand();
			}
		}
	}

	transpositions.reserve(50000);
	std::cout<<"Randomizing the numbers...\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

AI::~AI(){}

std::pair<std::pair<int,int>,std::pair<int,int>> AI::minimax(board& currentBoard, bool team, int depth)
{
	int bestValue = INT_MAX;    //placeholder value, should be exceeded by anything
	if(team)    //if AI is playing for white
	{
		bestValue = -INT_MAX;    //starting best value is large negative number
								 //white is seeking to maximize values (most positive)
		std::cout<<"AI playing white\n";
	}
	else    //if AI is playing for black
	{
		bestValue = INT_MAX;    //starting best value is large positive number
								//black is seeking to minimize values (most negative)
		std::cout<<"AI playing black\n";
	}

	std::pair<std::pair<int,int>,std::pair<int,int>> bestMove;    //tracks the best move that been found

	for(int i = 0; i < 8; ++i)    //iterates through the 8x8
	{
		for(int j = 0; j < 8; ++j)
		{
			//if the current space occupied and the piece is the color the AI is playing
			if(currentBoard.isOccupied(i,j) && currentBoard.get(i,j)->getTeam() == team)
			{
				
				//list of moves piece in current sqaure can make
				std::vector<int*>* moves = currentBoard.get(i,j)->getMoves();
				//iterate through all the moves the piece in current sqaure can make
				for(auto it = moves->begin(); it != moves->end(); ++it)
				{

					board newBoard(currentBoard);    //newBoard is where each move is tried
					if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], team))
					{
						std::cout<<"Skipping move... Can't move: "<<newBoard.get(i,j)->getTeam() <<" from: "<<newBoard.get(i,j) -> getX() <<","<<newBoard.get(i,j)->getY() <<" to : "<<(*it)[0]<<","<< (*it)[1]<<"\n";
						continue;
					}

					newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);

					int value;
					if(team)    //fi AI is playing for white
					{
						value = minSearch(newBoard, depth-1 , -INT_MAX, INT_MAX);
						if(value > bestValue)
						{

							bestValue = 			 value;
							bestMove.first.first = 	 i;
							bestMove.first.second =  j;
							bestMove.second.first =  (*it)[0];
							bestMove.second.second = (*it)[1];
						}
					}
					else    //if AI is playing for black
					{
						value = maxSearch(newBoard, depth-1 , -INT_MAX, INT_MAX);
						if(value < bestValue)
						{
							std::cout<<"Found a better move...\n";
							bestValue = 			 value;
							bestMove.first.first =	 i;
							bestMove.first.second =  j;
							bestMove.second.first =  (*it)[0];
							bestMove.second.second = (*it)[1];
						}
					}
				}
			}
		}
	}
	std::cout<<"The value of the best move was: "<<bestValue<<"\n";
	return bestMove;
}

int AI::minSearch(board& currentBoard, int depth , int alpha, int beta)
{
	
	if(depth == 0)
	{
		return evaluate(currentBoard);
	}

	int bestValue = INT_MAX;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0;  j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j) && !currentBoard.get(i,j)->getTeam())
			{
				auto moves = currentBoard.get(i,j)->getMoves();
				for(auto it = moves->begin(); it != moves->end(); ++it)
				{
					board newBoard(currentBoard);
					if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], false))
					{
						continue;
					}

					newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);

					int value;
					if(transpositions.find(newBoard) != transpositions.end())
					{
						value = transpositions.find(newBoard) -> second;
					}
					else
					{
						value = maxSearch(newBoard, depth-1 , alpha , beta);
						transpositions[newBoard]=value;
						board newnewboard(newBoard);
						std::cout<<"Initial test..."<<(newBoard==newnewboard)<<"\n";
						std::cout<<"The current size is ... "<<transpositions.size()<<"\n";
						std::cout<<"This should be tru too......."<<(transpositions[newBoard] == value)<<"\n";
						
						std::cout<<"This should be tru:...."<<transpositions.count(newBoard)<<"\n";

						std::cout<<"Final test..." << (newBoard == newnewboard)<<"\n";
					}
					if(value < bestValue )
					{
						bestValue = value;
					}

					if(value < beta)
					{
						beta = value;
					}
					if(beta <= alpha)
					{
						std::cout<<"Beta cutoff!\n";
						break;
					}
				}
			}
		}
	}
	return bestValue;
}

int AI::maxSearch(board& currentBoard, int depth , int alpha , int beta)
{
	
	if(depth == 0)
	{
		return evaluate(currentBoard);
	}

	int bestValue = -INT_MAX;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j) && currentBoard.get(i,j)->getTeam())
			{
				auto moves = currentBoard.get(i,j)->getMoves();
				for(auto it = moves->begin(); it != moves->end(); ++it)
				{
					board newBoard(currentBoard);
					if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], true))
					{
						continue;
					}
					newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);

					int value;

					if(transpositions.find(newBoard) != transpositions.end())
					{
						std::cout<<"Found a match!!!!!\n\n\n\n\n\n\n";
						value = transpositions.find(newBoard) -> second;
					}
					else
					{
						value= minSearch(newBoard, depth-1, alpha, beta);
						transpositions[newBoard]=value;
					}
					if(value > bestValue)
					{
						bestValue = value;
					}
					if(value > alpha )
					{
						alpha = value;
					}
					if(beta <= alpha)
					{
						std::cout<<"Alpha cutoff!\n";
						break;
					}
				}
			}
		}
	}
	return bestValue;
}

int AI::evaluate(board& currentBoard)
{
	int value = 0;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j))
			{
				if(currentBoard.getTeam(i,j) == true)
				{
					/*
					if(currentBoard.get(i,j)->getType() == KING && currentBoard.get(i,j)->getMoves()->size() == 0)
					{
						return -INT_MAX;
					}
					*/
					value += getPieceValue(currentBoard.get(i,j)->getType());
				}
				else
				{
					/*
					if(currentBoard.get(i,j)->getType() == KING && currentBoard.get(i,j)->getMoves()->size() == 0)
					{
						return INT_MAX;
					}
					*/
					value -= getPieceValue(currentBoard.get(i,j)->getType());
				}
			}
		}
	}
	return value;
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
