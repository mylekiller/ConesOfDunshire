#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <stdio.h>

#ifndef LTEXTURE_H
#define LTEXTURE_H

const int SPLASH_WIDTH = 1400;
const int SPLASH_HEIGHT = 700;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path, SDL_Renderer* gRenderer );

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, int w = 100, int h = 100);

		//Set Blend Mode
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha Modulation
		void setAlpha(Uint8 alpha);

		//Gets and sets image dimensions
		int getWidth();
		int getHeight();
		void setWidth(int);
		void setHeight(int);
		void scaleToScreen();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif