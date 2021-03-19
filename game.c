#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "ui.h"

#define MAGIC 4617778

struct Game{
    size_t m_numOfHumanPlayers;
    size_t m_numOfComputerPlayers;
    int *m_scoreBoard;
    Player **m_players;
    size_t m_numOfRoundsPlayed;
    int m_magicNum;
    GAME_ERRORS(*m_scoreRuleFunc)(int* _scoreBoard, int _numOfPlayers);
    Round *m_gameRound;
};

char NAME_ARRAY[][6] = {"Alice", "Bob","Dylan", "Dana"};


/* HELPER */
Player** PlayerGenerator(size_t _numOfHumanPlayers, size_t _numOfComputerPlayers , char **_humanPlayerNameArray);
static void PlayerArrayDestroy(Player **_playersArray, size_t _numOfPlayers);
/************************************/






Game* GameCreate(size_t _numOfHumanPlayers, size_t _numOfComputerPlayers, GAME_ERRORS(*_scoreRuleFunc)(int* _scoreBoard, int _numOfPlayers) , char **_humanPlayerNameArray)
{
    Game* gamePtr;
    if( (_numOfComputerPlayers == 0 && _numOfHumanPlayers == 0) || (_numOfHumanPlayers > 0 && _humanPlayerNameArray == NULL) || _scoreRuleFunc == NULL)
    {
        return NULL;
    }

    gamePtr = malloc(sizeof(Game)); /*alloc game */
    if(gamePtr == NULL)
    {
        return NULL;
    }
    
    gamePtr->m_scoreBoard = calloc(sizeof(int), _numOfHumanPlayers + _numOfComputerPlayers); /* Keep score for each player */
    if(gamePtr->m_scoreBoard == NULL)
    {
        free(gamePtr);
        return NULL;
    }

    gamePtr->m_players = PlayerGenerator(_numOfHumanPlayers, _numOfComputerPlayers, _humanPlayerNameArray); /* Create players */
    if(gamePtr->m_players == NULL)
    {
        free(gamePtr->m_scoreBoard);
        free(gamePtr);
    }
    gamePtr->m_gameRound = RoundCreate(gamePtr->m_players, _numOfHumanPlayers + _numOfComputerPlayers, gamePtr->m_scoreBoard);
    if(gamePtr->m_gameRound == NULL)
    {
        free(gamePtr->m_scoreBoard);
        PlayerArrayDestroy(gamePtr->m_players, _numOfHumanPlayers + _numOfComputerPlayers);
        free(gamePtr);
    }

    gamePtr->m_numOfHumanPlayers = _numOfHumanPlayers;
    gamePtr->m_numOfComputerPlayers = _numOfComputerPlayers;     
    gamePtr->m_numOfRoundsPlayed = 0;
    gamePtr->m_magicNum = MAGIC;
    gamePtr->m_scoreRuleFunc = _scoreRuleFunc;
    return gamePtr;
}



void GameDestroy(Game* _gamePtr)
{
    size_t i;
    if(_gamePtr == NULL || _gamePtr->m_magicNum != MAGIC)
    {
        return;
    }
    free(_gamePtr->m_scoreBoard);
    PlayerArrayDestroy(_gamePtr->m_players, _gamePtr->m_numOfComputerPlayers + _gamePtr->m_numOfHumanPlayers);
    _gamePtr->m_magicNum = 0;
    RoundDestroy(_gamePtr->m_gameRound);
    free(_gamePtr);
}

GAME_ERRORS GameRun(Game* _gamePtr)
{
    GAME_ERRORS roundEndStatus = 0;
    if(_gamePtr == NULL || _gamePtr->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    ShowGameStartDeclaration();
    
    while( roundEndStatus != GAME_OVER)
    {
        RoundRun(_gamePtr->m_gameRound);
        (_gamePtr->m_numOfRoundsPlayed)++;
        roundEndStatus = _gamePtr->m_scoreRuleFunc(_gamePtr->m_scoreBoard, _gamePtr->m_numOfHumanPlayers + _gamePtr->m_numOfComputerPlayers);
        GameShowPlayersNameAndScore(_gamePtr);
    }
    

    return GAME_OVER;
}



/*  GET FUNCTIONS */
int GameGetRoundNumber(Game* _gamePtr)
{
    if(_gamePtr == NULL || _gamePtr->m_magicNum != MAGIC)
    {
        return -1;
    }
    return _gamePtr->m_numOfRoundsPlayed;
}

int *GameGetScoreboard(Game* _gamePtr)
{
    if(_gamePtr == NULL || _gamePtr->m_magicNum != MAGIC)
    {
        return NULL;
    }
    return _gamePtr->m_scoreBoard;
}

int GameGetNumOfPlayers(Game* _gamePtr)
{
    if(_gamePtr == NULL || _gamePtr->m_magicNum != MAGIC)
    {
        return -1;
    }
    return (int)(_gamePtr->m_numOfHumanPlayers + _gamePtr->m_numOfComputerPlayers);
}

Player** GameGetPlayers(Game* _gamePtr)
{
    if(_gamePtr == NULL || _gamePtr->m_magicNum != MAGIC)
    {
        return NULL;
    }
    return _gamePtr->m_players;
}



/*  UI Functions        */
void GameShowPlayersNameAndScore(Game* _gamePtr)
{
    size_t i;
    char name[15];
    if(_gamePtr == NULL || _gamePtr->m_magicNum != MAGIC)
    {
        return;
    }
    for(i = 0 ;i < (_gamePtr->m_numOfHumanPlayers + _gamePtr->m_numOfComputerPlayers); i++)
    {
        PlayerGetName(_gamePtr->m_players[i], name);
        ShowPlayerScoreState(name, _gamePtr->m_scoreBoard[i]);
    }
}

void PrintPlayersHands(Game* _gamePtr)
{
    size_t i;
    if(_gamePtr == NULL || _gamePtr->m_magicNum != MAGIC)
    {
        return;
    }
    for(i = 0; i < (_gamePtr->m_numOfHumanPlayers+ _gamePtr->m_numOfComputerPlayers); i++)
    {
        PlayerPrintHand(_gamePtr->m_players[i]);
    }

}



/*         HELPER      */
Player** PlayerGenerator(size_t _numOfHumanPlayers, size_t _numOfComputerPlayers , char **_humanPlayerNameArray)
{
    Player **playersArray, *playerPtr;
    size_t i;
    char name[10];
    playersArray = malloc(sizeof(Player*) * (_numOfHumanPlayers + _numOfComputerPlayers)); /* Array of pointers for the players */
    if(playersArray == NULL)
    {
        return NULL;
    } 

    for(i = 0; i < _numOfHumanPlayers; i++)  /* generate human players */
    {   
        strcpy(name, _humanPlayerNameArray[i]);
        playerPtr = PlayerCreate(name, HUMAN_PLAYER);
        if(playerPtr == NULL)   /* Self Destroy if one of the player generation failed */
        {
            if(i != 0)
            {
                for(i -= 1; i >= 0; i--)
                {
                    PlayerDestroy(playersArray[i]);
                }
            }            
            free(playersArray);
            return NULL;
        }
        playersArray[i] = playerPtr;
    }
    for(i = 0; i < _numOfComputerPlayers; i++)  /* generate computer players */
    {   
        strcpy(name, NAME_ARRAY[i]);
        playerPtr = PlayerCreate(name, COMPUTER_PLAYER);
        if(playerPtr == NULL)   /* Self Destroy if one of the player generation failed */
        { 
            if(i != 0)
            {
                for(i = (i - 1 + _numOfHumanPlayers); i >= 0; i--)
                {
                    PlayerDestroy(playersArray[i]);
                }
            }            
            free(playersArray);
            return NULL;
        }
        playersArray[i + _numOfHumanPlayers] = playerPtr;
    }
    return playersArray;
}

static void PlayerArrayDestroy(Player **_playersArray, size_t _numOfPlayers)
{
    size_t i;
    for(i = 0; i < _numOfPlayers; i++)
    {
        PlayerDestroy(_playersArray[i]);
    }
    free(_playersArray);
}