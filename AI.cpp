#include <iostream>
#include <vector>
#include "AI.h"
#include "pawn.h"
#include <time.h>

#include <random>


bool breakpoint = false;

AI::AI(){


	std::random_device rd; 
	std::mt19937 gen(rd()); //seeds it

	std::uniform_int_distribution<long long> dist(0,ULONG_MAX);


	/*
	 *  Randomly assigning values to each square/piece for the purposes of hashing the chess boards
	 *
	 */
	//std::cout<<sizeof(size_t)<<"\n";
	for(size_t t = 0; t<12 ;t++)
	{
		for(size_t i = 0; i<8;i++)
		{
			for(size_t j = 0; j<8;j++)
			{
				hashvalues[t][i][j] = dist(gen);
			}
		}
	}

	transpositions.reserve(50000);
	refutations.reserve(1000);
	//std::cout<<"Randomizing the numbers...\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

AI::~AI(){}



moveResult AI::iterate(board& currentBoard, bool team, int depth)
{

	/*
	 * Uses iterative deepening and aspiration windows to come up with the best move for the AI
	 *
	 *
	 */

	moveResult r;
	r = minimax(currentBoard,team,2,-INT_MAX,INT_MAX); //starts at a low depth to find the ballpark

	for(int d = 3; d<=depth; d++)
	{
		//uses a window around the ballpark so that we can cutoff a lot more often at the higher depths
		double windowlow = r.value - 2.0;
		double windowhigh = r.value + 2.0;


		r = minimax(currentBoard, team, d , windowlow, windowhigh);

		//unfortunately, if the window is too narrow we have to do a re-search that takes forever
		if(r.value <= windowlow || r.value>=windowhigh)
		{
			r = minimax(currentBoard, team, d, -INT_MAX, INT_MAX);
		}


	}
	return r;
}

moveResult AI::minimax(board& currentBoard, bool team, int depth,double alpha,double beta)
{
	double bestValue = INT_MAX ;    //placeholder value, should be exceeded by anything
	if(team)    //if AI is playing for white
	{
		bestValue = (double ) (-INT_MAX)  -1 ;    //starting best value is large negative number
								 //white is seeking to maximize values (most positive)
		//std::cout<<"AI playing white\n";
	}
	else    //if AI is playing for black
	{
		bestValue = (double) (INT_MAX)  + 1;    //starting best value is large positive number
								//black is seeking to minimize values (most negative)
		//std::cout<<"AI playing black\n";
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
					if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], team)) {
                        //std::cout<<"Skipping move... Can't move: "<<newBoard.get(i,j)->getTeam() <<" from: "<<i <<","<<j <<" to : "<<(*it)[0]<<","<< (*it)[1]<<"\n";
                        continue;
                    }


					newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);

					double value;
					if(team)    //fi AI is playing for white
					{
						value = minSearch(newBoard, 1, alpha, beta, depth);



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
						
						value = maxSearch(newBoard, 1 ,alpha, beta , depth);

						if(value < bestValue)
						{
				
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

	return result;
}


//looks for the best move for black with current board
double AI::minSearch(board& currentBoard, int depth , double alpha, double beta , int maxdepth)
{

	//base case
	if(depth == maxdepth)
	{
		return evaluate(currentBoard);
	}

	double bestValue = beta;

	/*
	 * Loop through every move
	 */
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0;  j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j) && !currentBoard.get(i,j)->getTeam())
			{
				int count = 0;

				auto moves = currentBoard.get(i,j)->getMoves();
				/*
				 * Check the refutations first because they are more likely to cause a cutoff
				 */
				for(auto it = moves->begin(); it != moves->end(); ++it)
				{
					count++;
						if(isRefutation(i,j,(*it)[0],(*it)[1],depth))
						{
							board newBoard(currentBoard);
							/*
							 * Make sure this move is allowed (doesn't put you in check or something)
							 */
							if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], false))
							{
								continue;
							}

							//executes the move on a new board and uses that board to check further
							newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);

							//making sure we don't have checkmate on the board (if we do we need to stop)
							double eval = evaluate(newBoard);
							if(eval == INT_MAX || eval == -INT_MAX)
							{
								return eval;
							}


							double value;
							//if we already checked this position we can just return the recorded result
							if(transpositions.find(newBoard) != transpositions.end() &&transpositions[newBoard].depth >= maxdepth)
							{
								value = (transpositions.find(newBoard) -> second).value;
							}
							else
							{
								//recursive case, do a search for white's best response to this move
								value = maxSearch(newBoard, depth+1 , alpha , beta, maxdepth);

								//add a transposition once we get the value
								if(value != alpha && value != beta) {
									transpositions[newBoard].value = value;
									transpositions[newBoard].depth = maxdepth;
								}
								board newnewboard(newBoard);
							}

							//updating the value
							if(value < bestValue )
							{
								bestValue = value;
							}
							//updating beta (beta is best value for black found so for)
							if(value < beta)
							{
								beta = value;
							}

							//If beta is less than or equal to alpha, this node is guaranteed to have no effect on the final result
							if(beta <= alpha)
							{
								//std::cout<<"Beta cutoff in refutation move!\n";

								return beta;
							}
						}
						else
						{
							//std::cout<<"Nope!\n";
						}
					
				}

				/*
				 *  Doing the same thing as above but for the normal moves (not refutations)   :
				 *
				 */
				for(auto it = moves->begin(); it != moves->end(); ++it)
				{
					if(isRefutation(i,j,(*it)[0],(*it)[1],depth))
					{
						continue;
					}
					board newBoard(currentBoard);

					if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], false))
					{
						continue;
					}


					newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);
					double eval = evaluate(newBoard);
					if(eval == INT_MAX || eval == -INT_MAX)
					{
						return eval;
					}

					double value;
					if(transpositions.find(newBoard) != transpositions.end() && transpositions[newBoard].depth >= maxdepth)
					{

						value = (transpositions.find(newBoard) -> second).value;
					}
					else
					{
						value = maxSearch(newBoard, depth+1 , alpha , beta, maxdepth);
						if(value != alpha && value != beta) {
							transpositions[newBoard].value = value;
							transpositions[newBoard].depth = maxdepth;
						}
						board newnewboard(newBoard);
						
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
						//std::cout<<"Beta cutoff!\n";
						addRefutation(i,j,(*it)[0],(*it)[1],depth,value);
						return beta;
					}
				}
			}
			
		}
	}
	return bestValue;
}


/*
 *
 * Same things as min search but looking for max value and dealing with alpha instead of beta
 *
 *
 */
double AI::maxSearch(board& currentBoard, int depth , double alpha , double beta , int maxdepth)
{
	
	static int count = 0;
	if(depth == maxdepth)
	{
		return evaluate(currentBoard);
	}

	double bestValue = alpha;
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j) && currentBoard.get(i,j)->getTeam())
			{

				auto moves = currentBoard.get(i,j)->getMoves();

				for(auto it = moves->begin(); it != moves->end(); ++it)
				{
					if(isRefutation(i,j,(*it)[0],(*it)[1],depth))
					{
							board newBoard(currentBoard);
							if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], true))
							{
								continue;
							}
							newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);


							double eval = evaluate(newBoard);
							if(eval == INT_MAX || eval == -INT_MAX)
							{
								return eval;
							}

							double value;

							if(transpositions.find(newBoard) != transpositions.end() && transpositions[newBoard].depth >= maxdepth)
							{
								value = (transpositions.find(newBoard) -> second).value;
							}
							else
							{
								value= minSearch(newBoard, depth+1, alpha, beta,maxdepth);
								if(value != alpha && value != beta) {
									transpositions[newBoard].value = value;
									transpositions[newBoard].depth = maxdepth;
								}
							}

							//doesnt work if you start with a set window for alpha and beta 
							// works if you start with INT_MAX and -INT_MAX

							if(value > bestValue) //update bestValue
							{
								bestValue = value;
							}
							if(value > alpha ) //Update the best from this depth (alpha)
							{
								alpha = value;
							}
							if(beta <= alpha) // If the lowest value at a higher depth (beta) is less than or equal to the highest from
												//this depth (alpha), we can break.
							{
								//std::cout<<"Alpha cutoff with refutation move!\n";

								return alpha;
							}
							removeRefutation(i,j,(*it)[0],(*it)[1],depth,value);
						
					}
				}

				for(auto it = moves->begin(); it != moves->end(); ++it)
				{
					if(isRefutation(i,j,(*it[0]),(*it)[1],depth))
					{
				
						continue;
					}
						
					board newBoard(currentBoard);
					if(!newBoard.isAllowed(newBoard.get(i,j), (*it)[0], (*it)[1], true))
					{
						continue;
					}
					newBoard.execmove(newBoard.get(i,j), (*it)[0], (*it)[1]);


					double eval = evaluate(newBoard);
					if(eval == INT_MAX || eval == -INT_MAX)
					{
						return eval;
					}
					double value;

					if(transpositions.find(newBoard) != transpositions.end() && transpositions[newBoard].depth>=maxdepth)
					{
					
						value = (transpositions.find(newBoard) -> second).value;
					}
					else
					{
						count++;
						value= minSearch(newBoard, depth+1, alpha, beta,maxdepth);
						if(value != alpha && value != beta) {
							transpositions[newBoard].value = value;
							transpositions[newBoard].depth = maxdepth;
						}
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
						//std::cout<<"Alpha cutoff!\n";
						addRefutation(i,j,(*it)[0],(*it)[1],depth,value);
						return alpha;
					}
				}
			}
		}
	}
	return bestValue;
}


/*
 * Makes a best guess at judging the state of the board it gets passed
 *
 */
double AI::evaluate(board& currentBoard)
{
	bool team = currentBoard.toMove();
	double value = 0 , mater=0, center =0 , ksaf = 0, mob = 0; //these are the factors we added
	/*
	 * Material
	 * Center control
	 * King safety
	 * Mobility
	 *
	 */
	int checkval = currentBoard.check(team);

	int control[8][8];
	for(int i = 0;i<8;i++)
	{
		for(int j = 0; j<8;j++)
		{
			control[i][j] = 0;
		}
	}

	//Checking the easy cases
	switch(checkval)
	{
		case 2:
			return INT_MAX * (team ? -1 : 1); //checkmate
		
			break;
		case 3:
			return 0; //stalemate
			break;
	}

	/*
	 * Calculating material
	 */
	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if(currentBoard.isOccupied(i,j))
			{
				if(currentBoard.getTeam(i,j) == true)
				{
					mater += getPieceValue(currentBoard.get(i,j)->getType());
				}
				else
				{
					mater -= getPieceValue(currentBoard.get(i,j)->getType());
				}

				auto attacks = currentBoard.get(i,j) -> getAttacks();
				for(auto it = attacks -> begin();it!= attacks -> end();it++)
				{
					control[(*it)[0]][(*it)[1]] += (currentBoard.get(i,j)->getTeam() ? 1 : -1);
				}
			}
		}
	}

	//calculating center control
	for(int i = 3;i<5;i++)
	{
		for(int j = 3; j<5;j++)
		{
			center+=control[i][j];
		}
	}

	//calculating king safety
	for(int i = 0; i<8;i++)
	{
		for(int j = 0; j<8;j++)
		{
			if(currentBoard.inbounds(i,j) && currentBoard.isOccupied(i,j) && currentBoard.get(i,j) -> getType() == KING)
			{
				for(int x = i-1;x<i+2;x++)
				{
					for(int y = j-1;y<j+2;y++)
					{
						if(currentBoard.inbounds(x,y))
						{
							ksaf += control[x][y];
						}
					}
				}
			}
		}
	}

	//calculating mobility
	if(checkval == 0)
	{
		for(int i = 0; i<8;i++)
		{
			for(int j = 0; j<8;j++)
			{
				if(currentBoard.isOccupied(i,j))
				{
				
					mob += (double) (currentBoard.get(i,j) -> getMoves() -> size() ) * (currentBoard.get(i,j) -> getTeam() ? 1 : -1);
				}
			}
		}
	}
	else
	{
		mob = 0;
	}


	//getting the final value using weights on each factor
	value = mater + 0.2 * center + 0.05 * mob + 0.02 * ksaf;

	return value;
}

//just gives us the relative value of each piece
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
    return -1;
}

/*
 *
 * Helper functions to deal with the refutations hash
 *
 */
bool AI::isRefutation(int sx,int sy, int ex,int ey, int depth)
{

	refutation r;
	r.m.first.first = sx;
	r.m.first.second = sy;
	r.m.second.first = ex;
	r.m.second.second = ey;
	r.depth = depth;
	return (refutations.find(r) != refutations.end());
}

void AI::addRefutation(int sx, int sy, int ex, int ey, int depth , double value)
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
void AI::removeRefutation(int sx, int sy, int ex, int ey, int depth , double value)
{
	refutation r;
	r.m.first.first = sx;
	r.m.first.second = sy;
	r.m.second.first = ex;
	r.m.second.second = ey;
	r.depth = depth;


	refutations.erase(r);



}
