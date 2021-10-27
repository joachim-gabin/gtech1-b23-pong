#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "pong.h"
#include "ball.h"



SDL_Window* window = 0;
SDL_Renderer* renderer = 0;

int  init( void );
void quit( void );



int main()
{
	int initCode = init();
	if ( initCode )
		return initCode;

	// Wait 3 seconds then exit the game.
	bool closeRequest = false;
	SDL_Event e;

	ball_t ball;
	ball_init( &ball, 5 );

	Uint32 frameStart, frameTime, frameDelay = 10;

	while (!closeRequest){

		while (SDL_PollEvent(&e) != 0) {

			if (e.type == SDL_QUIT) {
				closeRequest = true;

			}
			else if (e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
					case SDLK_ESCAPE:
						closeRequest = true;
						break;
				}
			}
		}

		frameStart = SDL_GetTicks();

		ball_step_pos( &ball );

		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear( renderer );


		SDL_Rect fillRect = { ball.posX, ball.posY, 10, 10 };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF );
		SDL_RenderFillRect( renderer, &fillRect);

		SDL_RenderPresent( renderer );

		frameTime = SDL_GetTicks() - frameStart;
		if ( frameTime < frameDelay )
		{
			SDL_Delay( frameDelay - frameTime );
		}
	}

	quit();

	return 0;
}



int init( void )
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

	// Create renderer for window.
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

	return 0;
}

void quit( void )
{
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );

	SDL_Quit();
}
