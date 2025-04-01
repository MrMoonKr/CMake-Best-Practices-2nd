#include "display.h"

#define PLAYER_CARD_HAND 11
#define DEALER_CARD_HAND 3
#define CARD_HEIGHT 5
#define CARD_WIDTH  7
#define CARD_OFFSET 3


/**
 * @brief Initializes the ncurses library and sets up the terminal for use.
 */
void initCurses()
{
    initscr();

    curs_set( FALSE );
    cbreak();
    noecho();
    keypad( stdscr, TRUE );
    mousemask( ALL_MOUSE_EVENTS, NULL );

    return;
}

void gameBoard(int dealerLimit)
{
    WINDOW *topHalf;
    WINDOW *botHalf;

    int width = COLS - (COLS/4);
    int height = LINES/2;

    int startx = 0;

    topHalf = create_win(height, width, 0, 0);
    botHalf = create_win(height, width, LINES/2, 0);

    mvwprintw(topHalf, 1, (width/2) - 3, "Dealer");
    mvwprintw(topHalf, 2, (width/2) - 19, "Must draw to %d and stand on all %d's", dealerLimit, dealerLimit+1);

    mvwprintw(botHalf, 1, (width/2) - 5, "Your Hand");

    wrefresh(topHalf);
    wrefresh(botHalf);

    delwin(topHalf);
    delwin(botHalf);
}

int gameMenuLoop()
{
    WINDOW *gameMenu;

    int numChoices = sizeof(GameMenuChoices)/sizeof(GameMenuChoices[0]);
    int highlight = 1;
    int choice = 0;
    int c = 0;

    int width = COLS/4;
    int height = LINES/2;

    int startx = COLS - (COLS/4);

    gameMenu = create_win(height, width, LINES/2, startx);
    keypad(gameMenu, TRUE);

    printMenu(gameMenu, numChoices, highlight, GameMenuChoices);

    while(1)
    {
        c = wgetch(gameMenu);
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
        printMenu(gameMenu, numChoices, highlight, GameMenuChoices);
        if(choice != 0)
            break;
    }

    return choice;
}

int inGameMenuLoop()
{
    WINDOW *inGameMenu;

    int numChoices = sizeof(InGameMenuChoices)/sizeof(InGameMenuChoices[0]);
    int highlight = 1;
    int choice = 0;
    int c = 0;

    int width = COLS/4;
    int height = LINES/2;

    int startx = COLS - (COLS/4);

    inGameMenu = create_win(height, width, LINES/2, startx);
    keypad(inGameMenu, TRUE);

    printMenu(inGameMenu, numChoices, highlight, InGameMenuChoices);

    while(1)
    {
        c = wgetch(inGameMenu);
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
        printMenu(inGameMenu, numChoices, highlight, InGameMenuChoices);
        if(choice != 0)
            break;
    }

    return choice;

}

int betMenu(int currentBet, int highlight)
{
    WINDOW *betMenu;

    int numChoices = sizeof(BetMenuChoices)/sizeof(BetMenuChoices[0]);

    int bet = currentBet;
    int choice = 0;
    int c = 0;

    if(highlight == 0)
        highlight = 1;

    int width = COLS/4;
    int height = LINES/2;

    int startx = COLS - (COLS/4);

    betMenu = create_win(height, width, LINES/2, startx);
    keypad(betMenu, TRUE);

    printBetMenu(betMenu, numChoices, bet, highlight);

    while(1)
    {
        choice = 0;
        c = wgetch(betMenu);
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
        printBetMenu(betMenu, numChoices, bet, highlight);
        if(choice != 0)
            break;
    }

    return choice;
}


void printBetMenu(WINDOW *menu, int numChoices, int bet, int highlight)
{
    int xMargin = 2;
    int yMargin = 4;

    mvwprintw(menu, yMargin - 2, xMargin, "Set bet: %d", bet);

    for(int i = 0; i < 3; i++){

        if(highlight == i + 1){
            wattron(menu, A_REVERSE);
            mvwprintw(menu, yMargin, xMargin, "%s", BetMenuChoices[i]);
            wattroff(menu, A_REVERSE);
        }
        else
            mvwprintw(menu, yMargin, xMargin, "%s", BetMenuChoices[i]);
        
        ++yMargin;
    }

    wrefresh(menu);
}

void statsWindow(int money, int bet, int handValue, int dealerHandValue, const char *message)
{
    WINDOW *statsWindow;
    int width = COLS/4;
    int height = LINES/2;

    int startx = COLS - (COLS/4);

    statsWindow = create_win(height, width, 0, startx);

    mvwprintw(statsWindow, 1 , 2, "Money = %d", money);
    mvwprintw(statsWindow, 2 , 2, "Bet = %d", bet);

    if(handValue > 0)
        mvwprintw(statsWindow, 3 , 2, "Your Hand = %d", handValue);

    if(dealerHandValue > 0)
        mvwprintw(statsWindow, 4 , 2, "Dealer Hand = %d", dealerHandValue);

    if(message != ""){
        wattron(statsWindow, A_REVERSE);
        mvwprintw(statsWindow, height - 2, 2, "%s", message);
        wattroff(statsWindow, A_REVERSE);
    }

    wrefresh(statsWindow);
    delwin(statsWindow);
}

/*
    Prints an alert message with an 'OK' message to the screen.
    If the length of the message exceeds the bounds determined by the size of
    the alert box, then a single question mark is displayed in the box.

    Max length that can fit in the box is determined by the expression:
        (width - (X_MARGIN * 2)) * (height - ((Y_MARGIN + 1) * 2))
    
    Then, Max length of one line can be determined by the expression:
        width - (X_MARGIN * 2)

    Text that does not fit on one line will be word-wrapped without hypenation
*/
void alert(const char *message, int height, int width, int startY, int startX)
{
    WINDOW *alertBox;

    alertBox = create_win(height, width, startY, startX);
    keypad(alertBox, TRUE);

    if(strlen(message) < width - (X_MARGIN) * 2){
        mvwprintw(alertBox, Y_MARGIN, (width/2) - (strlen(message))/2, message);
    }
    else if(strlen(message) < (width - (X_MARGIN * 2)) * (height - ((Y_MARGIN + 1) * 2))){
        centerJustifyPrint(alertBox, message, width - (X_MARGIN * 2));
    }
    else {
        mvwprintw(alertBox, Y_MARGIN, width/2, "?");
    }
    
    wattron(alertBox, A_REVERSE);
    mvwprintw(alertBox, height - (Y_MARGIN + 1), (width/X_MARGIN) - 1, "OK");
    wattroff(alertBox, A_REVERSE);

    wrefresh(alertBox);

    // Close alert box only on Enter/Return keypress
    while(wgetch(alertBox) != 10);

    wclear(alertBox);
}


/* 
    Prints characters to a given window, centering text when possible.
    Does not hyphenate words that exceed length of line
*/
void centerJustifyPrint(WINDOW *window, const char *string, int maxLineChars) {
    int charsLeft = (strlen(string)); 

    int row = Y_MARGIN;
    int col = X_MARGIN;

    for(int i = 0; string[i] != 0; i++){
        if(col == maxLineChars + X_MARGIN){
            if(charsLeft < maxLineChars){
                col = X_MARGIN + (maxLineChars - charsLeft) / 2;
            }
            else {
                col = X_MARGIN;
            }
            
            row += 1;
        }
        mvwaddch(window, row, col, string[i]);
        charsLeft -= 1;
        col += 1;
    }
}

// 1 2 3 4 5 6 7 8 9 10 11 12 13
// 2 3 4 5 6 7 8 9 10 J  Q  K  A
void printCard(char suit, int value, int cardCount, bool hideFirstCard, bool isDealer)
{
    WINDOW *card;

    int dealerCardRow = LINES/2 - (LINES/4) - 1;
    int playerCardRow = LINES/2 + (LINES/4) - 1;

    char cardValue = '0';
    switch(value)
    {
        case 10:
            cardValue = 'J';
            break;

        case 11:
            cardValue = 'Q';
            break;

        case 12:
            cardValue = 'K';
            break;

        case 13:
            cardValue = 'A';
            break;
        
        default:
            cardValue = 49 + value;
    }

    if(isDealer){
        if(hideFirstCard && (cardCount == 1))
            card = create_card(CARD_HEIGHT, CARD_WIDTH, dealerCardRow, ((CARD_WIDTH + CARD_OFFSET) * cardCount), '+', '+');
        else
            card = create_card(CARD_HEIGHT, CARD_WIDTH, dealerCardRow, ((CARD_WIDTH + CARD_OFFSET) * cardCount), cardValue, suit);
    }
    else
        card = create_card(CARD_HEIGHT, CARD_WIDTH, playerCardRow, ((CARD_WIDTH + CARD_OFFSET) * cardCount), cardValue, suit);


    wrefresh(card);
}

// Prints a bordered title screen
void printTitle()
{
    WINDOW* titleScreen;
    int startx = 0;

    titleScreen = create_win( LINES, COLS, 0, 0 );

    for( int i = 0 ; i < (sizeof(Title)/sizeof(Title[0])) ; ++i )
    {
        startx = ( COLS / 2 ) - ( strlen( Title[i] ) / 2 );
        mvwprintw( titleScreen, i + TITLE_INDENT, startx, "%s", Title[i] );
    }

    wrefresh( titleScreen );
}

void printMenu( WINDOW* menu, int numChoices, int highlight, const char* choices[] )
{
    int yMargin = Y_MARGIN;

    for( int i = 0 ; i < numChoices ; i++ )
    {
        if ( highlight == i + 1 )
        {
            wattron( menu, A_REVERSE );
            mvwprintw( menu, yMargin, X_MARGIN, "%s", choices[i] );
            wattroff( menu, A_REVERSE );
        }
        else
        {
            mvwprintw( menu, yMargin, X_MARGIN, "%s", choices[i] );
        }
        
        ++yMargin;
    }

    wrefresh( menu );
}


// Print menu to screen such that each item in choices is center justified.
void printCenterMenu( WINDOW *menu, int numChoices, int highlight, int maxWidth, const char *choices[])
{
    int yMargin = Y_MARGIN;

    for(int i = 0; i < numChoices; i++){
        int left_padding = (maxWidth - strlen(choices[i])) / 2;

        if(highlight == i + 1){
            wattron(menu, A_REVERSE);
            mvwprintw(menu, yMargin, left_padding, "%s",choices[i]);
            wattroff(menu, A_REVERSE);
        }
        else
            mvwprintw(menu, yMargin, left_padding, "%s",choices[i]);
        
        ++yMargin;
    }

    wrefresh(menu);
}

int longestStringLength(int numChoices, const char *choices[]) {
    if(choices == NULL)
        return -1;

    int longest_length = 0;
    
    for(int i = 0; i < numChoices; i++){
        int length = strlen(choices[i]);
        if(length > longest_length)
            longest_length = length;
    }

    return longest_length;
}

int menuLoop()
{
    int numChoices = sizeof(MenuChoices)/sizeof(MenuChoices[0]);
    int menuWidth = longestStringLength(numChoices, MenuChoices) + X_MARGIN;

    int starty = TITLE_LINES + TITLE_INDENT + 1; // Add another space below title
    int startx = (COLS - menuWidth) / 2;

    int highlight = 1;
    int choice = 0;
    int c = 0;

    WINDOW *menu = create_win(numChoices + 2, menuWidth, starty, startx);
    keypad(menu, TRUE);
    printCenterMenu(menu, numChoices, highlight, menuWidth, MenuChoices);

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
        printCenterMenu(menu, numChoices, highlight, menuWidth, MenuChoices);
        if(choice != 0)
            break;
    }

    return choice;
}

/**
 * @brief Creates a new window with a border and refreshes it.
 */
WINDOW* create_win( int height, int width, int starty, int startx )
{
    WINDOW* local_win;

    local_win = newwin( height, width, starty, startx );
    box( local_win, 0, 0 );

    wrefresh( local_win );

    return local_win;
}

void destroy_win( WINDOW* local_win )
{
    wborder( local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ' );
    wrefresh( local_win );
    delwin( local_win );
}

WINDOW *create_card(int height, int width, int starty, int startx, char value, char suit)
{
    WINDOW *local_card;

    local_card = newwin(height, width, starty, startx);

    // Special case for a 10 card
    if(value == ':'){
        wborder(local_card, '|', '|', '-', '-', suit, '0', '1' , suit);
        mvwaddch(local_card, 0, (width - 2), '1');
        mvwaddch(local_card, (height-1), 1, '0');
        wrefresh(local_card);
        return local_card;
    }

    wborder(local_card, '|', '|', '-', '-', suit, value, value , suit);

    wrefresh(local_card);

    return local_card;
}