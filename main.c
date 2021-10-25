#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "pong.h"

SDL_Window* window = 0;

int main()
{
	// Initialize SDL.
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL init failed.\n" );
		return 1;
	}

	// Create the SDL window.
	window = SDL_CreateWindow(
		"PONG!",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN );

	if ( !window )
	{
		printf( "SDL window creation failed.\n" );
		return 2;
	}

	// Wait 3 seconds then exit the game.
	int quit = 0;
	SDL_Event e;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Create renderer for window
	gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );


	while (!quit){

		while (SDL_PollEvent(&e) != 0) {

			if (e.type == SDL_QUIT) {
				quit = 1;

			}
			else if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_ESCAPE:
						quit = 1;
						break;
				}
			}

			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear( gRenderer );


			SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF );
			SDL_RenderFillRect( gRenderer, &fillRect);

			SDL_RenderPresent( gRenderer );
		}
	}
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}
