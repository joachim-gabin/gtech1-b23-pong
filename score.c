#include "score.h"

#include <SDL2/SDL.h>

static char* zero  = "xxxx xx xx xxxx";
static char* one   = "  x  x  x  x  x";
static char* two   = "xxx  xxxxx  xxx";
static char* three = "xxx  xxxx  xxxx";
static char* four  = "x xx xxxx  x  x";
static char* five  = "xxxx  xxx  xxxx";
static char* six   = "xxxx  xxxx xxxx";
static char* seven = "xxx  x  x  x  x";
static char* eight = "xxxx xxxxx xxxx";
static char* nine  = "xxxx xxxx  xxxx";

static char** digits[] = { &zero, &one, &two, &three, &four, &five, &six, &seven, &eight, &nine };

static void draw_digit( SDL_Renderer* r, int digit, int posX, int posY )
{
	SDL_Rect rect = { 0, 0, 10, 10 };
	SDL_SetRenderDrawColor( r, 46, 107, 219, 255 );

	digit = digit % 10;

	for ( int y = 0; y < 5; ++y )
	{
		for ( int x = 0; x < 3; ++x )
		{
			if ( (*(digits[digit]))[y * 3 + x] == 'x' )
			{
				rect.x = posX + x * 10;
				rect.y = posY + y * 10;
				SDL_RenderFillRect( r, &rect );
			}
		}
	}
}

void draw_number( SDL_Renderer* r, int number, int posX, int posY )
{
	// Cannot display more than two digits.
	if ( number >= 100 )
		return;

	// Two digits.
	if ( number >= 10 )
	{
		draw_digit( r, number % 10, posX + 40, posY );
		draw_digit( r, number / 10, posX, posY );
	}

	// One digit.
	else
	{
		draw_digit( r, number, posX, posY );
	}
}
