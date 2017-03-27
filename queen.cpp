#include "queen.h"

void queen::setMoves(board* bin)
{
        for(int xdir = -1;xdir<=1;xdir+=2)
        {
                for(int ydir = -1;ydir<=1;ydir+=2)
                {
                        int x;
                        int y;
                        for (int dis = 1; dis <= 7; dis++) {
                                x = getX() + xdir*dis;
                                y = getY() + ydir;
                                if(inbounds(x,y))
                                {
                                        addMove(x,y);
                                }
                                x = getX() + xdir;
                                y = getY() + ydir*dis ;
                                if (inbounds(x,y))
                                        addMove(x,y);
                                x = getX() + xdir*dis;
                                y = getY() + ydir*dis;
                                if (inbounds(x,y))
                                        addMove(x,y);
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
