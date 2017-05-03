# Chess

A implementation of chess where users can play against each other or a computer player implemented using a custom minimax algorithm and SDL2 Graphics.

Authors: Kyle Miller, MacKenzie Cavanagh, Andrew Callahan, Christopher Clarizio

CSE 20312 Data Structures Spring 2017

Started: 03/01/17

Completed: 04/05/17

Features: What you can do with the program 
* This program is a chess game that allows the user to decide between a two player mode and playing against the computer. We used a graphics program (SDL2) that allows the user to see the chessboard and their moves easier. The first screen the user sees once running the game, is the option to choose between two player and computer play game (the main screen). Once the user has chosen a mode, the chess board with all the pieces appears (black on the top of the board and white on the bottom). You can then play out a full game of chess. To end the program, you can simply exit out of the screen. If someone wins, by achieving checkmate, then a screen will appear announcing who won. Similarly, if there is a stalemate, then a screen will appear. By pressing enter, the original main screen will then appear and the user can choose to play another game.

Usage: How to use the program 
* When the user first runs the program, they are prompted for which type of play they want to do to: 2 player mode or playing the computer. Then a chessboard appears in the GUI with all the pieces set up on the board. The user can move their pieces according to the rules of Chess. We included in our rules the general rules of chess, including castling, promotion, and en passant. If the user tries to perform an illegal move, the piece will not move and the user must then move the piece in another, legal way. The previous move remains highlighted yellow so that players can see the move recent move. This feature was included because many online chess games contain this for user friendliness. The game continues like this until either white wins (by checkmate), black wins (by checkmate), stalemate, someone quits the game, the players agree to draw, or the player wants to start a newgame. If white wins, a message appears on the screen announcing "Checkmate! White wins". If black wins, "Checkmate! Black wins" will appear and if there is a stalemate, "Stalemate" appears. The user can then exit out of the screen to end the program or they can press enter to be brought back to the main screen. During the game if the players agree to draw a player can press the ‘a’ key on the keyboard and this will take them to the stalemate screen where they can then press enter to start a new game or q to quit. If the players are frustrated with their current game they can chose to start a new game by pressing ‘n’ on the keyboard which will take the player back to the selection screen. One small known bug in the game is that when playing against the AI a very large amount of data is stored in a hash table in order to store refutations and transpositions due to this when trying to exit/restart the game while playing the AI this command can hang for a few seconds before actually being executed as the large amount of allocated memory is freed. 

Design: How things are structured 
* For our chess game, we created a class for each type of piece (King, Queen, Bishop, Knight, Rook, and Pawn) that all inherit from the overall piece class. Each piece class has the specific moves that a piece can do. For example, the Knight class has that the Knight pieces can only move in an "L" shape. The board class creates an 8 by 8 chess board that the pieces are then placed on and has functions to print the board, get attacks and move the pieces. The overall game class adds the correct number of pieces to the board in the correct order (8 pawns in the front row and Rook, Knight, Bishop, King, Queen, Bishop, Knight, Rook in the back row). This is compiled into a chesslib.a which is then used to create the chess executable file. The chess executable file is compiled by using the chesslib, the AI, and the Graphics files. 

User Manual for needed software and how to run program 
* To run the program, the user must have access to SDL2 graphics. To compile the program the user justs types the make command at the command line, then to run the graphics they user runs the program called chess. The user must download all the chess pieces, board, game, etc. files in order to play the game, these files must be stored in a folder in the directory where the program is being run from in a folder called images. The chess executable can be run by doing ./chess and this program uses the SDL2 graphics. See the above section on usage to see how the program is interacted with. 
The chess game follows the traditional rules of chess so a user should follow these rules for the game (but skip step 1):
https://www.chess.com/learn-how-to-play-chess
We are assuming the user is familiar with the game of chess and can play the game. If not, the above link goes through the rules. 

Group time log:
*3/1/2017 (2 hours) : Created initial classes and makefiles (just the structure) while totally paying attention in systems and stats
*3/1/2017 (30 Min): Kyle, Chris and Drew made sure that the github repo was working correctly and made sure that everyone could commit to the repo. Creating an initial makefile for the project was semi-annoying but thinking about all of our dependencies allowed us to get a working version written.
*3/8/2017 (50 Minutes) - Kenzie and Drew worked in lab on dividing up the tasks for lab6. Kenzie will work on the files and implementation for the rook and queen pieces while Drew will work on the pawn and King pieces. Our goal is to be finished with implementing all six types of chess pieces by the end of this lab. 
*4/12/2017 (1 hour) - Met to discuss what else needed to be done, fixed some bugs in the pieces movement
*4/18/2017 (1 hour) - Met to discuss a plan of action, goal of having everything interacting by Sunday. Want to have 90% of the project done by this weekend. Tested to make sure the board graphics were working and will work on adding the rules for the game, as well a implementing our plan of action that we have written up for our minimax algorithm for the AI.
*4/18/2017 (2 hours) - Met to work on project, this included taking a zip-car to the South Bend train station to secure essential materials for the project and continued on to a local donut shop to continue discussing project and apply machine learning to their manufacturing process.
*4/23/17 (5 hours) - Met to work on project. This included fixing some of the errors with our AI, working on castling and promotion, and adding more to the graphics. We created the checkmate and stalemate screens and fixed numerous issues within our code.
*4/30/17 (3 hours) - Met to work on presentations for OOP week and work on our code. We created the Makefile dependencies and divided up who would present on what part of our project. We also continued to work on the AI and trying to make it more efficient. 
*5/02/17 (3 hours) - Met to continue working on the AI and the final report doc. Also started working on commenting the code as well as the individual reports.

This is in addition to the individual time logs included in our group report and in our four individual reports. 
