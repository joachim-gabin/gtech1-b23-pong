#include "ball.h"

#include "pong.h"

#include <math.h>

void ball_init( ball_t* b, int velx, int vely )
{
	b->initVelX = velx;
	b->initVelY = vely;

	ball_reset( b );
}

void ball_reset( ball_t* b )
{
	b->posX = SCREEN_WIDTH  / 2;
	b->posY = SCREEN_HEIGHT / 2;

	b->velX = b->initVelX;
	b->velY = b->initVelY;
}

void ball_step_pos( ball_t* b )
{
	b->posX += b->velX;
	b->posY += b->velY;

	float acc = 0.2F;

	// Playground collision test.
	// Vertical.
	if ( (b->posY <= 0 && b->velY < 0) || (b->posY >= SCREEN_HEIGHT && b->velY > 0) )
	{
		b->velY  = -b->velY;
		b->velY += (b->velY > 0 && fabs(b->velY) < 10) ? acc : -acc;
	}

	// Horizontal.
	if ( (b->posX >= SCREEN_WIDTH && b->velX > 0) || (b->posX <= 0 && b->velX < 0) )
	{
		ball_reset( b );
	}
}
