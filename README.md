# Chess

A implementation of chess where users can play against each other or a computer 
player implemented using a custom minimax algorithm and SDL2 Graphics.

Authors: Kyle Miller, MacKenzie Cavanagh, Andrew Callahan, Christopher Clarizio

CSE 20312 Data Structures Spring 2017

Started: 03/01/17

Completed: 04/--/17

Features: What you can do with the program
This program is a chess game that allows the user to decide between a two player mode and playing against the computer. We used a graphics program (SDL2) that allows the user to see the chessboard and their moves easier. The first screen the user sees once running the game, is the option to choose between two player and computer play game. Once the user has choosen a mode, the chess board with all the pieces appears. You can then play out a full game of chess. To end the program, you can simply exit out of the screen, or you can press q, which will then ask you if you want to quit the game. If you answer yes, then the program returns you to the main screen you initially see. If you answer no, the game continues. 

Usage: How to use the program
When the user first runs the program, they are prompted for which type of play they want to do to: 2 player mode or playing the computer. Then a chessboard appears in the GUI with all the pieces set up on the board. The user can move their pieces according to the rules of Chess. We included in our rules the general rules of chess, including castling, promotion, and en passant. If the user tries to perform an illegal move, the piece will not move and the user must then move the piece in another, legal way. The game continues like this until either white wins (by checkmate), black wins (by checkmate), stalemate, or someone quits the game. If white wins, a message appears on the screen (same if black wins or if there is a stalemate). 

Design: How things are structured

User Manual for needed software and how to run program:
1. Need to download SDL2 onto machine 
