#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "pong.h"
#include "ball.h"
#include "player.h"
#include "score.h"



SDL_Window* window = 0;
SDL_Renderer* renderer = 0;

player_t player1;
player_t player2;
ball_t   ball;

int  init( void );
void update( void );
void render( void );
void quit( void );

// Drawing functions.
void draw_net( void );
void draw_rackets( void );



int main()
{
	int initCode = init();
	if ( initCode )
		return initCode;

	bool closeRequest = false;
	SDL_Event e;

	Uint32 frameStart, frameTime, frameDelay = 20;
	while ( !closeRequest )
	{
		frameStart = SDL_GetTicks();

		// Poll window events.
		while ( SDL_PollEvent(&e) != 0 )
		{
			if ( e.type == SDL_QUIT ) {
				closeRequest = true;
			}
			else if ( e.type == SDL_KEYDOWN ) {
				switch ( e.key.keysym.sym ) {
				case SDLK_ESCAPE:
					closeRequest = true;
					break;
				}
			}
		}

		update();
		render();

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

	int centerY = (SCREEN_HEIGHT - PLAYER_HEIGHT) / 2;
	player1.posY = centerY;
	player2.posY = centerY;
	player1.score = 0;
	player2.score = 0;

	ball_init( &ball, 3, 3 );

	return 0;
}

void update( void )
{
	const Uint8* keystates = SDL_GetKeyboardState( 0 );

	// Player input.
	if ( keystates[SDL_SCANCODE_W] ) {
		player1.posY -= 10;
		if ( player1.posY <= 0 )
			player1.posY = 0;
	}
	if ( keystates[SDL_SCANCODE_S] ) {
		player1.posY += 10;
		if ( player1.posY >= SCREEN_HEIGHT - 60 )
			player1.posY = SCREEN_HEIGHT - 60;
	}
	if ( keystates[SDL_SCANCODE_UP] ) {
		player2.posY -= 10;
		if ( player2.posY <= 0 )
			player2.posY = 0;
	}
	if ( keystates[SDL_SCANCODE_DOWN] ) {
		player2.posY += 10;
		if ( player2.posY >= SCREEN_HEIGHT - 60 )
			player2.posY = SCREEN_HEIGHT - 60;
	}

	// Ball movement.
	ball_step_pos( &ball, &player1, &player2 );
}

void render( void )
{
	SDL_SetRenderDrawColor( renderer, 143, 151, 166, 255 );
	SDL_RenderClear( renderer );

	// Player scores.
	draw_number( renderer, player1.score, 150, 50 );
	draw_number( renderer, player2.score, SCREEN_WIDTH - 150, 50 );

	draw_net();
	draw_rackets();

	SDL_Rect fillRect = { ball.posX, ball.posY, 10, 10 };
	SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
	SDL_RenderFillRect( renderer, &fillRect );

	SDL_RenderPresent( renderer );
}

void quit( void )
{
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );

	SDL_Quit();
}

// Draws the net at the center of the window.
void draw_net( void )
{
	SDL_Rect fillRect = { SCREEN_WIDTH / 2 - 5, 0, 10, SCREEN_HEIGHT };
	SDL_SetRenderDrawColor( renderer, 46, 107, 219, 255 );
	SDL_RenderFillRect( renderer, &fillRect );
}

// Draws both the player's rackets.
void draw_rackets( void )
{
	SDL_Rect p1 = { PLAYER_OFFSETX, player1.posY, PLAYER_WIDTH, PLAYER_HEIGHT };
        SDL_SetRenderDrawColor( renderer, 46, 107, 219, 255 );
        SDL_RenderFillRect( renderer, &p1 );

	SDL_Rect p2 = { SCREEN_WIDTH - PLAYER_OFFSETX - PLAYER_WIDTH, player2.posY, PLAYER_WIDTH, PLAYER_HEIGHT };
        SDL_SetRenderDrawColor( renderer, 46, 107, 219, 255 );
        SDL_RenderFillRect( renderer, &p2 );
}
