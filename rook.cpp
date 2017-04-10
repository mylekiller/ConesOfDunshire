#include "rook.h"

void rook::setMoves(board* bin)
{
        for(int xdir = -1;xdir<=1;xdir+=2)
        {
             for(int ydir = -1;ydir<=1;ydir+=2)
             {
                     int x = getX() + xdir;
                     int y = getY();

                     if(inbounds(x,y))
                     {
                          addMove(x,y);
                     }

                     x = getX();
                     y = getY() + ydir;
                     if(inbounds(x,y))
                     {
                          addMove(x,y);
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
 }
 rook::~rook(){}