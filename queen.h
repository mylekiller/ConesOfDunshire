#include "piece.h"
#ifndef QUEEN_H
#define QUEEN_H

//Header file for the queen class, modeled after all the different piece classes, inherits from the overall piece class
class queen:public piece
{
        public:
                queen(int, int, bool);   //default constructor; args: x postion, y position, team
                queen(const queen&);
                ~queen();   //destructor
                void setMoves(board* bin); //fils vector of "moves" with all possible moves
                void setAttacks(board*); //gets possible attacks
                void print();

               bool operator==(const piece& pin) const;
        private:

};

#endif
