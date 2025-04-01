#ifndef DISPLAY_H
#define DISPLAY_H

#define TITLE_LINES     9   // Lines of the splash art + description/authorship lines
#define TITLE_INDENT    5   // Buffer between the top of the window and splash art

#define X_MARGIN    2 // Column offset from the left within windows
#define Y_MARGIN    1 // Row offset from the top within windows

#include <curses.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// ASCII Art generated on https://www.patorjk.com/software/taag/
// Using the font DOOM by Frans P. de Vries <fpv@xymph.iaf.nl>  18 Jun 1996
static char const *Title[] = {
    "_____                       ___            _",
    "/  __ \\                     |_  |          | |",
    "| /  \\/_   _ _ __ ___  ___    | | __ _  ___| |",
    "  | |   | | | | '__/ __|/ _ \\   | |/ _` |/ __| |/ /",
    " | \\__/\\ |_| | |  \\__ \\  __/\\__/ / (_| | (__|   <",
    "   \\____/\\__,_|_|  |___/\\___\\____/ \\__,_|\\___|_|\\_\\",
    "",
    "Blackjack in the terminal",
    "Tachyon 2021"
};

//static char *License[]{};

// Use odd length choices so the menu looks nice and centered
static const char* MenuChoices[] = {
    "Start",
    "End",
};

static const char *GameMenuChoices[] = {
    "Deal",
    "Bet",
    "Exit",
};

static const char *InGameMenuChoices[] = {
    "Hit",
    "Double Down",
    "Stay",
    "Surrender",
    "End",
};

static const char *BetMenuChoices[] = {
    "Increase",
    "Decrease",
    "Confirm", 
};

void initCurses();

void gameBoard(int dealerLimit);

int gameMenuLoop();

int inGameMenuLoop();

int betMenu(int currentBet, int highlight);

void statsWindow(int money, int bet, int handValue, int dealerHandValue, const char *message);

void alert(const char *message, int height, int width, int startY, int startX);

void centerJustifyPrint(WINDOW *window, const char *string, int maxLineChars);

void printCard(char suit, int value, int cardCount, bool hideFirstCard, bool isDealer);

void printTitle();

void printMenu(WINDOW *menu, int numChoices, int highlight, const char *choices[]);

void printCenterMenu(WINDOW *menu, int numChoices, int highlight, int maxWidth, const char *choices[]);

void printBetMenu(WINDOW *menu, int numChoices, int bet, int highlight);

int menuLoop();

WINDOW *create_win(int height, int width, int starty, int startx);

void destroy_win(WINDOW *local_win);

WINDOW *create_card(int height, int width, int starty, int startx, char value, char suit);

#endif