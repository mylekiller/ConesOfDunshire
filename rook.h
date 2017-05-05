
#include <iostream>
#include "piece.h"
#ifndef ROOK_H
#define ROOK_H

//Header file for the rook class, modeled after all the different piece classes, inherits from the overall piece class
class rook:public piece
{
        public:
                rook(int, int, bool);   //default constructor with arguments for the x, y positions, and attacks
                rook(const rook&);
                ~rook();   //destructor
                void setMoves(board* bin);
                void setAttacks(board*); //gets attacks
                void print();  //prints piece

               bool operator==(const piece& pin) const;
        private:

};

#endif
