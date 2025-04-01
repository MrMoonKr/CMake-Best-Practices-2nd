//#include <pcg_variants.h>
#include <pcg_random.hpp>
#include <random>
#include <time.h>
#include "display.h"
#include "game.h"

#define START   1
#define QUIT    2

int main( int argc, char* argv[] )
{
    // Init and seed RNG
    // pcg32_random_t rng;
    // pcg32_srandom_r(&rng, time(NULL) ^ (intptr_t)&printf, (intptr_t)&printTitle);
    pcg32 rng;
    std::uniform_int_distribution<int> dist( 0, 51 );

    // This must go near the start, else we cannot obtain LINES or COLS
    initCurses();
    
    int choice = 0;

    while( choice != QUIT )
    {
        refresh();
        printTitle();
        choice = menuLoop();
        switch( choice )
        {
            case START:
                {
                    refresh();
                    gameLoop(&rng);
                }
                break;
            case QUIT:
                {
                    // nothing to do
                }
                break;
            default:
                {
                    alert("That choice has not been implemented yet", 8, 30, TITLE_LINES + TITLE_INDENT, (COLS - 30) / 2);
                }
                break;
        }
    }

    endwin();
    return 0;
}