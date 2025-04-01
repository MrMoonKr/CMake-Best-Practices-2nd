#ifndef DEBUG_H
#define DEBUG_H

//#include <pcg_variants.h>
#include <pcg_random.hpp>

#include "display.h"
#include "card.h"

static const char *DebugChoices[] = {
    "Print Deck",
    "Shuffle Deck",
    "Back",
};

int debugLoop();

void printCards( Card *deckPtr);

void debugCards(pcg32 *randSeed);

void debugShuffle(pcg32 *randSeed);


#endif