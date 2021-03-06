//Queen implementation file that allows the queen to move left, right, up, down and diagonal any number of spaces. 
#include "queen.h"
#include "board.h"
void queen::setMoves(board* bin)
{


        for(int xdir = -1;xdir<=1;xdir+=2)
        {
                int x,y; 
                for (int dis = 1; dis <= 7; dis++) {
                        x = getX() + xdir*dis; //allows the piece to move to the right
                        y = getY();
                        if(inbounds(x,y) && bin -> isOccupied(x,y))
                        { //if inbounds, adds move
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
                        y = getY() + ydir*dis; //allows the piece to move up or down


                        if(inbounds(x,y) && bin -> isOccupied(x,y))
                        { //checks to ensure the move is in the bounds of the board and not moving through other pieces
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
                               
                                x = getX() + xdir*dis; //allows the piece to move diagonally
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

void queen::setAttacks(board* bin)
{


        for(int xdir = -1;xdir<=1;xdir+=2)
        {
                int x,y; 
                for (int dis = 1; dis <= 7; dis++) {
                        x = getX() + xdir*dis; //allows the piece to move to the right
                        y = getY();
                        if(inbounds(x,y) && bin -> isOccupied(x,y))
                        { //if inbounds, adds move
                               
                                addAttack(x,y);
                                
                                break;
                        }
                        if(inbounds(x,y))
                        {
                                addAttack(x,y);
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
                        y = getY() + ydir*dis; //allows the piece to move up or down


                        if(inbounds(x,y) && bin -> isOccupied(x,y))
                        { //checks to ensure the move is in the bounds of the board and not moving through other pieces
                               
                                addAttack(x,y);
                                
                                break;
                        }
                        if(inbounds(x,y))
                        {
                                addAttack(x,y);
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
                               
                                x = getX() + xdir*dis; //allows the piece to move diagonally
                                y = getY() + ydir*dis;


                                if(inbounds(x,y) && bin -> isOccupied(x,y))
                                {
                                       
                                        addAttack(x,y);
                                        
                                        break;
                                }
                                if(inbounds(x,y))
                                {
                                        addAttack(x,y);
                                }
                                else
                                {
                                        break;
                                }
                        }
                }
        }
        
}


bool queen::operator==(const piece& pin) const
{
        if(pin.getType() == QUEEN)
        {
                queen* p = (queen*) (&pin);
                if(p -> x == x && p->y == y && p->team==team && p->hasmoved == hasmoved)
                        return true;
        }
        return false;
}

void queen::print() //prints the queen on the board, q or Q depending on black or white pieces
{
        if(getTeam())
                std::cout<<'Q';
        else
                std::cout<<'q';
}


queen::queen(int x, int y, bool team) : piece(x,y,team)
{
        setType(QUEEN);
}
queen::queen(const queen& qin) : piece(qin.x, qin.y ,qin.team)
{
        setType(QUEEN);
        copyData((piece*)(&qin));
}
queen::~queen(){}
