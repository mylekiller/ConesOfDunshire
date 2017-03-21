#include "piece.h"
#ifndef QUEEN_H
#define QUEEN_H


class queen:public piece
{
        public:
                queen(int, int, bool);   //default constructor; args: x postion, y position, team
                ~queen();   //destructor
                void setMoves(board* bin);
                std::vector<int*>* getAttacks();
                void print();
        private:

};

#endif
