#ifndef PONG_BALL_H
#define PONG_BALL_H



typedef struct
{
	// Ball's position.
	int posX;
	int posY;

	// Ball's velocity.
	float velX;
	float velY;

	// Ball's initial velocity, reused when a player scores.
	float initVelX, initVelY;

} ball_t;



// Initialize the ball. Reset the ball's position to the center of the screen
// and resets its velocity.
void ball_init( ball_t* b, int initial_velX, int initial_velY );

// Resets the ball's position to the center of the screen, and resets its velocity.
void ball_reset( ball_t* b );

// Updates the ball's position according to its velocity.
void ball_step_pos( ball_t* b );



#endif // PONG_BALL_H
