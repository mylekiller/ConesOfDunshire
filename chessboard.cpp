/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "game.h"
#include "piece.h"


//Macros for Different Pieces 
int const WHITEKING = 5;
int const WHITEQUEEN = 4;
int const WHITEBISHOP = 2;
int const WHITEKNIGHT = 1;
int const WHITEROOK = 3;
int const WHITEPAWN = 0;
int const BLACKKING = 11;
int const BLACKQUEEN = 10;
int const BLACKBISHOP = 8;
int const BLACKKNIGHT = 7;
int const BLACKROOK = 9;
int const BLACKPAWN = 6;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

SDL_Rect gChessPieces[ 12 ];

//Individual Pieces Sprite Sheet
LTexture gChessPiecesTexture;
//Chess Board to render pieces on 
LTexture gChessBoard;
//Selected Background 
LTexture gSelected;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

int main( int argc, char* args[] )
{
	game newGame;
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			bool selected = false;
			int xcord;
			int ycord;
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						if (x/100 == xcord && y/100 == ycord && selected) {
							selected = !selected;
						}
						else {
							xcord = x/100;
							ycord = y/100;
							selected = true;
						}
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render Background Image
				gChessBoard.render(gRenderer,0,0,NULL);

				if (selected) {
					gSelected.render(gRenderer,xcord*100, ycord*100, NULL);
				}

				//Render each piece in proper area
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						piece * p = newGame.getpiece(j, -1*(i-7));
						if (p != nullptr) {
							gChessPiecesTexture.render(gRenderer, j*100, i*100, &gChessPieces[ p -> getType()+(!p->getTeam()*6) ]);
						}
					}
				}
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Cones of Dunshire", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	if ( !gChessBoard.loadFromFile("Chessboard.bmp", gRenderer)) 
	{
		printf("Failed to load chessboard background!\n");
		success = false;
	}
	else {
		gChessBoard.scaleToScreen();
		//Load sprite sheet texture
		if( !gChessPiecesTexture.loadFromFile( "dots.png", gRenderer ) )
		{
			printf( "Failed to load pieces texture!\n" );
			success = false;
		}
		else
		{
			//Set white king
			gChessPieces[ WHITEKING ].x =   0;
			gChessPieces[ WHITEKING ].y =   0;
			gChessPieces[ WHITEKING ].w = 333;
			gChessPieces[ WHITEKING ].h = 333;

			//Set white queen
			gChessPieces[ WHITEQUEEN ].x = 333;
			gChessPieces[ WHITEQUEEN ].y = 	 0;
			gChessPieces[ WHITEQUEEN ].w = 333;
			gChessPieces[ WHITEQUEEN ].h = 333;
			
			//Set white bishop
			gChessPieces[ WHITEBISHOP ].x = 666;
			gChessPieces[ WHITEBISHOP ].y =   0;
			gChessPieces[ WHITEBISHOP ].w = 333;
			gChessPieces[ WHITEBISHOP ].h = 333;

			//Set white knight
			gChessPieces[ WHITEKNIGHT ].x = 999;
			gChessPieces[ WHITEKNIGHT ].y =   0;
			gChessPieces[ WHITEKNIGHT ].w = 333;
			gChessPieces[ WHITEKNIGHT ].h = 333;

			//Set white rook
			gChessPieces[ WHITEROOK ].x =1332;
			gChessPieces[ WHITEROOK ].y =   0;
			gChessPieces[ WHITEROOK ].w = 333;
			gChessPieces[ WHITEROOK ].h = 333;

			//Set white pawn
			gChessPieces[ WHITEPAWN ].x =1665;
			gChessPieces[ WHITEPAWN ].y =   0;
			gChessPieces[ WHITEPAWN ].w = 333;
			gChessPieces[ WHITEPAWN ].h = 333;

			//Set black king
			gChessPieces[ BLACKKING ].x =   0;
			gChessPieces[ BLACKKING ].y = 333;
			gChessPieces[ BLACKKING ].w = 333;
			gChessPieces[ BLACKKING ].h = 333;

			//Set black queen
			gChessPieces[ BLACKQUEEN ].x = 333;
			gChessPieces[ BLACKQUEEN ].y = 333;
			gChessPieces[ BLACKQUEEN ].w = 333;
			gChessPieces[ BLACKQUEEN ].h = 333;
			
			//Set black bishop
			gChessPieces[ BLACKBISHOP ].x = 666;
			gChessPieces[ BLACKBISHOP ].y = 333;
			gChessPieces[ BLACKBISHOP ].w = 333;
			gChessPieces[ BLACKBISHOP ].h = 333;

			//Set black knight
			gChessPieces[ BLACKKNIGHT ].x = 999;
			gChessPieces[ BLACKKNIGHT ].y = 333;
			gChessPieces[ BLACKKNIGHT ].w = 333;
			gChessPieces[ BLACKKNIGHT ].h = 333;

			//Set black rook
			gChessPieces[ BLACKROOK ].x =1332;
			gChessPieces[ BLACKROOK ].y = 333;
			gChessPieces[ BLACKROOK ].w = 333;
			gChessPieces[ BLACKROOK ].h = 333;

			//Set black pawn
			gChessPieces[ BLACKPAWN ].x =1665;
			gChessPieces[ BLACKPAWN ].y = 333;
			gChessPieces[ BLACKPAWN ].w = 333;
			gChessPieces[ BLACKPAWN ].h = 333;
		}
	}
	if ( !gSelected.loadFromFile("selected.png", gRenderer)) 
	{
		printf( "Failed to load selected background texture!\n" );
		success = false;
	}
	else {
		gSelected.setWidth(100);
		gSelected.setHeight(100);
	}
	return success;
}

void close()
{
	//Free loaded images
	gChessPiecesTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}