#include "piece.h"
#ifndef QUEEN_H
#define QUEEN_H


class queen:public piece
{
        public:
                queen(int, int, bool);   //default constructor; args: x postion, y position, team
                queen(const queen&);
                ~queen();   //destructor
                void setMoves(board* bin);
                void setAttacks(board*);
                void print();
        private:

};

#endif
