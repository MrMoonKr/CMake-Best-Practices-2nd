#pragma once

#include "rect.h"

typedef struct tagMOVE
{
    int x;
    int y;

    tagMOVE()
    {
        //
    }

} MOVE;

void move_rect( RECT* rect, MOVE* vel );
void move_next( RECT* in, MOVE* vel, RECT* out );
