#include "ball.h"

#include "pong.h"

void ball_init( ball_t* b, int init_vel )
{
	b->posX = SCREEN_WIDTH  / 2;
	b->posY = SCREEN_HEIGHT / 2;

	b->velX = init_vel;
	b->velY = init_vel;
}

void ball_step_pos( ball_t* b )
{
	b->posX += b->velX;
	b->posY += b->velY;

	if ( (b->posY <= 0 && b->velY < 0) || (b->posY >= SCREEN_HEIGHT && b->velY > 0) )
		b->velY = -b->velY;

	if ( (b->posX >= SCREEN_WIDTH && b->velX > 0) || (b->posX <= 0 && b->velX < 0) )
		b->velX = -b->velX;
}
