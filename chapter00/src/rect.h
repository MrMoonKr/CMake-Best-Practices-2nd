#pragma once

typedef struct tagRECT
{
    int top;
    int bottom;
    int left;
    int right;
    int width;
    int height;

    tagRECT()
    {
        //
    }

} RECT;

void rect_set_top( RECT* rect, int top );
void rect_set_bottom( RECT* rect, int bottom );
void rect_set_left( RECT* rect, int left );
void rect_set_right( RECT* rect, int right );
void rect_set_width( RECT* rect, int width );
void rect_set_height( RECT* rect, int height );

void rect_move_x( RECT* rect, int x );
void rect_move_y( RECT* rect, int y );

void rect_init( RECT* rect, int top, int left, int width, int height );
