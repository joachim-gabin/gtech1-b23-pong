#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

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
	window = SDL_CreateWindow( "PONG!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
	if ( !window )
	{
		printf( "SDL window creation failed.\n" );
		return 2;
	}

	// Wait 3 seconds then exit the game.
	for ( int i = 1; i <= 3; ++i )
	{
		SDL_Delay( 1000 );
		printf( "%i\n", i );
	}

	SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}
