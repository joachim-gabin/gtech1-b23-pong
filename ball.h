#ifndef PONG_BALL_H
#define PONG_BALL_H

typedef struct
{
	int posX;
	int posY;

	int velX;
	int velY;

} ball_t;

// Initialize the ball. Reset the ball's position to the center of the screen
// and resets its velocity.
void ball_init( ball_t* b, int initial_velocity );

// Updates the ball's position according to its velocity.
void ball_step_pos( ball_t* b );

#endif // PONG_BALL_H
