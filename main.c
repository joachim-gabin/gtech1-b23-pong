#include <SDL2/SDL.h>

SDL_Window* window = 0;

int main()
{
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL init failed.\n" );
		return 1;
	}

	window = SDL_CreateWindow( "PONG!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN );
	if ( !window )
	{
		printf( "SDL window creation failed.\n" );
		return 2;
	}

	SDL_Delay( 3000 );
	return 0;
}
