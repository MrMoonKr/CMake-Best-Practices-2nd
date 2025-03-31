#pragma once

#include "rect.h"
#include "move.h"

typedef struct
{
    RECT rect;
    MOVE vel;
    char ch;
} BALL;

typedef struct
{
    RECT rect;
    char ch;
    int speed;
} BAT;

typedef struct
{
    int lives;
    int score;
} BTYPE;

typedef struct
{
    RECT rect;
    BTYPE *btype;
    int lives;
} BRICK;
