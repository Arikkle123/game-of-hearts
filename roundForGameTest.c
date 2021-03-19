#include <stdlib.h>
#include <stdio.h>
#include "GAME_ERROR.h"
#include "heartRound.h"

#define MAGIC 4561778
#define TRICK_NUM 13
#define NUM_OF_DECKS 1

struct Round{
    Player **m_players;
    size_t m_numOfPlayers;
    int *m_roundScoreArr;
    int *m_gameScoreboard;
    int m_trickCnt;
    size_t m_currentRoundNumber; /* Needed to decide who to pass the 3 cards to in the start of the round */
    int m_magicNum;
};


Round* RoundCreate(Player **_playersArray, size_t _numOfPlayers, int *_gameScoreboard)
{
    if(_playersArray == NULL || _numOfPlayers == 0 || _gameScoreboard == NULL)
    {
        return NULL;
    }
    Round* roundOfHearts = malloc(sizeof(Round));
    if(roundOfHearts == NULL)
    {
        return NULL;
    }
    roundOfHearts->m_roundScoreArr = calloc(sizeof(int), _numOfPlayers);
    if( roundOfHearts->m_roundScoreArr == NULL)
    {
        free(roundOfHearts);
        return NULL;
    }
    roundOfHearts->m_gameScoreboard = _gameScoreboard;
    roundOfHearts->m_players = _playersArray;
    roundOfHearts->m_numOfPlayers = _numOfPlayers;
    roundOfHearts->m_trickCnt = 0;
    roundOfHearts->m_currentRoundNumber = 0;
    roundOfHearts->m_magicNum = MAGIC;
    return roundOfHearts;
}



GAME_ERRORS RoundRun(Round* _roundPtr)
{
    if(_roundPtr == NULL || _roundPtr->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    printf("current Round:%d \n" , _roundPtr->m_currentRoundNumber);
    _roundPtr->m_gameScoreboard[0] += 2;
    _roundPtr->m_gameScoreboard[1] += 2;
    _roundPtr->m_gameScoreboard[2] += 3;
    _roundPtr->m_gameScoreboard[3] += 4;
    (_roundPtr->m_currentRoundNumber)++;
    
}

void RoundDestroy(Round* _roundPtr)
{
    if(_roundPtr == NULL || _roundPtr->m_magicNum != MAGIC)
    {
        return;
    }
    free(_roundPtr->m_roundScoreArr);
    free(_roundPtr);
}



GAME_ERRORS _scoreRuleFunc(int* _scoreBoard, int _numOfPlayers) /*       Score rule funtion for tests                */
{
    size_t i;
    for(i = 0; i < _numOfPlayers; i++)
    {
        if (_scoreBoard[i] >= 5)
        {
            return GAME_OVER;
        }
    }
}
