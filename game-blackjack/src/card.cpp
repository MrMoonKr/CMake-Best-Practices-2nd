#include "card.h"

//#include <pcg_random.hpp>
#include <random>

void initDeck( Card *deckPtr)
{
    int i;

    for(i = 1; i <= 13; i++){
        deckPtr->value = i;
        deckPtr->suit = 'D';
        deckPtr++;
    }

    for(i = 1; i <= 13; i++){
        deckPtr->value = i;
        deckPtr->suit = 'S';
        deckPtr++;
    }

    for(i = 1; i <= 13; i++){
        deckPtr->value = i;
        deckPtr->suit = 'H';
        deckPtr++;
    }

    for(i = 1; i <= 13; i++){
        deckPtr->value = i;
        deckPtr->suit = 'C';
        deckPtr++;
    }

}

void swapCard( Card *rCard,  Card *lCard)
{
    Card temp;
    temp.value = rCard->value;
    temp.suit = rCard->suit;

    rCard->value = lCard->value;
    rCard->suit = lCard->suit;

    lCard->value = temp.value;
    lCard->suit = temp.suit;
}

void deckCopy(const  Card *sourceDeck,  Card *copyDeck)
{
    for(int i = 0; i < 52; i++){
        (copyDeck+i)->value = (sourceDeck+i)->value;
        (copyDeck+i)->suit = (sourceDeck+i)->suit;
    }
}

/*
Take top card from deck and place it into the deck at a random location
Continue until the bottom card is on top
This should take less than 400 iterations
*/
void pokeShuffle( Card *deckPtr, pcg32 *randSeed)
{
    Card bottomCard;
    Card tempCard;
    int randSelect;

    //Save bottom card of deck
    bottomCard.value = (deckPtr + 51)->value;
    bottomCard.suit = (deckPtr + 51)->suit;

    std::uniform_int_distribution<int> dist( 0, 51 );

    while(!(deckPtr->value == bottomCard.value && deckPtr->suit == bottomCard.suit)){
        //randSelect = pcg32_boundedrand_r(randSeed, 51) + 1;
        randSelect = dist( *randSeed ) + 1;

        tempCard.value = (deckPtr + randSelect)->value;
        tempCard.suit = (deckPtr + randSelect)->suit;

        (deckPtr + randSelect)->value = deckPtr->value;
        (deckPtr + randSelect)->suit = deckPtr->suit;

        for(int i = 0; i < randSelect; i++){
            (deckPtr+i)->value = (deckPtr+(i+1))->value;
            (deckPtr+i)->suit = (deckPtr+(i+1))->suit;
        }

        (deckPtr+(randSelect-1))->value = tempCard.value;
        (deckPtr+(randSelect-1))->suit = tempCard.suit;
    }
}

/*
Make and init a temporary deck
Randomly pick cards from temp deck and assign value to given deck (deckPtr)
until all elements in temp deck are 'zeroed' ()
This can take upwards of 600 iterations to complete
*/
void washShuffle( Card *deckPtr, pcg32 *randSeed)
{
    Card tempDeck[52];
    Card *tempPtr = 0;
    tempPtr = tempDeck;
    initDeck(tempPtr);
    int randSelect = 0;

    std::uniform_int_distribution<int> dist( 0, 51 );

    for(int i = 0; i < 52; i++){
        //randSelect = pcg32_boundedrand_r(randSeed, 52);
        randSelect = dist( *randSeed );
        while((tempPtr+randSelect)->suit == '0')
            //randSelect = pcg32_boundedrand_r(randSeed, 52);
            randSelect = dist( *randSeed);

        (deckPtr+i)->value = (tempPtr+randSelect)->value;
        (deckPtr+i)->suit = (tempPtr+randSelect)->suit;
        (tempPtr+randSelect)->suit = '0';
    }

    return;
}

void riffleShuffle( Card *deckPtr)
{
    Card topHalf[26];
    Card bottomHalf[26];
    int i = 0;
    int k = 0;

    for(i = 0; i < 26; i++){
        topHalf[i].value = (deckPtr+i)->value;
        topHalf[i].suit = (deckPtr+i)->suit;
    }

    for(i = 0; i < 26; i++){
        bottomHalf[i].value = (deckPtr+(i+26))->value;
        bottomHalf[i].suit = (deckPtr+(i+26))->suit;
    }

    for(i = 0; i < 52; i++){
        if((i % 2) == 0){
            (deckPtr+i)->value = topHalf[k].value;
            (deckPtr+i)->suit = topHalf[k].suit;
        }
        else{
            (deckPtr+i)->value = bottomHalf[k].value;
            (deckPtr+i)->suit = bottomHalf[k].suit;
            k++;
        }
    }

    return;
}

/*
Shift the cards up by one, 26 times so that the top half is now 
the bottom half, and vice versa
*/
void cutShuffle( Card *deckPtr)
{
    Card tempCard;

    for(int i = 0; i < 26; i++){
        tempCard.value = deckPtr->value;
        tempCard.suit = deckPtr->suit;

        for(int j = 0; j < 51; j++){
            (deckPtr+j)->value = (deckPtr+(j+1))->value;
            (deckPtr+j)->suit = (deckPtr+(j+1))->suit;
        }

        (deckPtr+51)->value = tempCard.value;
        (deckPtr+51)->suit = tempCard.suit;
    }

    return;
}

/*
Take a portion (no larger than a quarter) off the top of the deck and place 
it at the bottom of the deck (maintaining the order) and shift the cards up 
by one until all of the cards have been moved.
*/
void boxShuffle( Card *deckPtr, pcg32 *randSeed)
{
    Card tempCard;
    int randSelect;
    int cards = 52;

    std::uniform_int_distribution<int> dist( 0, 51 );

    while(cards > 0){
        //randSelect = pcg32_boundedrand_r(randSeed, 12) + 1;
        randSelect = dist(*randSeed ) + 1;

        for(int i = 0; i < randSelect; i++){
            tempCard.value = deckPtr->value;
            tempCard.suit = deckPtr->suit;

            for(int j = 0; j < 51; j++){
                (deckPtr+j)->value = (deckPtr+(j+1))->value;
                (deckPtr+j)->suit = (deckPtr+(j+1))->suit;
            }

            (deckPtr+51)->value = tempCard.value;
            (deckPtr+51)->suit = tempCard.suit;
        }

        cards -= randSelect;
    }

    return;
}

void vegasShuffle( Card *deckPtr, pcg32 *randSeed)
{
    washShuffle(deckPtr, randSeed);
    riffleShuffle(deckPtr);
    riffleShuffle(deckPtr);
    boxShuffle(deckPtr, randSeed);
    riffleShuffle(deckPtr);
    cutShuffle(deckPtr);
}
