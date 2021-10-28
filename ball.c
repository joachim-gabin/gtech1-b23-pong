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

void ball_step_pos( ball_t* b, player_t* p1, player_t* p2 )
{
	b->posX += b->velX;
	b->posY += b->velY;

	float acc = 1.5F;

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
		// We can determine who scored based on the ball's velocity.
		if ( b->velX > 0 ) p1->score++;
		else               p2->score++;

		ball_reset( b );
	}

	// Player collision.
	// Going towards player 2.
	if ( b->velX > 0 )
	{
		// Player AABB.
		int x0 = SCREEN_WIDTH - PLAYER_OFFSETX - PLAYER_WIDTH;
		int x1 = x0 + PLAYER_WIDTH;

		if ( b->posY + 10 >= p2->posY && b->posY <= p2->posY + PLAYER_HEIGHT ) {
			if ( b->posX + 10 >= x0 && b->posX <= x1 ) {
				b->velX = -b->velX;
				b->velX += (b->velX > 0 && fabs(b->velX) < 20) ? acc : -acc;

				float y = (float) b->posY - (float) p2->posY - (float) PLAYER_HEIGHT / 2;
				b->velY = y / (PLAYER_HEIGHT * 0.1F);
			}
		}
	}

	// Going towards player 1.
	else
	{
		// Player AABB.
		int x0 = PLAYER_OFFSETX;
		int x1 = x0 + PLAYER_WIDTH;

		if ( b->posY + 10 >= p1->posY && b->posY <= p1->posY + PLAYER_HEIGHT ) {
			if ( b->posX + 10 >= x0 && b->posX <= x1 ) {
				b->velX = -b->velX;
				b->velX += (b->velX > 0 && fabs(b->velX) < 20) ? acc : -acc;

				float y = (float) b->posY - (float) p1->posY - (float) PLAYER_HEIGHT / 2;
				b->velY = y / (PLAYER_HEIGHT * 0.1F);
			}
		}
	}
}
