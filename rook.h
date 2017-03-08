#include <iostream>
#include "piece.h"
#ifndef ROOK_H
#define ROOK_H


class rook:public piece
{
        public:
                rook(int, int, bool);   //default constructor; args: x postion, y position, team
                ~rook();   //destructor
                void setMoves(board* bin);
                std::vector<int*>* getAttacks();
                void print();
        private:

};

#endif
