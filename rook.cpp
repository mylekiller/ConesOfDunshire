#include "rook.h"
#include "board.h"
void rook::setMoves(board* bin)
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
 }
 
 void rook::print()
 {
         if(getTeam())
                 std::cout<<'r';
         else
                 std::cout<<'R';
 }
 
 std::vector<int*>* rook::getAttacks()
 {
         return getMoves();
 }
 
 rook::rook(int x, int y, bool team) : piece(x,y,team)
 {
    setType(ROOK);
 }
 rook::~rook(){}