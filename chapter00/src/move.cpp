#include "move.h"

void move_rect( RECT* rect, MOVE* vel )
{
    rect_move_x( rect, vel->x );
    rect_move_y( rect, vel->y );
}

void move_next( RECT* in, MOVE* vel, RECT* out )
{
    out->top = in->top;
    out->left = in->left;
    out->width = in->width; 
    out->height = in->height;
    out->right = in->right;
    out->bottom = in->bottom;

    move_rect( out, vel );
}

