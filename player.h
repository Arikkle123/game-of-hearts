#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cards.h"
#include "GAME_ERROR.h"
#include "ui.h"

typedef struct Player Player;

typedef enum PLAYER_TYPE {
    HUMAN_PLAYER,
    COMPUTER_PLAYER
} PLAYER_TYPE;


/*
Description: Creates a new player with the name given and identity - Human player or computer player.
Inputs: String of the name given to the player, identity - Human/Computer, number of max cards the player will use during the game.
Outputs: Pointer to the player or NULL.
Errors: NULL if failed - pointer to the name NULL OR identity illegal.
*/
Player *PlayerCreate(char *_name, PLAYER_TYPE _identity);


/*
Description: Destroy a given player.
Inputs: Pointer to the player.
Outputs: None.
Errors: Won't destroy if given pointer not initialized.
*/
void PlayerDestroy(Player *_player);


/*
Description: Give a card to a player.
Inputs: Pointer to the player, card to give.
Outputs: OK, POINTER_NOT_INITIALIZED, ILLEGAL_CARD, HAND_REALLOCATION_FAIL.
Errors: POINTER_NOT_INITIALIZED - if player pointer not initialized, ILLEGAL_CARD - if given card not legal in the current deck, HAND_REALLOCATION_FAIL.
*/
GAME_ERRORS PlayerGiveCard(Player *_player, CARD _card);

/*
Description: Take a card from a player by index in the hand.
Inputs: Pointer to the player, pointer to the card container to output to, index of the card in player's hand.
Outputs: OK, POINTER_NOT_INITIALIZED, ILLEGAL_INDEX, EMPTY_HAND
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, ILLEGAL_INDEX if given index out of player's hand bounds, EMPTY_HAND - if player's hand is empty.
*/
GAME_ERRORS PlayerTakeCardByIndex(Player *_player, CARD *_cardOutput, size_t _cardIndex);

/*
Description: Take a card from a player by card type.
Inputs: Pointer to the player, pointer to the card container to output to, type of card to take.
Outputs: OK, POINTER_NOT_INITIALIZED, CARD_NOT_FOUND, EMPTY_HAND
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, CARD_NOT_FOUND - if given type of card is not found in player's hand, EMPTY_HAND - if player's hand is empty.
*/
GAME_ERRORS PlayerTakeCardByCardType(Player *_player, CARD *_cardOutput, CARD _cardType);



/*
Description: Take a card from a player by given rule function
Inputs: Pointer to the player, pointer to the card container to output to, pointer to the rule function
Outputs: OK, POINTER_NOT_INITIALIZED, ILLEGAL_CARD, CARD_NOT_FOUND, EMPTY_HAND
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, CARD_NOT_FOUND - if given type of card is not found in player's hand, EMPTY_HAND - if player's hand is empty.
*/
GAME_ERRORS PlayerTakeCardByRuleFunction(Player *_player, CARD *_cardOutput, GAME_ERRORS (*_cardFindIndexFunction)(CARD *_hand, size_t _numOfCardsInHand, size_t *_indexOutput));

/*
Description: Sort the hand of the player - by the order of the enum - spades, hearts, diamonds, clubs, by rank. (using bubble sort)
Inputs: Pointer to the player.
Outputs: OK, POINTER_NOT_INITIALIZED, EMPTY_HAND.
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, EMPTY_HAND - if hand is empty.
*/
GAME_ERRORS PlayerSortHand(Player *_player);


/*
Description: Checks if given player's hand is empty.
Inputs: Pointer to the player.
Outputs: CARD_FOUND, CARD_NOT_FOUND, POINTER_NOT_INITIALIZED, ILLEGAL_CARD.
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, ILLEGAL_CARD - if card is not in the standart card deck.
*/
GAME_ERRORS PlayerHandIsEmpty(Player *_player);


/*
Description: Check if given card is found in given player's hand
Inputs: Pointer to the player, card to find.
Outputs: POINTER_NOT_INITIALIZED, EMPTY_HAND, HAND_NOT_EMPTY.
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized.
*/
GAME_ERRORS PlayerCardIsFound(Player *_player, CARD _card);



/*
Description: check player's hand for given card suite
Inputs: Pointer to the player, suite to check for
Outputs: POINTER_NOT_INITIALIZED, ILLEGAL_SUITE, FOUND, NOT_FOUND
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, ILLEGAL_SUITE - if not legal suite given.
*/
GAME_ERRORS PlayerCheckHandForSuite(Player *_player, CARD_SUITS _suite);


/*
Description: check player's hand if consists from heart cards only
Inputs: Pointer to the player.
Outputs: EMPTY_HAND, TRUE, FALSE
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, ILLEGAL_SUITE - if not legal suite given.
*/
GAME_ERRORS CheckHandForAllHearts(Player *_player);


/*
Description: Finds the current lowest rank card in player's hand.
Inputs: Pointer to the player, card pointer to output the answer.
Outputs: OK, POINTER_NOT_INITIALIZED, EMPTY_HAND.
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, EMPTY_HAND.
*/
GAME_ERRORS PlayerGetMinCard(Player *_player, CARD *_cardHolder);

/*
Description: Finds the current lowest rank card in player's hand suits the give card suite
Inputs: Pointer to the player, card pointer to output the answer, suite.
Outputs: OK, POINTER_NOT_INITIALIZED, EMPTY_HAND, CARD_NOT_FOUND;
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, EMPTY_HAND, CARD_NOT_FOUND - if no cards in found from the given suite.
*/
GAME_ERRORS PlayerGetMinCardBySuite(Player *_player, CARD *_cardHolder, CARD_SUITS _cardSuite);



/*
Description: Finds the current highest rank card in player's hand suits the give card suite
Inputs: Pointer to the player, card pointer to output the answer, suite.
Outputs: OK, POINTER_NOT_INITIALIZED, EMPTY_HAND, CARD_NOT_FOUND;
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, EMPTY_HAND, CARD_NOT_FOUND - if no cards in found from the given suite.
*/
GAME_ERRORS PlayerGetMaxCardBySuite(Player *_player, CARD *_cardHolder, CARD_SUITS _cardSuite);



/*
Description: Finds the current highest rank card in player's hand.
Inputs: Pointer to the player, card pointer to output the answer.
Outputs: OK, POINTER_NOT_INITIALIZED, EMPTY_HAND.
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, EMPTY_HAND.
*/
GAME_ERRORS PlayerGetMaxCard(Player *_player, CARD *_cardHolder);




/*
Description: Check a card of given player by given index.
Inputs: Pointer to the player, index of card in the hand, card pointer to output the answer.
Outputs: OK, POINTER_NOT_INITIALIZED, EMPTY_HAND, CARD_NOT_FOUND
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, EMPTY_HAND, CARD_NOT_FOUND - if given index not in hand.
*/
GAME_ERRORS PlayerGetCardByIndex(Player *_player, size_t _cardIndex, CARD *_cardHolder);


/*
Description: copies player's hand to given array CARD array.
Inputs: Pointer to the player, pointer to the array.
Outputs: OK, POINTER_NOT_INITIALIZED, EMPTY_HAND, 
Errors: POINTER_NOT_INITIALIZED - if player pointer container pointer not initialized, EMPTY_HAND, 
*/
GAME_ERRORS PlayerShowHand(Player *_player, CARD *_handOutput);


/*
Description: Print the player's hand.
Inputs: Pointer to the player.
Outputs: None.
Errors: Will not print if given player not initialized or hand is empty.
*/
void PlayerPrintHand(Player *_player);








/*********************** GET FUNCTIONS ***********************/

/*
Description: Get the name of the player.
Inputs: Pointer to the player, pointer to the name container to output to.
Outputs: OK, POINTER_NOT_INITIALIZED.
Errors: POINTER_NOT_INITIALIZED - if player or container pointer not initialized.
*/
GAME_ERRORS PlayerGetName(Player *_player, char *_name);

/*
Description: Get the identity of the player - human player or computer player.
Inputs: Pointer to the player, pointer to the identity container to output to.
Outputs: OK, POINTER_NOT_INITIALIZED.
Errors: POINTER_NOT_INITIALIZED - if player or container pointer not initialized.
*/
GAME_ERRORS PlayerGetIdentity(Player *_player, PLAYER_TYPE *_identity);

/*
Description: Get the hand of the player.
Inputs: Pointer to the player, pointer to the hand container to output to.
Outputs: OK, POINTER_NOT_INITIALIZED.
Errors: POINTER_NOT_INITIALIZED - if player or container pointer not initialized.
*/
GAME_ERRORS PlayerGetHand(Player *_player, CARD **_hand);

/*
Description: Get the current number of cards the player has.
Inputs: Pointer to the player, pointer to the number container to output to.
Outputs: OK, POINTER_NOT_INITIALIZED.
Errors: POINTER_NOT_INITIALIZED - if player or container pointer not initialized.
*/
GAME_ERRORS PlayerGetNumOfCards(Player *_player, size_t *_numOfCards);




#endif