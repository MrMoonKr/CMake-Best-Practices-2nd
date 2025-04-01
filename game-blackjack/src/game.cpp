#include "game.h"

#define DEAL    1
#define BET     2
#define EXIT    3

#define HIT         1
#define D_DOWN      2
#define STAND       3
#define SURRENDER   4
#define FOLD        5

void gameLoop(pcg32 *randSeed)
{
    Card deck[52];
    Card *deckPtr = 0;
    deckPtr = deck;

    initDeck(deckPtr);

    bool gameInPlay = true;
    int gameChoice = 0;

    unsigned int bet = 0;

    struct Dealer dealer = {16, NULL};
    struct Player player = {1000, NULL};

    while(gameInPlay){

        if(bet > player.money)
            bet = 0;

        vegasShuffle(deckPtr, randSeed);
        gameBoard(dealer.limit);
        statsWindow(player.money, bet, 0, 0, "");
        gameChoice = gameMenuLoop();
        switch(gameChoice)
        {
            case DEAL:
                handleDeal(bet, &player, &dealer, deckPtr);

                if(!natural21(bet, &player, &dealer, deckPtr))
                    inGameLoop(bet, &player, &dealer, deckPtr);
                
                break;

            case BET:
                bet = handleBet(bet, &player);
                break;

            case EXIT:
                gameInPlay = false;
                break;
        }
        
    }

    refresh();
}


/*
    Check intial hands for a natural 21.

    Push if dealer and player both get blackjack
    Take bet from player if delear gets blackjack
    Or pay player 3 times the bet if player gets blackjack

    Otherwise, return false
*/
bool natural21(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    int dealerSum = sumHand(dealer->hand);
    int playerSum = sumHand(player->hand);

    if(dealerSum == 21 && playerSum == 21){
        addMoney(bet, player);
        printHand(dealer->hand, false, true);
        alert((const char*)"Push!", 6, 16, LINES/2 - 3, COLS/2 - 8);
        delHand(dealer->hand, player->hand, deckPtr);
        return true;
    }
    else if(dealerSum == 21) {
        subtractMoney(bet, player);
        printHand(dealer->hand, false, true);
        alert("Dealer got Blackjack!", 6, 26, LINES/2 - 3, COLS/2 - 8);
        delHand(dealer->hand, player->hand, deckPtr);
        return true;
    }
    else if (playerSum == 21) {
        if(checkBet(bet, 3, player)){
            addMoney(bet*3, player);
        }
        else{
            addMoney(bet, player);
        }

        printHand(dealer->hand, false, true);
        alert("Blackjack!", 6, 16, LINES/2 - 3, COLS/2 - 8);
        delHand(dealer->hand, player->hand, deckPtr);
        return true;
    }

    return false;
} 


// In game loop where player gets cards
void inGameLoop(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    int subGameChoice = 0;
    bool subGameInPlay = true;

    while(subGameInPlay)
    {
        subGameChoice = inGameMenuLoop();
        switch(subGameChoice)
        {
        case HIT:
            handleHit(bet, player, dealer, deckPtr);
            subGameInPlay = handleBust(bet, player, dealer, deckPtr);
            break;

        case D_DOWN:
            // Doubledown can only be selected if player hasn't hit yet.
            if(handCount(player->hand) != 2){
                statsWindow(player->money, bet, sumHand(player->hand), sumObscuredHand(dealer->hand), "Can't Doubledown");
                break;
            }
            
            if(!checkBet(bet, 2, player)){
                statsWindow(player->money, bet, sumHand(player->hand), sumObscuredHand(dealer->hand), "Not enough money");
                break;
            }

            bet *= 2;

            handleDoubleDown(bet, player, dealer, deckPtr);

            if(!handleBust(bet, player, dealer, deckPtr)){
                subGameInPlay = false;
                break;
            }

            dealerTurn(dealer->limit, dealer->hand, deckPtr);
            statsWindow(player->money, bet, sumHand(player->hand), sumHand(dealer->hand), "");
            closeBets(bet, player, dealer, deckPtr);
            subGameInPlay = false;
            break;

        case STAND:
            dealerTurn(dealer->limit, dealer->hand, deckPtr);
            statsWindow(player->money, bet, sumHand(player->hand), sumHand(dealer->hand), "");
            closeBets(bet, player, dealer, deckPtr);
            subGameInPlay = false;
            break;
        
        case SURRENDER:
            {
                unsigned int surrenderBet = bet / 2;
                subtractMoney(surrenderBet, player);
                subGameInPlay = false;
            }
            break;

        case FOLD:
            {
                subGameInPlay = false;
            }
            break;
        }
    }
}

void handleDeal(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    player->hand = initHead(deckPtr);
    dealer->hand = initHead(deckPtr);
    appendCard(deckPtr, player->hand);
    appendCard(deckPtr, dealer->hand);

    printHand(dealer->hand, true, true);
    printHand(player->hand, false, false);

    statsWindow(player->money, bet, sumHand(player->hand), sumObscuredHand(dealer->hand), "");
}

unsigned int handleBet(unsigned int bet, struct Player *player)
{
    int betMenuChoice = 0;

    while(betMenuChoice != 3){
        betMenuChoice = betMenu(bet, betMenuChoice);
        if(betMenuChoice == 1){
            if(player->money > bet){
                bet += 5;
            }
        }
        else if(betMenuChoice == 2){
            if(bet > 0){
                bet -= 5;
            }
        }
    }

    return bet;
}

void handleHit(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    appendCard(deckPtr, player->hand);
    printHand(player->hand, false, false);
    statsWindow(player->money, bet, sumHand(player->hand), sumObscuredHand(dealer->hand), "");
}

void handleDoubleDown(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    appendCard(deckPtr, player->hand);
    printHand(player->hand, false, false);
    statsWindow(player->money, bet, sumHand(player->hand), sumObscuredHand(dealer->hand), "");
}

bool handleBust(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    if(sumHand(player->hand) > 21){
        statsWindow(player->money, bet, sumHand(player->hand), sumHand(dealer->hand), "");
        alert("BUST!", 6, 16, LINES/2 - 3, COLS/2 - 8);
        subtractMoney(bet, player);
        delHand(dealer->hand, player->hand, deckPtr);
        return false;
    }

    return true;
}

void printHand(struct Hand *hand, bool hideFirstCard, bool isDealer)
{
    struct Hand *temp = hand;
    int cardNumber = 1;

    while(temp != NULL){
        printCard(temp->card.suit, temp->card.value, cardNumber, hideFirstCard, isDealer);
        temp = temp->next;
        cardNumber++;
    }
}

Card drawCard( Card *deckPtr)
{
    Card tempCard = {.value = deckPtr->value, .suit = deckPtr->suit};
    shiftDeck(deckPtr, 1);
    return tempCard;
}

void appendCard( Card *deckPtr, struct Hand *hand)
{
    if(hand == NULL){
        hand = (Hand*)malloc(sizeof(struct Hand));
        hand->card = drawCard(deckPtr);
        hand->next = NULL;
        return;
    }

    struct Hand *newHand;
    struct Hand *temp = hand;

    newHand = (Hand*)malloc(sizeof(struct Hand));
    newHand->card = drawCard(deckPtr);
    newHand->next = NULL;

    while(temp->next != NULL)
        temp = temp->next;

    temp->next = newHand;
}

void dealerTurn(int limit, struct Hand *hand, Card *deckPtr)
{
    printHand(hand, false, true);
    bool finishedTurn = false;
    int dealerHand = sumHand(hand);

    while(finishedTurn == false){
        if(sumHand(hand) < limit){
            appendCard(deckPtr, hand);
            printHand(hand, false, true);
        }
        else
            finishedTurn = true;
    }
}

/*
    When the hands are equal, it's a push and player keeps his bet
    When dealer's hand is greater than player's, dealer wins
    When player's hand is greater than dealer's, playe wins
    TODO: There's a lot more nuance to the winning conditions
        that the function doesn't check for yet.
*/
int checkResult(struct Hand *dealerHand, struct Hand *playerHand)
{
    int dealerSum = sumHand(dealerHand);
    int playerSum = sumHand(playerHand);

    if(dealerSum > playerSum)
        return 1;
    if(dealerSum == playerSum)
        return 0;
    if(dealerSum < playerSum)
        return -1;
}

void closeBets(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr)
{
    int dealerSum = sumHand(dealer->hand);
    int playerSum = sumHand(player->hand);

    // Check for dealer bust
    if(dealerSum > 21){
        alert("Dealer busts!", 6, 18, LINES/2 - 3, COLS/2 - 8);
        addMoney(bet * 2, player);
        delHand(dealer->hand, player->hand, deckPtr);
        return;
    }

    if(dealerSum > playerSum){
        alert("Dealer wins!", 6, 16, LINES/2 - 3, COLS/2 - 8);
        subtractMoney(bet, player);
    }
    if(dealerSum == playerSum){
        alert("Push!", 6, 16, LINES/2 - 3, COLS/2 - 8);
    }
    if(dealerSum < playerSum){
        alert("You have won!", 6, 18, LINES/2 - 3, COLS/2 - 8);
        addMoney(bet * 2, player);
    }

    delHand(dealer->hand, player->hand, deckPtr);
}

int sumHand(struct Hand *hand)
{
    if(hand == NULL)
        return -1;

    int sum = 0;
    struct Hand *temp = hand;

    while(temp != NULL){
        if(temp->card.value < 9)
            sum += temp->card.value + 1;
        else if(temp->card.value > 8 && temp->card.value < 13)
            sum += 10;
        else{
            if((sum + 11) <= 21)
                sum += 11;
            else
                sum += 1;
        }

        temp = temp->next;
    }


    return sum;
}

int sumObscuredHand(struct Hand *hand)
{
    if(hand == NULL)
        return -1;

    int sum = 0;
    struct Hand *temp = hand;

    // Skip first/hidden card
    if(temp->next != NULL) {
        temp = temp->next;
    }
    else {
        return -1;
    }

    while(temp != NULL){
        if(temp->card.value < 9)
            sum += temp->card.value + 1;
        else if(temp->card.value > 8 && temp->card.value < 13)
            sum += 10;
        else{
            if((sum + 11) <= 21)
                sum += 11;
            else
                sum += 1;
        }

        temp = temp->next;
    }


    return sum;
}

void delHand(struct Hand *dealerHand, struct Hand *playerHand, struct Card *deckPtr)
{
    if(playerHand == NULL && dealerHand == NULL)
        return;

    // Get total number of played cards so we can put them back into the deck
    int sum = 0;
    struct Hand *temp = playerHand;

    while(temp != NULL){
        sum++;
        temp = temp->next;
    }

    temp = dealerHand;

    while(temp != NULL){
        sum++;
        temp = temp->next;
    }

    // Put cards back at the bottom of the deck

    for(int i = sum; i > 0; i--){
        if(dealerHand != NULL){
            temp = dealerHand;
            dealerHand = dealerHand->next;

            (deckPtr+(52-i))->value = temp->card.value;
            (deckPtr+(52-i))->suit = temp->card.suit;

            free(temp);
        }
        else{
            temp = playerHand;
            playerHand = playerHand->next;

            (deckPtr+(52-i))->value = temp->card.value;
            (deckPtr+(52-i))->suit = temp->card.suit;

            free(temp);
        }
    }
}

struct Hand *initHead(struct Card *deckPtr)
{
    struct Hand *newHand;
    newHand = (Hand*)malloc(sizeof(struct Hand));
    newHand->card = drawCard(deckPtr);
    newHand->next = NULL;

    return newHand;
}

// Shift deck up by an amount (i.e., shift array elements to the left)
void shiftDeck(struct Card *deckPtr, int amount)
{
    if(amount < 0)
        return;

    for(int i = 0; i < amount; i++){
        for(int j = 0; j < 51; j++){
            (deckPtr+j)->value = (deckPtr+(j+1))->value;
            (deckPtr+j)->suit = (deckPtr+(j+1))->suit;
        }
    }

    return;
}

/*
    Returns the number of cards in the given hand
*/
int handCount(struct Hand *hand)
{
    int count = 0;
    struct Hand *temp = hand;

    while(temp != NULL){
        count += 1;

        temp = temp->next;
    }

    return count;
}

bool checkBet(unsigned int bet, unsigned int multiplier, struct Player *player)
{
    if(multiplier == 0){
        return false;
    }

    if (bet * multiplier < bet){
        return false;
    }

    if(bet * multiplier > player->money){
        return false;
    }

    return true;
}


void addMoney(unsigned int bet, struct Player *player)
{
    // UINT Wrap-around
    if(bet + player->money < player->money){
        alert("You have broke the bank!", 6, 30, LINES/2 - 3, COLS/2 - 15);
    }

    player->money = player->money + bet;
}

void subtractMoney(unsigned int bet, struct Player *player)
{
    // UINT Wrap-around
    if(player->money - bet > player->money){
        alert("You are bankrupt!", 6, 22, LINES/2 - 3, COLS/2 - 11);
        return;
    }

    player->money = player->money - bet;
}