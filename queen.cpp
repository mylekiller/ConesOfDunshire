
#include "queen.h"
#include "board.h"
void queen::setMoves(board* bin)
{


        for(int xdir = -1;xdir<=1;xdir+=2)
        {
                int x,y; 
                for (int dis = 1; dis <= 7; dis++) {
                        x = getX() + xdir*dis;
                        y = getY();
                        if(inbounds(x,y) && bin -> isOccupied(x,y))
                        {
                                if(bin -> getTeam(x,y) != getTeam())
                                {
                                        addMove(x,y);
                                }
                                break;
                        }
                        if(inbounds(x,y))
                        {
                                addMove(x,y);
                        }
                        else
                        {
                                break;
                        }
                }
        }       

        for(int ydir = -1; ydir<=1; ydir+=2)
        {     
                int x,y;  
                for (int dis = 1; dis <= 7; dis++) {
                        x = getX();
                        y = getY() + ydir*dis;


                        if(inbounds(x,y) && bin -> isOccupied(x,y))
                        {
                                if(bin -> getTeam(x,y) != getTeam())
                                {
                                        addMove(x,y);
                                }
                                break;
                        }
                        if(inbounds(x,y))
                        {
                                addMove(x,y);
                        }
                        else
                        {
                                break;
                        }
                }
        }
                       

        for(int xdir = -1;xdir<=1;xdir+=2)
        {
                for(int ydir = -1;ydir<=1;ydir+=2)
                {
                        for (int dis = 1; dis <= 7; dis++) 
                        {
                                int x;
                                int y;
                               
                                x = getX() + xdir*dis;
                                y = getY() + ydir*dis;


                                if(inbounds(x,y) && bin -> isOccupied(x,y))
                                {
                                        if(bin -> getTeam(x,y) != getTeam())
                                        {
                                                addMove(x,y);
                                        }
                                        break;
                                }
                                if(inbounds(x,y))
                                {
                                        addMove(x,y);
                                }
                                else
                                {
                                        break;
                                }
                        }
                }
        }
        
}

void queen::print()
{
        if(getTeam())
                std::cout<<'q';
        else
                std::cout<<'Q';
}

std::vector<int*>* queen::getAttacks()
{
        return getMoves();
}

queen::queen(int x, int y, bool team) : piece(x,y,team)
{
}
queen::~queen(){}