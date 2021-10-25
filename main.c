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

	while (!quit){
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = 1;
			}
		}
	}
	SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}
