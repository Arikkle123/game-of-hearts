#include <stdlib.h> 
#include <time.h>
#include <stdio.h>

#include "deck.h"

void DeckCreateWith0();
void DeckCreate1();
void DeckCreate2();

void DeckDoubleFree();

void DeckShuffleNotInitialized();
void DeckShuffleTest1();
void DeckShuffleTest2();

void DeckCardDisributeNotInitialized();
void DeckCardDisributeCardHolderNotInitialized();
void DeckCardDisributeTest1();
void DeckCardDisributeTest2();
void DeckCardDisributeEmptyDeck();


void DeckIsEmptyNotInitialized();
void DeckIsEmptyEmptyDeck();
void DeckIsEmptyNotEmptyDeck();


int main(void)
{
    DeckCreateWith0();
    DeckCreate1();
    DeckCreate2();
    putchar('\n');

    printf("Double Free Test start:\n");
    DeckDoubleFree();
    printf("\nDouble Free Test End.\n");
    putchar('\n');

    DeckShuffleNotInitialized();
    DeckShuffleTest1();
    putchar('\n');

    DeckCardDisributeNotInitialized();
    DeckCardDisributeCardHolderNotInitialized();
    DeckCardDisributeTest1();
    DeckCardDisributeTest2();
    DeckCardDisributeEmptyDeck();
    putchar('\n');

    DeckIsEmptyNotInitialized();
    DeckIsEmptyEmptyDeck();
    DeckIsEmptyNotEmptyDeck();
    putchar('\n');
    
}




void DeckCreateWith0()
{
    Deck *deckPtr = DeckCreate(0);
    if(deckPtr == NULL)
    {
        printf("Deck create with 0 deck test PASS!\n");
    }
    else
    {
        printf("Deck create with 0 deck test FAIL!\n");
    }
}
void DeckCreate1()
{
    Deck *deckPtr = DeckCreate(1);
    size_t numOfCards;
    if (DeckGetNumOfCards(deckPtr, &numOfCards) != OK)
    {
        printf("Get number of cards failed! \n");
        DeckDestroy(deckPtr);
        return;
    }
    if(deckPtr != NULL && numOfCards == 52)
    {
        printf("Deck create with 1 deck test PASS!\n");
    }
    else{
        printf("Deck create with 1 deck test FAIL!\n");
    }
    DeckDestroy(deckPtr);
}
void DeckCreate2()
{
    Deck *deckPtr = DeckCreate(2);
    size_t numOfCards;
    if (DeckGetNumOfCards(deckPtr, &numOfCards) != OK)
    {
        printf("Get number of cards failed! \n");
        DeckDestroy(deckPtr);
        return;
    }
    if(deckPtr != NULL && numOfCards == 104)
    {
        printf("Deck create with 2 deck test PASS!\n");
    }
    else{
        printf("Deck create with 2 deck test FAIL!\n");
    }    
    DeckDestroy(deckPtr);
}

void DeckDoubleFree()
{
    Deck *deckPtr = DeckCreate(2);
    DeckDestroy(deckPtr);
    DeckDestroy(deckPtr);
}

void DeckShuffleNotInitialized()
{
    Deck *deckPtr = NULL;
    if(DeckShuffle(deckPtr) == POINTER_NOT_INITIALIZED)
    {
        printf("Deck shuffle not initialized deck PASS!\n");
    }
    else{
        printf("Deck shuffle not initialized deck FAIL!\n");
    }
}
void DeckShuffleTest1()
{
    Deck *deckPtr = DeckCreate(1);
    size_t i, checkSum = 0;
    CARD cardHolder;
    DeckShuffle(deckPtr);
    for(i = 0; i < 52; i++)
    {
        DeckCardDisribute(deckPtr, &cardHolder);
        checkSum += (size_t)cardHolder;
    }
    if(checkSum == 1326)
    {
        printf("Deck shuffle test with 1 deck PASS!\n");
    }
    else
    {
        printf("Deck shuffle test with 1 deck FAIL!\n");
    }
    DeckDestroy(deckPtr);
}
void DeckShuffleTest2();

void DeckCardDisributeNotInitialized()
{
    Deck *deckPtr = NULL;
    CARD cardHolder;
    if(DeckCardDisribute(deckPtr, &cardHolder) == POINTER_NOT_INITIALIZED)
    {
        printf("Deck Card Disribute Not Initialized deck PASS!\n");
    }
    else{
        printf("Deck Card Disribute Not Initialized deck FAIL!\n");
    }
}
void DeckCardDisributeCardHolderNotInitialized()
{
    Deck *deckPtr = DeckCreate(1);
    CARD *cardHolder = NULL;
    if(DeckCardDisribute(deckPtr, cardHolder) == POINTER_NOT_INITIALIZED)
    {
        printf("Deck Card Disribute Not Initialized card holder PASS!\n");
    }
    else{
        printf("Deck Card Disribute Not Initialized card holder FAIL!\n");
    }
    DeckDestroy(deckPtr);
}

void DeckCardDisributeTest1()
{
    Deck *deckPtr = DeckCreate(1);
    CARD cardHolder = 0;
    if(DeckCardDisribute(deckPtr, &cardHolder) == OK && cardHolder == club_K)
    {
        printf("Deck Card Disribute test 1 PASS!\n");
    }
    else{
        printf("Deck Card Disribute test 1 FAIL!\n");
    }
    DeckDestroy(deckPtr);
}
void DeckCardDisributeTest2()
{
    Deck *deckPtr = DeckCreate(1);
    CARD cardHolder1 = 0;
    CARD cardHolder2 = 0;
    DeckCardDisribute(deckPtr, &cardHolder1);
    if(DeckCardDisribute(deckPtr, &cardHolder2) == OK && cardHolder2 == club_Q && cardHolder1 == club_K)
    {
        printf("Deck Card Disribute test 2 PASS!\n");
    }
    else{
        printf("Deck Card Disribute test 2 FAIL!\n");
    }
    DeckDestroy(deckPtr);
}


void DeckCardDisributeEmptyDeck()
{
    Deck *deckPtr = DeckCreate(1);
    CARD cardHolder;
    size_t i;
    for(i = 0; i < 52; i++)
    {
        DeckCardDisribute(deckPtr, &cardHolder);
        cardHolder = 0;
    }
    if(DeckCardDisribute(deckPtr, &cardHolder) == EMPTY_DECK && cardHolder == 0)
    {
        printf("Deck Card Disribute empty deck PASS!\n");
    }
    else{
        printf("Deck Card Disribute empty deck FAIL!\n");
    }
    DeckDestroy(deckPtr);
}

void DeckIsEmptyNotInitialized()
{
    Deck *deckPtr = NULL;
    if(IsDeckEmpty(deckPtr) == POINTER_NOT_INITIALIZED)
    {
        printf("Deck Card is empty Not Initialized deck PASS!\n");
    }
    else{
        printf("Deck Card is empty Not Initialized deck FAIL!\n");
    }
}
void DeckIsEmptyEmptyDeck()
{
    Deck *deckPtr = DeckCreate(1);
    CARD cardHolder;
    size_t i;
    for(i = 0; i < 52; i++)
    {
        DeckCardDisribute(deckPtr, &cardHolder);
    }
    if(IsDeckEmpty(deckPtr) == EMPTY_DECK)
    {
        printf("Deck Card is empty empty deck PASS!\n");
    }
    else{
        printf("Deck Card is empty empty deck FAIL!\n");
    }
    DeckDestroy(deckPtr);
}
void DeckIsEmptyNotEmptyDeck()
{
    Deck *deckPtr = DeckCreate(1);
    if(IsDeckEmpty(deckPtr) == DECK_NOT_EMPTY)
    {
        printf("Deck Card is empty not empty deck PASS!\n");
    }
    else{
        printf("Deck Card is empty not empty deck FAIL!\n");
    }
    DeckDestroy(deckPtr);
}
