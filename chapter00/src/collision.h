#pragma once

#include "rect.h"
#include "move.h"

typedef enum tagCOLLISION
{
    NONE,
    TOP,
    BOTTOM,
    LEFT,
    RIGHT

} COLLISION;

bool col_test( const RECT* r1, const RECT* r2 );
COLLISION col_mov_test( const RECT* stat, const RECT* rect, const MOVE* vel );

