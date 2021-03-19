#ifndef __DECK_H__
#define __DECK_H__

#include "cards.h"
#include "GAME_ERROR.h"
#include <stdlib.h>

/*
TODO:
DeckTakeCard.

*/


typedef struct Deck Deck;


/*
Description: Creates a new deck number of decks wanted.
Inputs: Number of decks wanted.
Outputs: Pointer to the deck or NULL.
Errors: NULL if failed.
*/
Deck *DeckCreate(size_t _numOfDecks);

/*
Description: Destroy a given deck.
Inputs: Pointer to the deck.
Outputs: None.
Errors: Won't destroy if given pointer not initialized.
*/
void DeckDestroy(Deck *_deck);

/*
Description: Shuffle a given deck.
Inputs: Pointer to the deck.
Outputs: OK, POINTER_NOT_INITIALIZED.
Errors: POINTER_NOT_INITIALIZED if given deck not initailized.
*/
GAME_ERRORS DeckShuffle(Deck *_deck);


/*
Description: Take a card from a given deck. (from the end of the deck)
Inputs: Pointer to the deck, card container to output the card to.
Outputs: OK, EMPTY_DECK, POINTER_NOT_INITIALIZED.
Errors: EMPTY_DECK if deck is empty or POINTER_NOT_INITIALIZED if given deck not initailized.
*/
GAME_ERRORS DeckCardDisribute(Deck *_deck, CARD *_card);


/*
Description: Checks if given deck is empty.
Inputs: Pointer to the deck.
Outputs: EMPTY_DECK, DECK_NOT_EMPTY, POINTER_NOT_INITIALIZED.
Errors: POINTER_NOT_INITIALIZED if given deck not initailized.
*/
GAME_ERRORS IsDeckEmpty(Deck *_deck);

/*
Description: Gets the current number of cards in the given deck.
Inputs: Pointer to the deck, pointer to output the number of cards to.
Outputs: OK, POINTER_NOT_INITIALIZED.
Errors: POINTER_NOT_INITIALIZED if given deck not initailized or given card number holder pointer not initialized.
*/
GAME_ERRORS DeckGetNumOfCards(Deck *_deck, size_t *_cardNum);



/*
Description: Prints the cards of a given deck.
Inputs: Pointer to the deck.
Outputs: none.
Errors: won't print if given deck not initialized.
*/
void DeckPrint(Deck *_deck);

#endif