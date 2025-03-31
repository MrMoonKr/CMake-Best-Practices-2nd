#include <iostream>
//#include <ncurses/ncurses.h> // pacman -S mingw-w64-ucrt-x86_64-ncurses 설치 필요
#include <curses.h>

#include "game.h"

/**
 * @brief Check if the screen size is sufficient for the game.
 * @return true if the screen size is sufficient, false otherwise.
 */
static inline bool game_check_screen()
{
    return LINES >= 20 && COLS >= 80 ;
}

/**
 * @brief Initialize the game settings. mostly ncurses settings.
 */
static inline void game_init()
{
    curs_set( 0 );              // 커서 숨기기
    keypad( stdscr, true );     // 특수키 입력 가능하게 하기
    cbreak();                   // 키 입력 버퍼 없애기
    noecho();                   // 키 입력 시 입력값 화면에 출력 안하기
    nodelay( stdscr, true );    // 입력 없을 시 대기 없이 바로 리턴
}


#define NCHLIVES 4
#define NBTYPES 4
#define NBRICKS 16

static inline void game_loop()
{
    RECT rect;
    CLOCK clock;

    RECT ball_rect;
    MOVE ball_vel;
    BALL ball;

    ball.rect = ball_rect;
    ball.vel = ball_vel;

    RECT bat_rect;
    BAT bat;

    bat.rect = bat_rect;

    char chlives[4];

    chlives[0] = '=';
    chlives[1] = '$';
    chlives[2] = '&';
    chlives[3] = '|';

    BTYPE btypes[NBTYPES];

    btypes[0].lives = 1;
    btypes[0].score = 2;

    btypes[1].lives = 2;
    btypes[1].score = 4;

    btypes[2].lives = 3;
    btypes[2].score = 8;

    btypes[3].lives = 4;
    btypes[3].score = 16;

    BRICK bricks[NBRICKS];

    int konami_keys[10];

    konami_keys[0] = KEY_UP;
    konami_keys[1] = KEY_UP;
    konami_keys[2] = KEY_DOWN;
    konami_keys[3] = KEY_DOWN;
    konami_keys[4] = KEY_LEFT;
    konami_keys[5] = KEY_RIGHT;
    konami_keys[6] = KEY_LEFT;
    konami_keys[7] = KEY_RIGHT;
    konami_keys[8] = 'B';
    konami_keys[9] = 'A';

    KONAMI konami;

    konami.nkeys = 10;
    konami.keys = konami_keys;

    GAME game;

    game.win = stdscr;
    game.rect = rect;
    game.clock = clock;
    game.ball = &ball;
    game.bat = &bat;

    game.nchlives = NCHLIVES;
    game.chlives = chlives;

    game.nbtypes = NBTYPES;
    game.btypes = btypes;

    game.nbricks = NBRICKS;
    game.rbricks = NBRICKS;
    game.bricks = bricks;

    game.title = "Ncurses C Breakout";

#ifdef DEBUG
    game.debug = true;
#else
    game.debug = false;
#endif

    game.konami = &konami;

    game_setup(&game);
    game_run(&game);
}

int main( int argc, char* argv[] )
{
    initscr();  // ncurses 초기화

    if( !game_check_screen() )
    {
        endwin();
        std::cerr << "[에러] Screen size is too small." << std::endl;
        return -1;
    }

    game_init();     // 게임임 설정 초기화
    game_loop();      // 게임 실행

    endwin();   // ncurses 종료

    return 0;
}