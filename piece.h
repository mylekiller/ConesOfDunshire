#include <vector>



#ifndef PIECE_H
#define	PIECE_H

class piece{
public:
	piece(int , int,bool);
	~piece();
	virtual void setMoves() = 0;
	virtual std::vector<int*>* getAttacks() = 0;
	std::vector<int*>* getMoves();
	int getX();
	int getY();
	bool getTeam();


protected:	
	std::vector<int*> moves;
	void addMove(int , int);
	
	bool inbounds(int,int);


private:
	int x;
	int y;

	bool team;

};

#endif