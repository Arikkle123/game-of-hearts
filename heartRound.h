#ifndef __HEARTROUND_H__
#define __HEARTROUND_H__
#include "GAME_ERROR.h"
#include "cards.h"
#include "deck.h"
#include "game.h"
#include "player.h"

typedef struct Round Round;



/*
Description: check the given scoreboard for losers
Input: pointer to the scoreboard, number of players.
Output:GAME_OVER if one of the players got 100 points or more.
Errors:POINTER_NOT_INITIALIZED
*/
GAME_ERRORS ScoreRuleFunc(int* _scoreBoard, int _numOfPlayers);


/*
Description: create a round for given players.
Input: pointer to the players array, number of player, pointer to game scoreboard.
Output: pointer to round or NULL.
Errors: NULL if given pointers null, num of players is 0, or problems allocating memory.
*/
Round* RoundCreate(Player **_playersArray, size_t _numOfPlayers, int *_gameScoreboard);


/*
Description: run the round until the stop rule is met - one of players get more than 100 points.
Input: pointer to the round.
Output: GAME_OVER.
Errors: POINTER_NOT_INITIALIZED.
*/
GAME_ERRORS RoundRun(Round* _roundPtr);



/*
Description: Destroy the given round.
Input: pointer to the round. 
Output: None.
Errors: Will not destroy if given pointer is not initialized.
*/
void RoundDestroy(Round* _roundPtr);





#endif