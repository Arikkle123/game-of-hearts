#include <stdlib.h> 
#include <time.h>
#include <stdio.h>

#include "deck.h"

#define MAGIC 4459897

struct Deck{
    CARD *m_deckArray;
    size_t m_cardsNum;
    int m_magicNum;
};

/* HELPER */
void SwapCards(CARD *_deck, size_t _a, size_t _b);
/* HELPER_END */



Deck *DeckCreate(size_t _numOfDecks)
{
    Deck *_deckPtr;
    CARD *_deckCardArr;
    size_t index;
    if(_numOfDecks == 0)
    {
        return NULL;
    }
    _deckPtr = malloc(sizeof(Deck));
    if(_deckPtr == NULL)
    {
        return NULL;
    } 
    _deckCardArr = malloc(sizeof(CARD) * NUM_OF_CARDS * _numOfDecks);
    if(_deckCardArr == NULL)
    {
        free(_deckPtr);
        return NULL;
    }
    for(index = 0; index < NUM_OF_CARDS * _numOfDecks; index++)
    {
        _deckCardArr[index] = index % NUM_OF_CARDS;
    }
    _deckPtr->m_deckArray = _deckCardArr;
    _deckPtr->m_cardsNum = _numOfDecks * NUM_OF_CARDS;
    _deckPtr->m_magicNum = MAGIC;
    return _deckPtr;
}


void DeckDestroy(Deck *_deck)
{
    if(_deck == NULL || _deck->m_magicNum != MAGIC)
    {
        return;
    }
    free(_deck->m_deckArray);
    _deck->m_magicNum = 0;
    free(_deck);
}



GAME_ERRORS DeckShuffle(Deck *_deck)
{
    size_t i, j;
    if(_deck == NULL || _deck->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    srand ( time(NULL) );
    for(i = _deck->m_cardsNum - 1; i > 0; i--)
    {
        SwapCards(_deck->m_deckArray, rand() % (i+1), i);
    }
    return OK;

}


GAME_ERRORS DeckCardDisribute(Deck *_deck, CARD *_card)
{
    if(_deck == NULL || _deck->m_magicNum != MAGIC || _card == NULL)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_deck->m_cardsNum == 0)
    {
        return EMPTY_DECK;
    }
    *_card = _deck->m_deckArray[_deck->m_cardsNum - 1];
    (_deck->m_cardsNum)--;
    return OK;
}


GAME_ERRORS IsDeckEmpty(Deck *_deck)
{
    if(_deck == NULL || _deck->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_deck->m_cardsNum == 0)
    {
        return EMPTY_DECK;
    }
    return DECK_NOT_EMPTY;
}

GAME_ERRORS DeckGetNumOfCards(Deck *_deck, size_t *_cardNum)
{
    if(_deck == NULL || _deck->m_magicNum != MAGIC || _cardNum == NULL)
    {
        return POINTER_NOT_INITIALIZED;
    }
    *_cardNum = _deck->m_cardsNum;
    return OK;
}


/* TESTING */
void DeckPrint(Deck *_deck)
{
    size_t i;
    if(_deck == NULL || _deck->m_magicNum != MAGIC)
    {
        return;
    }
    for(i = 0; i < _deck->m_cardsNum; i++)
    {
        printf("%ld card is %d\n", i+1, _deck->m_deckArray[i]);
    }

}



/* HELPER */

void SwapCards(CARD *_deck, size_t _a, size_t _b)
{
    CARD temp = _deck[_a];
    _deck[_a] = _deck[_b];
    _deck[_b] = temp;
}