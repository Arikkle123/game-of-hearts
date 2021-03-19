#include "heartRound.h"
#include <stdlib.h>

void GameRunTest1();




int main(void)
{
    GameRunTest1();
}

void GameRunTest1()
{
    Game *gamePtr;
    char **nameArr = malloc(sizeof(char*) * 4);
    char name1[] = "Ariel";
    char name2[] = "Adi";
    char name3[] = "yoni";
    nameArr[0] = name1;
    nameArr[1] = name2;
    nameArr[2] = name3;
    gamePtr = GameCreate(1, 3, ScoreRuleFunc, nameArr);
    GameRun(gamePtr);
    GameDestroy(gamePtr);
    free(nameArr);
}