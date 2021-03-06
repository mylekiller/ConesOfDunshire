#include <vector>

#include <iostream>

#ifndef PIECE_H
#define	PIECE_H
//Piece header file that contains properties that all 6 pieces inherit
enum piecetype
{
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
};	


class board;
class piece
{
public:
	piece(int, int, bool);   //defualt constructor; args: x position, y position, team (black/white)
	virtual ~piece();   //default constructor
	virtual void setMoves(board*) = 0;   //setter function; sets the moves possible for the piece
	virtual void setAttacks(board*) = 0;
	std::vector<int*>* getMoves();   //getter function; returns pointer to vector of possible moves
	std::vector<int*>* getAttacks();
	void resetMoves();   //clears the vector "moves" to allow it to be updated
	void resetAttacks();
	void setX(int);   //setter function; sets the current x position of the piece
	int getX();   //getter function; gets the current x position of the piece
	void setY(int);   //setter function; sets the current y position of the piece
	int getY();   //getter function; gets the current y position of the piece
	void setTeam(bool);   //setter function; sets the team of the piece
	bool getTeam();   //getter function; gets the team of the current piece
	bool hasMoved();
	void move(int, int);   //"moves" the piece sets the pieces position to (x,y)
	bool canMove();
	void reset();
	void update(board*);
	void copyData(piece*);
	virtual void print() = 0;
	piecetype getType() const;

	virtual bool operator==(const piece& pin) const  = 0;
protected:
	void setType(enum piecetype);
	std::vector<int*> moves;   //vector of pointers to integers arrays; represents the possible moves
	std::vector<int*> attacks;
	void addMove(int, int);   //adds the possibility of a move to a specific space
	void addAttack(int , int);
	bool inbounds(int,int);   //reutrns whethere a space is on the board

	int x;   //piece's current x position
	int y;   //piece's current y position
	bool team;   //piece's team; whether piece is white (true=white, false=black)
	bool hasmoved;
	piecetype type; // the type of the piece
private:
	
};


#endif
