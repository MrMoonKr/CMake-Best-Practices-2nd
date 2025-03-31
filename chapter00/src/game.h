#pragma once

//#include <ncurses/ncurses.h>
#include <curses.h>

#include "rect.h"
#include "move.h"
#include "clock.h"
#include "object.h"
#include "konami.h"

typedef struct tagGAME
{
    WINDOW *win;
    RECT rect;

    CLOCK clock;

    BALL *ball;
    BAT *bat;

    int nchlives;
    char *chlives; // Live characters

    int nbtypes;
    BTYPE *btypes; // Brick types

    int nbricks;
    int rbricks; // Remaining bricks
    BRICK *bricks;

    const char *title;

    bool debug;
    bool end;
    bool won;
    bool over;
    int score;

    KONAMI *konami;

} GAME;


void game_setup( GAME* game );
void game_run( GAME* game );
void game_repaint( GAME* game );
void game_refresh( GAME* game );

