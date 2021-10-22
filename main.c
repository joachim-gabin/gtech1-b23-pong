#include <SDL2/SDL.h>

int main()
{
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "Init failed.\n" );
	}
}
