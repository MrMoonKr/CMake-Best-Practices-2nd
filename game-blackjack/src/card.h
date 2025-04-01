#ifndef CARD_H
#define CARD_H

// #include <pcg_variants.h>
#include <pcg_random.hpp>

struct Card
{
    int value;
    char suit;

} ;

void initDeck( Card* deckPtr );

void shuffleDeck( Card* deckPtr );

void swapCard( Card *rCard, Card *lCard);

void deckCopy(const Card *sourceDeck, Card *copyDeck);

// Various shuffle methods
void washShuffle( Card *deckPtr, pcg32 *randSeed);

void pokeShuffle( Card *deckPtr, pcg32 *randSeed);

void riffleShuffle( Card *deckPtr);

void cutShuffle( Card *deckPtr);

void boxShuffle( Card *deckPtr, pcg32 *randSeed);

void vegasShuffle( Card *deckPtr, pcg32 *randSeed);

#endif