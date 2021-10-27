#ifndef PONG_PLAYER_H
#define PONG_PLAYER_H

// Player rectangles geometry.
#define PLAYER_WIDTH  5
#define PLAYER_HEIGHT 60
#define PLAYER_OFFSETX 20 // Player offset from the edge of the window.

typedef struct
{
	int posY;
	int score;

} player;

#endif // PONG_PLAYER_H
