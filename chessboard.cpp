/* Main for the Cones of Dunshire chess game, includes all graphics rendering and interacts with 
all of the chess classes to make a game */

//Using SDL, SDL_image, standard math, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "game.h"
#include "piece.h"


//Constants for Different Pieces 
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

//The windows for the main chess game
SDL_Window* gWindow = NULL;
//The window for the splash menu
SDL_Window* splashWindow = NULL;
//The main window renderer
SDL_Renderer* gRenderer = NULL;
//Renderer for the splash menu
SDL_Renderer* splashRenderer = NULL;

SDL_Rect gChessPieces[ 12 ];

//Individual Pieces Sprite Sheet
LTexture gChessPiecesTexture;
//Chess Board to render pieces on 
LTexture gChessBoard;
//Selected Background 
LTexture gSelected;
//Splash Screen 
LTexture gSplash;
//Overlay for Splash Buttons
LTexture gOverlay;
//Texture to Display when a king is in check
LTexture gCheck;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Frees and Closes Splash Screen
void closeSplash();

int main( int argc, char* args[] )
{
	// Create a new game object to interact with
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

			bool chooseMode = false;
			bool onePlayer = false;
			bool twoPlayer = false;
			bool playerColor = true;
			int players = 0;
			while (!chooseMode && !quit) {
				while (SDL_PollEvent( &e ) != 0) {
					if (e.type == SDL_QUIT) {
						quit = true;
					}
					if (e.type == SDL_WINDOWEVENT) {
						if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
							quit = true;
						}
					}
					if (e.type == SDL_MOUSEMOTION) {
						int x,y;
						SDL_GetMouseState(&x,&y);
						if (x >365 && x <1035) {
							if (y > 103 && y < 241) {
								onePlayer = true;
							}
							else if (y > 396 && y < 534) {
								twoPlayer = true;
							}
							else {
								onePlayer = false;
								twoPlayer = false;
							}
						}
						else {
							onePlayer = false;
							twoPlayer = false;
						}
					}
					if (e.type == SDL_MOUSEBUTTONDOWN) {
						if(onePlayer) {
							players = 1;
							chooseMode = true;
						}
						else if (twoPlayer) {
							players = 2;
							chooseMode = true;
						}
					}
				}
				SDL_SetRenderDrawColor( splashRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( splashRenderer );
				gSplash.render(splashRenderer,0,0,NULL);
				if (onePlayer) {
					gOverlay.render(splashRenderer,365,103,NULL);
				}
				if (twoPlayer) {
					gOverlay.render(splashRenderer,365,396,NULL);
				}
				SDL_RenderPresent(splashRenderer);
			}

			closeSplash();
			bool selected = false;
			bool moved = false;
			int xcord; //The Constantly updated Cords based on clicks 
			int ycord;
			int xcordi;//The initial cords of a successful move
			int ycordi;
			int xcordf;//The final cords of a successful move
			int ycordf;
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
					if (e.type == SDL_WINDOWEVENT) {
						if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
							quit = true;
						}
					}
					if (e.type == SDL_MOUSEBUTTONDOWN) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						if (selected) {
							if (x/100 == xcord && y/100 == ycord) {
								selected = !selected;
							}
							else {
								bool outcome;
								outcome = newGame.trymove(xcord, -1*(ycord-7), x/100, -1*((y/100)-7));
								selected = !selected;
								if (outcome) {
									xcordi = xcord;
									ycordi = ycord;
									xcordf = x/100;
									ycordf = y/100;
									moved = true;
								}
							}
						}
						else {
							piece * p = newGame.getpiece(x/100, -1*((y/100)-7));
							if (p != nullptr && p -> getTeam() == newGame.getTurn()) {
								selected = true;
								xcord = x/100;
								ycord = y/100;
							}
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

				if(moved) {
					gSelected.render(gRenderer,xcordi*100, ycordi*100, NULL);
					gSelected.render(gRenderer,xcordf*100, ycordf*100, NULL);
				}

				//Render each piece in proper area
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						piece * p = newGame.getpiece(j, -1*(i-7));
						if (p != nullptr) {
							if (p -> getType() == KING && newGame.inCheck(p -> getTeam())) {
								gCheck.render(gRenderer, j*100, i*100, NULL);
								if (selected && p -> getType() == KING) {
									gSelected.render(gRenderer, xcord*100, ycord*100, NULL);
								}
							}
							gChessPiecesTexture.render(gRenderer, j*100, i*100, &gChessPieces[ p -> getType()+(!p->getTeam()*6) ]);
						}
					}
				}
				SDL_RenderPresent( gRenderer );
				if (players == 1 && (newGame.getTurn() != playerColor)) {
					std::pair<std::pair<int,int>, std::pair<int,int>> tofrom = newGame.getAIMove();
					newGame.trymove(tofrom.first.first, tofrom.first.second, tofrom.second.first, tofrom.second.second);
					xcordi = tofrom.first.first;
					ycordi = -1*(tofrom.first.second-7);
					xcordf = tofrom.second.first;
					ycordf = -1*(tofrom.second.second-7);
					moved = true;
				}
				SDL_Delay(100);
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
		splashWindow = SDL_CreateWindow("Cones of Dunshire", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SPLASH_WIDTH, SPLASH_HEIGHT, SDL_WINDOW_SHOWN);
		gWindow = SDL_CreateWindow( "Cones of Dunshire", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_HIDDEN);
		if( gWindow == NULL || splashWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			splashRenderer = SDL_CreateRenderer(splashWindow, -1, SDL_RENDERER_ACCELERATED);
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL || splashRenderer == NULL)
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_SetRenderDrawColor( splashRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
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

	if ( !gChessBoard.loadFromFile("images/Chessboard.bmp", gRenderer)) 
	{
		printf("Failed to load chessboard background!\n");
		success = false;
	}
	else {
		gChessBoard.scaleToScreen();
		//Load sprite sheet texture
		if( !gChessPiecesTexture.loadFromFile( "images/pieces.png", gRenderer ) )
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
	if ( !gSelected.loadFromFile("images/selected.png", gRenderer)) 
	{
		printf( "Failed to load selected background texture!\n" );
		success = false;
	}
	else {
		gSelected.setWidth(100);
		gSelected.setHeight(100);
		gSelected.setBlendMode(SDL_BLENDMODE_BLEND);
		gSelected.setAlpha(180);
	}
	if (!gSplash.loadFromFile("images/splash.png", splashRenderer)) {
		printf("Failed to load splash screen!\n");
		success = false;
	}
	else {
		gSplash.setWidth(SPLASH_WIDTH);
		gSplash.setHeight(SPLASH_HEIGHT);
	}
	if (!gOverlay.loadFromFile("images/overlay.png", splashRenderer)) {
		printf("Failed to load splash buttons overlay!\n");
		success = false;
	}
	else {
		gOverlay.setWidth(670);
		gOverlay.setHeight(138);
		gOverlay.setBlendMode( SDL_BLENDMODE_BLEND );
		gOverlay.setAlpha(60);
	}
	if (!gCheck.loadFromFile("images/check.png", gRenderer)) {
		printf("Failed to load king check background!\n");
		success = false;
	}
	else {
		gCheck.setWidth(100);
		gCheck.setHeight(100);
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
	SDL_DestroyWindow(splashWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void closeSplash() {
	//Show the main chess window
	SDL_ShowWindow(gWindow);
	SDL_RaiseWindow(gWindow);
	//Free Splash Image
	gSplash.free();

	//Destroy Old Window
	SDL_DestroyRenderer(splashRenderer);
	SDL_HideWindow(splashWindow);
	splashRenderer = NULL;
	splashWindow = NULL;
}