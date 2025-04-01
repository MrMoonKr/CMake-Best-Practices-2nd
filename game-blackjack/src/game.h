#ifndef GAME_H
#define GAME_H

//#include <pcg_variants.h>
#include <pcg_random.hpp>
#include <stdlib.h>
#include <stdbool.h>
#include "card.h"
#include "display.h"

struct Hand{
    Card card;
    Hand *next;
};

struct Dealer{
    int limit;
    struct Hand *hand;
};

struct Player{
    unsigned int money;
    struct Hand *hand;
};

void gameLoop(pcg32 *randSeed);

void inGameLoop(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr);

bool natural21(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr);

void handleDeal(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr);

unsigned int handleBet(unsigned int bet, struct Player *player);

void handleHit(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr);

bool handleBust(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr);

void handleDoubleDown(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr);

struct Card drawCard(struct Card *deckPtr);

void shiftDeck(struct Card *deckPtr, int amount);

int handCount(struct Hand *hand);

bool checkBet(unsigned int bet, unsigned int multiplier, struct Player *player);

void addMoney(unsigned int bet, struct Player *player);

void subtractMoney(unsigned int bet, struct Player *player);

void appendCard(struct Card *deckPtr, struct Hand *hand);

void dealerTurn(int limit, struct Hand *hand, struct Card *deckPtr);

int checkResult(struct Hand *dealerHand, struct Hand *playerHand);

void closeBets(unsigned int bet, struct Player *player, struct Dealer *dealer, struct Card *deckPtr);

int sumHand(struct Hand *hand);

int sumObscuredHand(struct Hand *hand);

void delHand(struct Hand *dealerHand, struct Hand *playerHand, struct Card *deckPtr);

//void initHead(struct Card *deckPtr, struct Hand *hand);

struct Hand *initHead(struct Card *deckPtr);

void printHand(struct Hand *hand, bool hideFirstCard, bool isDealer);

#endif