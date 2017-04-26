#include <iostream>
#include <vector>
#include "AI.h"
#include "pawn.h"
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
				std::cout<<hashvalues[t][i][j];
			}
		}
	}

	transpositions.reserve(50000);
	refutations.reserve(1000);
	std::cout<<"Randomizing the numbers...\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

AI::~AI(){}



moveResult AI::iterate(board& currentBoard, bool team, int depth)
{
	moveResult r;
	for(int d = 2; d<=depth; d++)
	{
		r = minimax(currentBoard, team, d);
		std::cout<<d<<"\n";
	}
	return r;
}

moveResult AI::minimax(board& currentBoard, bool team, int depth)
{
	double bestValue = INT_MAX;    //placeholder value, should be exceeded by anything
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
	moveResult result;

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
						std::cout<<"Skipping move... Can't move: "<<newBoard.get(i,j)->getTeam() <<" from: "<<i <<","<<j <<" to : "<<(*it)[0]<<","<< (*it)[1]<<"\n";
						continue;
					}

					newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);

					double value;
					if(team)    //fi AI is playing for white
					{
						value = minSearch(newBoard, 1, -INT_MAX, INT_MAX, depth);
						if(value > bestValue)
						{

							bestValue = 			 value;
							bestMove.first.first = 	 i;
							bestMove.first.second =  j;
							bestMove.second.first =  (*it)[0];
							bestMove.second.second = (*it)[1];
						
							result.m = bestMove;
							result.value = bestValue;
							result.depth = depth;
						}
					}
					else    //if AI is playing for black
					{
						std::cout<<"Starting max search with max depth..."<<depth<<"\n";
						value = maxSearch(newBoard, 1 , -INT_MAX, INT_MAX , depth);
						if(value < bestValue)
						{
							std::cout<<"Found a better move...\n";
							bestValue = 			 value;
							bestMove.first.first =	 i;
							bestMove.first.second =  j;
							bestMove.second.first =  (*it)[0];
							bestMove.second.second = (*it)[1];

							result.m = bestMove;
							result.value = bestValue;
							result.depth= depth;


						}
					}
				}
			}
		}
	}
	std::cout<<"The value of the best move was: "<<bestValue<<"\n";
	return result;
}

double AI::minSearch(board& currentBoard, int depth , int alpha, int beta , int maxdepth)
{


	
	if(depth == maxdepth)
	{
		std::cout<<"Evaluating with max depth == "<<maxdepth<<"\n"; 
		return evaluate(currentBoard);
	}

	int bestValue = INT_MAX;

	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0;  j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j) && !currentBoard.get(i,j)->getTeam())
			{
				bool cutoff = false;
				auto moves = currentBoard.get(i,j)->getMoves();
				for(auto it = moves->begin(); it != moves->end(); ++it)
				{
						if(isRefutation(i,j,(*it)[0],(*it)[1],depth))
						{
							board newBoard(currentBoard);
							if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], false))
							{
								continue;
							}

							newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);

							double value;
							if(transpositions.find(newBoard) != transpositions.end() &&transpositions[newBoard].depth >= maxdepth)
							{
								value = (transpositions.find(newBoard) -> second).value;
							}
							else
							{
								value = maxSearch(newBoard, depth+1 , alpha , beta, maxdepth);
								transpositions[newBoard].value = value;
								transpositions[newBoard].depth = maxdepth;
								board newnewboard(newBoard);
								std::cout<<"Initial test..."<<(newBoard==newnewboard)<<"\n";
								std::cout<<"The current size is ... "<<transpositions.size()<<"\n";
								std::cout<<"This should be tru too......."<<(transpositions[newBoard].value == value)<<"\n";
								
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
								std::cout<<"Beta cutoff in refutation move!\n";
								cutoff = true;
								break;
							}
						}
					
				}
				if(cutoff)
				{
					continue;
				}
				for(auto it = moves->begin(); it != moves->end(); ++it)
				{
					if(isRefutation(i,j,(*it)[0],(*it)[1],depth))
					{
						continue;
					}
					board newBoard(currentBoard);


					std::cout<<newBoard.get(i,j)<<"\n";
					std::cout<<currentBoard.get(i,j)<<"\n";
					if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], false))
					{
						continue;
					}


					newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);

					double value;
					if(transpositions.find(newBoard) != transpositions.end() && transpositions[newBoard].depth >= maxdepth)
					{
						std::cout<<"Found a match !!!!\n:P:P:P:P:P\n\n\n\n\n\n\n:P:P:P:P:P:P:\n\n\n\n\n\n\n";
						value = (transpositions.find(newBoard) -> second).value;
					}
					else
					{
						value = maxSearch(newBoard, depth+1 , alpha , beta, maxdepth);
						transpositions[newBoard].value=value;
						transpositions[newBoard].depth=maxdepth;
						board newnewboard(newBoard);
						std::cout<<"Initial test..."<<(newBoard==newnewboard)<<"\n";
						std::cout<<"The current size is ... "<<transpositions.size()<<"\n";
						std::cout<<"This should be tru too......."<<(transpositions[newBoard].value == value)<<"\n";
						
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
						addRefutation(i,j,(*it)[0],(*it)[1],depth,value);
						break;
					}
				}
			}
			
		}
	}
	return bestValue;
}

double AI::maxSearch(board& currentBoard, int depth , int alpha , int beta , int maxdepth)
{
	
	static int count = 0;
	if(depth == maxdepth)
	{
		return evaluate(currentBoard);
	}

	double bestValue = -INT_MAX;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j) && currentBoard.get(i,j)->getTeam())
			{

				bool cutoff = false;
				auto moves = currentBoard.get(i,j)->getMoves();

				for(auto it = moves->begin(); it != moves->end(); ++it)
				{
					if(isRefutation(i,j,(*it)[0],(*it)[1],depth))
					{
							std::cout<<"Inside the if!!!!!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
							board newBoard(currentBoard);
							if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], true))
							{
								continue;
							}
							newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);

							double value;

							if(transpositions.find(newBoard) != transpositions.end() && transpositions[newBoard].depth >= maxdepth)
							{
								std::cout<<"Found a match from refutation!!!!!\n\n\n\n\n\n\n";
								value = (transpositions.find(newBoard) -> second).value;
							}
							else
							{
								value= minSearch(newBoard, depth+1, alpha, beta,maxdepth);
								transpositions[newBoard].value=value;
								transpositions[newBoard].depth = maxdepth;
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
								std::cout<<"Alpha cutoff with refutation move!\n";
								cutoff = true;
								break;
							}
						
					}
				}
				if(cutoff)
					continue;
				for(auto it = moves->begin(); it != moves->end(); ++it)
				{
					if(isRefutation(i,j,(*it[0]),(*it)[1],depth))
					{
						std::cout<<"continue???\n";
						continue;
					}
						
					board newBoard(currentBoard);
					if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], true))
					{
						continue;
					}
					newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);

					double value;

					if(transpositions.find(newBoard) != transpositions.end() && transpositions[newBoard].depth>=maxdepth)
					{
						std::cout<<count<<"  |  Found a match!!!!!\n\n\n\n\n\n\n";
						std::cout<<"The depth is: "<<depth<<"\n";
						board testBoard;
						testBoard.addPiece(new pawn(3,4,false));
						std::cout<<(transpositions.find(testBoard) != transpositions.end()) << "\n";
						std::cout<<"The current size is: "<<transpositions.size()<<"\n";
						value = (transpositions.find(newBoard) -> second).value;
					}
					else
					{
						std::cout<<count<<"   |   Potatoes!!\n";
						count++;
						value= minSearch(newBoard, depth+1, alpha, beta,maxdepth);
						transpositions[newBoard].value=value;
						transpositions[newBoard].depth=maxdepth;
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
						addRefutation(i,j,(*it)[0],(*it)[1],depth,value);
						break;
					}
				}
			}
		}
	}
	return bestValue;
}

double AI::evaluate(board& currentBoard)
{
	double value = 0;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j))
			{
				if(currentBoard.getTeam(i,j) == true)
				{
					value += getPieceValue(currentBoard.get(i,j)->getType());
				}
				else
				{
					value -= getPieceValue(currentBoard.get(i,j)->getType());
				}
			}
		}
	}
	return value;
}

double AI::getPieceValue(enum piecetype type)
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

bool AI::isRefutation(int sx,int sy, int ex,int ey, int depth)
{
	std::cout<<"HIII!!\n\n";
	refutation r;
	r.m.first.first = sx;
	r.m.first.second = sy;
	r.m.second.first = ex;
	r.m.second.second = ey;
	r.depth = depth;
	return (refutations.find(r) != refutations.end());
}

void AI::addRefutation(int sx, int sy, int ex, int ey, int depth , int value)
{
	refutation r;
	r.m.first.first = sx;
	r.m.first.second = sy;
	r.m.second.first = ex;
	r.m.second.second = ey;
	r.depth = depth;

	refutations[r].m.first.first = sx;
	refutations[r].m.first.second = sy;
	refutations[r].m.second.first = ex;
	refutations[r].m.second.second = ey;
	refutations[r].depth = depth;
	refutations[r].value = value;

}
