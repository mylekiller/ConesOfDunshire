# Chess

A implementation of chess where users can play against each other or a computer 
player implemented using a custom minimax algorithm and SDL2 Graphics.

Authors: Kyle Miller, MacKenzie Cavanagh, Andrew Callahan, Christopher Clarizio

CSE 20312 Data Structures Spring 2017

Started: 03/01/17

Completed: 04/05/17

Features: What you can do with the program
This program is a chess game that allows the user to decide between a two player mode and playing against the computer. We used a graphics program (SDL2) that allows the user to see the chessboard and their moves easier. The first screen the user sees once running the game, is the option to choose between two player and computer play game (the main screen). Once the user has choosen a mode, the chess board with all the pieces appears (black on the top of the board and white on the bottom). You can then play out a full game of chess. To end the program, you can simply exit out of the screen. If someone wins, by achieving checkmate, then a screen will appear annoucing who won. Similarly, if there is a stalemate, then a screen will appear. By pressing enter, the original main screen will then appear and the user can choose to play another game. 

Usage: How to use the program
When the user first runs the program, they are prompted for which type of play they want to do to: 2 player mode or playing the computer. Then a chessboard appears in the GUI with all the pieces set up on the board. The user can move their pieces according to the rules of Chess. We included in our rules the general rules of chess, including castling, promotion, and en passant. If the user tries to perform an illegal move, the piece will not move and the user must then move the piece in another, legal way. The previous move remains highlighted yellow so that players can see the move recent move. This feature was included because many online chess games contain this for user friendliness. The game continues like this until either white wins (by checkmate), black wins (by checkmate), stalemate, or someone quits the game. If white wins, a message appears on the screen annoucing "Checkmate! White wins". If black wins, "Checkmate! Black wins" will appear and if there is a stalemate, "Stalemate" appears. The user can then exit out of the screen to end the program or they can press enter to be brought back to the main screen.  

Design: How things are structured
For our chess game, we created a class for each type of piece (King, Queen, Bishop, Knight, Rook, and Pawn) that all inherit from the overall piece class. Each piece class has the specific moves that a piece can do. For example, the Knight class has that the Knight pieces can only move in an "L" shape. The board class creates an 8 by 8 chess board that the pieces are then placed on and has functions to print the board, get attacks and move the pieces. The overall game class adds the correct number of pieces to the board in the correct order. 

User Manual for needed software and how to run program:
To run the program, the user must have access to SDL2 graphics. The user can play in the terminal without the SDL2 graphics, but the board is harder to see. The user must download all the chess pieces, board, game, etc. files in order to play the game. We have included a Makefile that will compile the program. By running make, two executables are created. The chess executable can be run by doing ./chess and this program uses the SDL2 graphics. The second exectuable file is runchess.out and the user can run the game this way if they do not have access to SDL2 graphics
