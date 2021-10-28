#ifndef PONG_SCORE_H
#define PONG_SCORE_H

struct SDL_Renderer;

/// Draws a number onto the screen. The number can have a maximum of two digits.
void draw_number( struct SDL_Renderer* r, int number, int posX, int posY );

#endif // PONG_SCORE_H
