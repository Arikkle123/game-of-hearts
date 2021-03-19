#ifndef __HEARTROUND_H__
#define __HEARTROUND_H__
#include "GAME_ERROR.h"
#include "cards.h"
#include "deck.h"
#include "game.h"
#include "player.h"

typedef struct Round Round;


Round* RoundCreate(Player **_playersArray, size_t _numOfPlayers, int *_gameScoreboard);

GAME_ERRORS RoundRun(Round* _roundPtr);

GAME_ERRORS _scoreRuleFunc(int* _scoreBoard, int _numOfPlayers);

void RoundDestroy(Round* _roundPtr);





#endif