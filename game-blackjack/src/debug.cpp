#include "debug.h"

#include <random>


void printCards( Card *deckPtr)
{
    refresh();
    WINDOW *debugCards;
    int startx = 0;
    int starty = 0;

    debugCards = create_win(LINES, COLS, 0, 0);
    keypad(debugCards, TRUE);

    for(int i = 0; i < 52; i++){
        if(i < 26){
            startx = 1;
            starty = i;
        }
        else{
            startx = 5;
            starty = i - 26;
        }

        mvwprintw(debugCards, starty, startx, "%d", (deckPtr+i)->value);
        mvwprintw(debugCards, starty, startx + 2, "%c", (deckPtr+i)->suit);
        wrefresh(debugCards);
    }

    if(wgetch(debugCards)){
        destroy_win(debugCards);
    }
}

void debugCards(pcg32 *randSeed)
{
    Card deck[52];
    Card *ptr = 0;
    ptr = deck;

    initDeck(ptr);
    printCards(ptr);

    refresh();
}

void debugShuffle(pcg32 *randSeed)
{
    Card deck[52];
    Card *ptr = 0;
    ptr = deck;

    initDeck(ptr);
    //washShuffle(ptr, randSeed);
    //riffleShuffle(ptr);
    //for(int i = 0; i < 5; i++)
    //boxShuffle(ptr, randSeed);
    //cutShuffle(ptr);
    vegasShuffle(ptr, randSeed);
    printCards(ptr);

    refresh();
}

void printDebugMenu(WINDOW *menu, int numChoices, int highlight)
{
    int xMargin = 0 ;
    int yMargin = 1;

    for(int i = 0; i < numChoices; i++){

        if(highlight == i + 1){
            wattron(menu, A_REVERSE);
            mvwprintw(menu, yMargin, xMargin, "%s", DebugChoices[i]);
            wattroff(menu, A_REVERSE);
        }
        else
            mvwprintw(menu, yMargin, xMargin, "%s", DebugChoices[i]);
        
        ++yMargin;
    }

    wrefresh(menu);
}

int debugLoop()
{
    WINDOW *menu;
    int numChoices = sizeof(DebugChoices)/sizeof(DebugChoices[0]);
    int starty = TITLE_LINES + TITLE_INDENT;
    int startx = (COLS - 12) / 2;

    int highlight = 1;
    int choice = 0;
    int c = 0;

    menu = create_win(7, 12, starty, startx);
    keypad(menu, TRUE);
    printDebugMenu(menu, numChoices, highlight);

    while(1)
    {
        c = wgetch(menu);
        switch(c)
        {
            case KEY_UP:
                if(highlight == 1)
                    highlight = numChoices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == numChoices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:    //On LF/Enter/Return
                choice = highlight;
                break;
        }
        printDebugMenu(menu, numChoices, highlight);
        if(choice != 0)
            break;
    }

    return choice;
}
