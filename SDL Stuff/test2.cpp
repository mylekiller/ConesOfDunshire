/* SDL Testing for Kyle Miller */

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;

//Starts up SDL and creates window
bool init();

//Loads media
SDL_Surface* loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

SDL_Surface* loadMedia()
{
	//Loading success flag
	SDL_Surface* optimizedSurface = NULL;

	//Load chessboard image
	SDL_Surface* gChessBoard = SDL_LoadBMP( "Chessboard.bmp" );
	if( gChessBoard == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "Chessboard.bmp", SDL_GetError() );
	}
	else {
		optimizedSurface = SDL_ConvertSurface( gChessBoard, gScreenSurface->format, 0 );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image Chessboard.bmp! SDL Error: %s\n", SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( gChessBoard );
	}

	return optimizedSurface;
}


void close(SDL_Surface* gChessBoard)
{
	//Deallocate surface
	SDL_FreeSurface( gChessBoard );
	gChessBoard = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	SDL_Surface* gChessBoard = NULL;
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		gChessBoard = loadMedia();
		if( gChessBoard == NULL)
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			//Apply the image while the user does not click exit
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
				}

				//Apply the image
				SDL_BlitScaled( gChessBoard, NULL, gScreenSurface, &stretchRect );
			
				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}

	//Free resources and close SDL
	close(gChessBoard);

	return 0;
}