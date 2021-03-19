#ifndef GAME_H
#define GAME_H

#include "GAME_ERROR.h"
#include "player.h"
#include "cards.h"
#include "heartRound.h"

/*#include "roundForGameTest.h"*/

typedef struct Game Game;

/* Round* RoundCreate(Player **_playersArray, size_t _numOfPlayers, size_t _currentRoundNum, int *_gameScoreboard); */

/*
Description: Creates a game with
Inputs: Number of computer players in the game, pointer to the game score rule function, pointer to the name of the human player.
Outputs: Pointer to the game or NULL.
Errors: NULL if give number of computer players is 0 OR given score rule function pointer is NULL OR given human player name pointer is null or empty string OR failed to allocate memory for every aspect of the game.
*/
Game* GameCreate(size_t _numOfHumanPlayers, size_t _numOfComputerPlayers, GAME_ERRORS(*_scoreRuleFunc)(int* _scoreBoard, int _numOfPlayers) , char **_humanPlayerNameArray);
/*
Description: Runs a given game until the Game end rule met.
Inputs: Pointer to the game.
Outputs: GAME_OVER, POINTER_NOT_INITIALIZED
Errors: POINTER_NOT_INITIALIZED if given pointer not initialized.
*/
GAME_ERRORS GameRun(Game* _gamePtr);


/*
Description: Destroy a given game.
Inputs: Pointer to the game.
Outputs: None.
Errors: Won't destroy if given pointer not initialized.
*/
void GameDestroy(Game* _gamePtr);





/*
Description: Get the current number of rounds played in a given game.
Inputs: Pointer to the game.
Outputs: Number of rounds.
Errors: -1 if given game not initialized.
*/
int GameGetRoundNumber(Game* _gamePtr);


/*
Description: Get the pointer to the scoreboard in a given game.
Inputs: Pointer to the game.
Outputs: pointer to the scoreboard.
Errors: NULL if given game not initialized.
*/
int *GameGetScoreboard(Game* _gamePtr);

/*
Description: Get the pointer to the scoreboard in a given game.
Inputs: Pointer to the game.
Outputs: number of player or -1.
Errors: -1 if given game not initialized.
*/
int GameGetNumOfPlayers(Game* _gamePtr);

/*
Description: Get the pointer to the array of players in the game.
Inputs: Pointer to the game.
Outputs: pointer to the array or NULL
Errors: NULL if given game not initialized.
*/
Player** GameGetPlayers(Game* _gamePtr);


/*
Description: Print a list of players and their current score in the game.
Inputs: Pointer to the game.
Outputs: None.
Errors: Will not print anything if pointer not initialized.
*/
void GameShowPlayersNameAndScore(Game* _gamePtr);


/*
Description: Print all players hands.
Inputs: Pointer to the game.
Outputs: None.
Errors: Will not print anything if pointer not initialized.
*/
void PrintPlayersHands(Game* _gamePtr);




#endif