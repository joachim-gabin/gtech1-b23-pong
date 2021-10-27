

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "pong.h"
#include "ball.h"
#include "player.h"


SDL_Window* window = 0;
SDL_Renderer* renderer = 0;

int  init( void );
void quit( void );
player player1;
player player2;


int main()
{
	player1.posY = 0;
	player2.posY = 0;

	int initCode = init();
	if ( initCode )
		return initCode;

	// Wait 3 seconds then exit the game.
	bool closeRequest = false;
	SDL_Event e;

	ball_t ball;
	ball_init( &ball, 3, 3 );

	Uint32 frameStart, frameTime, frameDelay = 20;

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
		const Uint8*keystates = SDL_GetKeyboardState(0);

		if(keystates[SDL_SCANCODE_W]){
			player1.posY -= 7;
			if(player1.posY <= 0)
				player1.posY = 0;
		}

                if(keystates[SDL_SCANCODE_S]){
                        player1.posY += 7;
			if (player1.posY >= SCREEN_HEIGHT - 60)
				player1.posY = SCREEN_HEIGHT - 60;
		}

                if(keystates[SDL_SCANCODE_UP]){
                        player2.posY -= 7;
			if (player2.posY <= 0)
				player2.posY = 0;
		}

                if(keystates[SDL_SCANCODE_DOWN]){
                        player2.posY += 7;
			if (player2.posY >= SCREEN_HEIGHT - 60)
				player2.posY = SCREEN_HEIGHT - 60;
		}



		frameStart = SDL_GetTicks();

		ball_step_pos( &ball, &player1, &player2 );

		SDL_SetRenderDrawColor( renderer, 143, 151, 166, 255);
		SDL_RenderClear( renderer );

		filet();
		raquette();

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


void filet() {


	SDL_Rect fillRect = {SCREEN_WIDTH/2-5,0,10,SCREEN_HEIGHT};
	SDL_SetRenderDrawColor(renderer, 46, 107, 219, 255 );
	SDL_RenderFillRect( renderer, &fillRect);
}

int raquette() {


	SDL_Rect fillRaquette1 = {PLAYER_OFFSETX, player1.posY, PLAYER_WIDTH, PLAYER_HEIGHT};
        SDL_SetRenderDrawColor(renderer, 46, 107, 219, 255 );
        SDL_RenderFillRect( renderer, &fillRaquette1);


	SDL_Rect fillRaquette2 = {SCREEN_WIDTH - PLAYER_OFFSETX - PLAYER_WIDTH, player2.posY, PLAYER_WIDTH, PLAYER_HEIGHT};
        SDL_SetRenderDrawColor(renderer, 46, 107, 219, 255 );
        SDL_RenderFillRect( renderer, &fillRaquette2);
}
