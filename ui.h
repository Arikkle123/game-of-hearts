#ifndef UI_H
#define UI_H
#include "cards.h"



/*  Card Print Function! */

void PrintCard(CARD _card);

void PrintSuite(CARD_SUITS _suite);

/*
Description: Print game start declartion to the terminal.
*/
void ShowGameStartDeclaration();

/*
Description: Print error for inputing false card.
*/
void ShowInvalidCardError();

/*
Description: prints an array of given cards.
*/
void PrintGivenCards(CARD *_cardsArr, size_t _numOfCards);

/*
Description: prints a given player's name.
*/
void ShowPlayersName(char *_name);

/*
Description: prints the name of the starting player of the round.
*/
void ShowStartingPlayer(char *_name);

/*
Description: prints the name of the losing player of the trick.
*/
void ShowTrickLoser(char *_name, size_t _currentScore);

/*
Description: prints the name of the player given and his given score.
*/
void ShowPlayerScoreState(char *_name, size_t _currentScore);

/*
Description: declare new round with it's number
*/
void ShowDeclareNewRound(size_t _num);
/*
Description: print the given card hand.
*/
void ShowHand(CARD *_cardsArr, size_t _numOfCards);

/*
Description: print the losers name and score.
*/
void ShowGameLoser(char *_name, size_t _currentScore);

/*
Description: print a message to input card number and scan for user's choice.
*/
void ShowGetPlayerChoice(int *_input, size_t numOfCards);

/*
Description: print a message for Card pass session.
*/
void ShowDeclareCardPass();

/*
Description: print a message for the number of the given trick.
*/
void ShowTrickNumber(size_t _num);


void ShowTable(CARD_SUITS _leadingSuite, char **_names, CARD *_cards);


#endif