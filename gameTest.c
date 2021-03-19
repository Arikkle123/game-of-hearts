#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"

GAME_ERRORS (*_scoreRuleFuncPtr)(int* _scoreBoard, int _numOfPlayers) = &_scoreRuleFunc;


void GameCreateWith0CompAndHumanPlayer();
void GameCreateWithoutScoreRuleFunc();
void GameCreateWithNullHumanName();
void GameCreateTest1();

void GameRunNotInitiliazedGameTest();
void GameRunTest1();


int main(void)
{
    GameCreateWith0CompAndHumanPlayer();
    GameCreateWithoutScoreRuleFunc();
    GameCreateWithNullHumanName();
    GameCreateTest1();
    putchar('\n');

    GameRunNotInitiliazedGameTest();
    GameRunTest1();
}





/***************************************** Game create Test ************************************************/

Game* GameCreate(size_t _numOfHumanPlayers, size_t _numOfComputerPlayers, GAME_ERRORS(*_scoreRuleFunc)(int* _scoreBoard, int _numOfPlayers) , char **_humanPlayerNameArray);


void GameCreateWith0CompAndHumanPlayer()
{
    char **nameArr = malloc(sizeof(char*) * 4);
    char name1[] = "Ariel";
    char name2[] = "Adi";
    char name3[] = "yoni";
    nameArr[0] = name1;
    nameArr[1] = name2;
    nameArr[2] = name3;
    Game *gamePtr;
    if( GameCreate(0, 0, _scoreRuleFuncPtr, nameArr) == NULL)
    {
        printf("Game create with 0 players test PASS!\n");
    }
    else
    {
        printf("Game create with 0 players test FAIL!\n");
    }
    free(nameArr);
}

void GameCreateWithoutScoreRuleFunc()
{
    char **nameArr = malloc(sizeof(char*) * 4);
    char name1[6] = "Ariel";
    char name2[6] = "Adi";
    char name3[6] = "yoni";
    nameArr[0] = name1;
    nameArr[1] = name2;
    nameArr[2] = name3;
    Game *gamePtr;
    if( GameCreate(1, 3, NULL, nameArr) == NULL)
    {
        printf("Game create without score rule function test PASS!\n");
    }
    else
    {
        printf("Game create without score rule function test FAIL!\n");
    }
    free(nameArr);
}

void GameCreateWithNullHumanName()
{
    Game *gamePtr;
    if( GameCreate(1, 3, _scoreRuleFuncPtr, NULL) == NULL)
    {
        printf("Game create NULL human name test PASS!\n");
    }
    else
    {
        printf("Game create NULL human name test FAIL!\n");
    }
}
void GameCreateTest1()
{
    size_t i;
    char **nameArr = malloc(sizeof(char*) * 4);
    char name1[] = "Ariel";
    char name2[] = "Adi";
    char name3[] = "yoni";
    nameArr[0] = name1;
    nameArr[1] = name2;
    nameArr[2] = name3;
    
    Game *gamePtr = GameCreate(1, 3, _scoreRuleFuncPtr, nameArr);
    int getRoundNum, *getScoreBoardPtr, getNumOfPlayers;
    Player **getPlayersArray;
    size_t checkIndex, scoreBoardCheckFlag = 0, playersArrayFlag = 0;
    

    getRoundNum = GameGetRoundNumber(gamePtr);
    getScoreBoardPtr = GameGetScoreboard(gamePtr);
    getNumOfPlayers = GameGetNumOfPlayers(gamePtr);
    getPlayersArray = GameGetPlayers(gamePtr);

    for(i = 0; i < getNumOfPlayers; i++)
    {
        if(getScoreBoardPtr[i] != 0)
        {
            scoreBoardCheckFlag = 1;
        }
        if(getPlayersArray[i] == NULL)
        {
            playersArrayFlag = 1;
        }
    }
    GamePrintPlayersNameAndScore(gamePtr);

    if( getRoundNum == 0 && scoreBoardCheckFlag == 0 && playersArrayFlag == 0 && getNumOfPlayers == 4)
    {
        printf("Game create test 1 PASS!\n");
    }
    else
    {
        printf("Game create test 1 FAIL!\n");
    }
    GameDestroy(gamePtr);
    free(nameArr);
}





/***************************************** Game Run Tests ************************************************/




void GameRunNotInitiliazedGameTest()
{
    Game* gamePtr = NULL;
    GAME_ERRORS testRoundFunction1(Game* _gamePtr)
    {
        return 1;
    }
    if( GameRun(gamePtr) == POINTER_NOT_INITIALIZED)
    {
        printf("Game run with no initialized game test PASS!\n");
    }
    else
    {
        printf("Game run with no initialized game test FAIL!\n");
    }
}


void GameRunTest1()
{
    char **nameArr = malloc(sizeof(char*) * 4);
    char name1[] = "Ariel";
    char name2[] = "Adi";
    char name3[] = "yoni";
    nameArr[0] = name1;
    nameArr[1] = name2;
    nameArr[2] = name3;
    Game *gamePtr = GameCreate(1, 3, _scoreRuleFuncPtr, nameArr);
    if(GameRun(gamePtr) == GAME_OVER)
    {
        printf("Game run test 1 PASS!\n");
    }
    else
    {
        printf("Game run test 1 FAIL!\n");
    }
    GameDestroy(gamePtr);
    free(nameArr);
}