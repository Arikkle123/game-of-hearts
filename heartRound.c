#include <stdlib.h>
#include "GAME_ERROR.h"
#include "heartRound.h"
#include "ui.h"

#define MAGIC 4561778
#define TRICK_NUM 13
#define NUM_OF_DECKS 1
#define START_CARD_AMOUNT 13
#define HEART_BROKEN 8971

struct Round{
    Player **m_players;
    size_t m_numOfPlayers;
    int *m_roundScoreArr;
    int *m_gameScoreboard;
    int m_trickCnt;
    size_t m_currentRoundNumber; /* Needed to decide who to pass the 3 cards to in the start of the round */
    int m_heartBrokenFlag;
    int m_magicNum;
};

typedef struct Table{
    CARD *m_table;
    CARD_SUITS m_leadingSuite;
    size_t m_numOfCards;
    int m_heartBrokenFlag;
    size_t m_startingPlayer;
    size_t m_numOfPlayers;
} Table;

void TableShow1(Round *_roundPtr, Table *_cardTable);

/*
TODO:

2 - comp strategy
*/



Table* TableCreate(size_t _numOfPlayers, int _heartBrokenFlag);
size_t TableFindLoser(Table* _table);
GAME_ERRORS TableAddCard(Table* _table, CARD _card, size_t _playerIndex);
size_t TablePenaltyPoints(Table* _table);
void TableDestroy(Table* _table);

GAME_ERRORS ScoreRuleFunc(int* _scoreBoard, int _numOfPlayers); /* Rule to stop game*/

static void DealCards(Player **_playersArray, size_t _numOfPlayers); /*Creates deck and distributes the cards to the players (than destroy the empty deck) */

/* Pass 3 cards in the beginning of each round */
static void PassStarting3Cards(Player **_playersArray, size_t _numOfPlayers, size_t _currentRoundNumber);
static void Pass3Cards(Player *_player, CARD *_cardInput);
static void Get3CardInput(Player *_player, CARD *_cardOutput);
static void GetHuman3CardsInput(Player *_player, CARD *_cardOutput);
static void GetComputer3CardsInputs(Player *_player, CARD *_cardOutput);


GAME_ERRORS TrickRun(Round* _roundPtr, size_t _startPlayer, size_t *_losingPlayer);
static void GetPlayerInput(Table* _currentTable, Player* _currentPlayer, size_t _tableIndex);
static void GetComputerInput(Table* _currentTable, Player* _currentPlayer, size_t _tableIndex);
static void GetHumanInput(Table* _currentTable, Player* _currentPlayer, size_t _tableIndex);
GAME_ERRORS HumanInputCheck(Table* _currentTable, CARD _inputCard, Player *_currentPlayer);

GAME_ERRORS CheckTableForHeartsAndSpadeQueen(Table* _currentTable);
GAME_ERRORS FindLowestNoneHeartCard(CARD *_hand, size_t _numOfCardsInHand, size_t *_indexOutput);
GAME_ERRORS FindLowestCard(CARD *_hand, size_t _numOfCardsInHand, size_t *_indexOutput);
GAME_ERRORS FindHighestCardOrQueenOfSpades(CARD *_hand, size_t _numOfCardsInHand, size_t *_indexOutput);
GAME_ERRORS FindHighestCard(CARD *_hand, size_t _numOfCardsInHand, size_t *_indexOutput);

size_t FindStartingPlayer(Player **_playersArray, size_t _numOfPlayers);   /*    return the index of the player that holds 2 clubs               */
static void SendRoundScoreToGameScoreboard(Round* _roundPtr);   /*      append the current round's score to the game scoreboard           */

void ShowCurrentScoreboardState(Round* _roundPtr);
void TableShow(Table* _table, Round* _gameRound);
void ShowDeclareLosers(Round* _roundPtr);

/*******************************************************/



GAME_ERRORS ScoreRuleFunc(int* _scoreBoard, int _numOfPlayers)
{
    size_t i;
    if(_scoreBoard == NULL || _numOfPlayers == 0)
    {
        return POINTER_NOT_INITIALIZED;
    }
    for(i = 0; i < _numOfPlayers; i++)
    {
        if(_scoreBoard[i] >= 100)
        {
            return GAME_OVER;
        }
    }
}


Round* RoundCreate(Player **_playersArray, size_t _numOfPlayers, int *_gameScoreboard)
{
    Round* roundOfHearts;
    if(_playersArray == NULL || _numOfPlayers != 4 || _gameScoreboard == NULL)
    {
        return NULL;
    }
    roundOfHearts = malloc(sizeof(Round));
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
    roundOfHearts->m_heartBrokenFlag = 0;
    return roundOfHearts;
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




/*************************************************** GAME RUN ***********************************************/

GAME_ERRORS RoundRun(Round* _roundPtr)
{
    size_t startPlayer, losingPlayer, i;
    char playerName[15];
    if(_roundPtr == NULL || _roundPtr->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    DealCards(_roundPtr->m_players, _roundPtr->m_numOfPlayers); 
    PassStarting3Cards(_roundPtr->m_players, _roundPtr->m_numOfPlayers, _roundPtr->m_currentRoundNumber); 
    startPlayer = FindStartingPlayer(_roundPtr->m_players, _roundPtr->m_numOfPlayers);  

    _roundPtr->m_trickCnt = 0;
    _roundPtr->m_heartBrokenFlag = 0; 
    ShowDeclareNewRound(_roundPtr->m_currentRoundNumber + 1);
    while(_roundPtr->m_trickCnt < 13)   
    {
        ShowTrickNumber(_roundPtr->m_trickCnt + 1);
        PlayerGetName(_roundPtr->m_players[startPlayer], playerName);
        ShowStartingPlayer(playerName);
        TrickRun(_roundPtr, startPlayer, &losingPlayer);
        (_roundPtr->m_trickCnt)++;
        startPlayer = losingPlayer;
    }    

    SendRoundScoreToGameScoreboard(_roundPtr); 
    ShowDeclareLosers(_roundPtr);
    return GAME_OVER;
}


GAME_ERRORS TrickRun(Round* _roundPtr, size_t _startPlayer, size_t *_losingPlayer)
{
    size_t currentPlayer = _startPlayer;
    PLAYER_TYPE currentPlayerType;
    CARD tempCardHolder;
    char playerName[15];
    Table *cardTable = TableCreate(_roundPtr->m_numOfPlayers, _roundPtr->m_heartBrokenFlag);

    if(_roundPtr->m_trickCnt == 0) /* First trick starts with 2 clubs */
    {
        PlayerTakeCardByCardType(_roundPtr->m_players[_startPlayer], &tempCardHolder, club_2);
        TableAddCard(cardTable, tempCardHolder, _startPlayer);
        currentPlayer = (currentPlayer + 1) % _roundPtr->m_numOfPlayers;
    }

    do{
        PlayerGetIdentity(_roundPtr->m_players[currentPlayer], &currentPlayerType);
        if(currentPlayerType == HUMAN_PLAYER)
        {
            /*TableShow(cardTable, _roundPtr);*/
            TableShow1(_roundPtr, cardTable);
        }        
        GetPlayerInput(cardTable, _roundPtr->m_players[currentPlayer], currentPlayer);
        currentPlayer = (currentPlayer + 1) % _roundPtr->m_numOfPlayers;
    } while (currentPlayer != _startPlayer);
    /*TableShow(cardTable, _roundPtr);*/
    TableShow1(_roundPtr, cardTable);
    *_losingPlayer = TableFindLoser(cardTable);
    _roundPtr->m_roundScoreArr[(*_losingPlayer)] = TablePenaltyPoints(cardTable);

    PlayerGetName(_roundPtr->m_players[(*_losingPlayer)], playerName);
    ShowTrickLoser(playerName, TablePenaltyPoints(cardTable));
    
    _roundPtr->m_heartBrokenFlag = cardTable->m_heartBrokenFlag;
    TableDestroy(cardTable);  
    
}


static void GetPlayerInput(Table* _currentTable, Player* _currentPlayer, size_t _tableIndex)
{
    PLAYER_TYPE identity;
    PlayerGetIdentity(_currentPlayer, &identity);
    if(identity == COMPUTER_PLAYER)
    {
        GetComputerInput(_currentTable, _currentPlayer, _tableIndex);
    }
    else if(identity == HUMAN_PLAYER)
    {
        GetHumanInput(_currentTable, _currentPlayer, _tableIndex);
    }
}


static void GetHumanInput(Table* _currentTable, Player* _currentPlayer, size_t _tableIndex)
{
    int cardChoiceNumber;
    size_t numOfCardsInHand;
    CARD tempCardHolder, cardForSuiteCheck;
    GAME_ERRORS checkForSuiteFlag;
    PlayerGetNumOfCards(_currentPlayer, &numOfCardsInHand);
    
    PlayerPrintHand(_currentPlayer);
    ShowGetPlayerChoice(&cardChoiceNumber, numOfCardsInHand);
    PlayerGetCardByIndex(_currentPlayer, cardChoiceNumber - 1, &tempCardHolder);
    
    while(HumanInputCheck(_currentTable, tempCardHolder, _currentPlayer) != OK)
    {
        ShowInvalidCardError();
        ShowGetPlayerChoice(&cardChoiceNumber, numOfCardsInHand);
        PlayerGetCardByIndex(_currentPlayer, cardChoiceNumber - 1, &tempCardHolder);
    }

    PlayerTakeCardByIndex(_currentPlayer, &tempCardHolder, cardChoiceNumber - 1);
    TableAddCard(_currentTable, tempCardHolder, _tableIndex);
}

GAME_ERRORS HumanInputCheck(Table* _currentTable, CARD _inputCard, Player *_currentPlayer)
{
    if(_currentTable->m_heartBrokenFlag != HEART_BROKEN && CARD_SUITE(_inputCard) == HEARTS)   
    {
        if(CheckHandForAllHearts(_currentPlayer) == TRUE)
        {
            return OK;
        }
        return ILLEGAL_CARD;
    }
    if(_currentTable->m_leadingSuite != NONE_SUIT && CARD_SUITE(_inputCard) != _currentTable->m_leadingSuite)
    {
        if( PlayerCheckHandForSuite(_currentPlayer, _currentTable->m_leadingSuite) == NOT_FOUND)
        {
            return OK;
        }
        return ILLEGAL_CARD;
    }
    return OK;
}

static void GetComputerInput(Table* _currentTable, Player* _currentPlayer, size_t _tableIndex)
{
    CARD cardHolder;
    if(_currentTable->m_numOfCards == 0) /*  First Card of the table */
    {
        if(_currentTable->m_heartBrokenFlag != HEART_BROKEN)
        {
            if(PlayerTakeCardByRuleFunction(_currentPlayer, &cardHolder, FindLowestNoneHeartCard) != OK)
            {
                PlayerTakeCardByRuleFunction(_currentPlayer, &cardHolder, FindLowestCard);
            }
        }
        else
        {
            PlayerTakeCardByRuleFunction(_currentPlayer, &cardHolder, FindLowestCard);
        }
    }
    else  /* Not first card  */
    {
        
        if( PlayerGetMinCardBySuite(_currentPlayer, &cardHolder, _currentTable->m_leadingSuite) == OK ) /* if existing card for suite found*/
        {
            if(_currentTable->m_numOfCards == 3) /*if putting the last card on table  */
            {
                if(CheckTableForHeartsAndSpadeQueen(_currentTable) == NOT_FOUND) /* Check to put highest card */
                {
                    PlayerGetMaxCardBySuite(_currentPlayer, &cardHolder, _currentTable->m_leadingSuite);
                }
            }
            PlayerTakeCardByCardType(_currentPlayer, &cardHolder, cardHolder);
        }
        else
        {
            PlayerTakeCardByRuleFunction(_currentPlayer, &cardHolder, FindHighestCardOrQueenOfSpades);
        }
    }
    TableAddCard(_currentTable, cardHolder, _tableIndex);
}


/*************************************** Computer strategy help functions ***********************************************/


GAME_ERRORS CheckTableForHeartsAndSpadeQueen(Table* _currentTable)
{
    size_t i;
    for(i = 0; i < _currentTable->m_numOfCards; i++)
    {
        if( _currentTable->m_table[(i + _currentTable->m_startingPlayer) % _currentTable->m_numOfPlayers] == spade_Q)
        {
            return FOUND;
        }
        if(CARD_SUITE(_currentTable->m_table[(i + _currentTable->m_startingPlayer) % _currentTable->m_numOfPlayers]) == HEARTS)
        {
            return FOUND;
        }
        
    }
    return NOT_FOUND;
}

GAME_ERRORS FindLowestNoneHeartCard(CARD *_hand, size_t _numOfCardsInHand, size_t *_indexOutput)
{
    int i = 0, tempCardIndex;
    while( CARD_SUITE( _hand[i]) == HEARTS) /* Check if all hearts or skips heart cards */
    {
        i++;
        if(i >= _numOfCardsInHand)
        {
            return CARD_NOT_FOUND;
        }
    }
    tempCardIndex = i; /* current card is not hearts - already checked */
    while(i < _numOfCardsInHand)
    {
        if(CARD_RANK(_hand[i]) < CARD_RANK(_hand[tempCardIndex])  && CARD_SUITE(_hand[i]) != HEARTS)
        {
            tempCardIndex = i;
        }
        i++;
    }
    *_indexOutput = tempCardIndex;
    return OK;
}


GAME_ERRORS FindLowestCard(CARD *_hand, size_t _numOfCardsInHand, size_t *_indexOutput)
{
    int i, tempCardIndex = 0;
    if(_numOfCardsInHand == 0)
    {
        return EMPTY_HAND;
    }
    for(i = 1; i < _numOfCardsInHand; i++)
    {
        if(CARD_RANK(_hand[i]) < CARD_RANK(_hand[tempCardIndex]))
        {
            tempCardIndex = i;
        }
    }
    *_indexOutput = tempCardIndex;
    return OK;
}

GAME_ERRORS FindHighestCardOrQueenOfSpades(CARD *_hand, size_t _numOfCardsInHand, size_t *_indexOutput)
{
    int i, tempCardIndex = 0;
    if(_hand[tempCardIndex] == spade_Q)
    {
        *_indexOutput = tempCardIndex;
    }
    for(i = 1; i < _numOfCardsInHand; i++)
    {
        if(_hand[i] == spade_Q)
        {
            *_indexOutput = i;
        }
        if(CARD_RANK(_hand[i]) > CARD_RANK(_hand[tempCardIndex]))
        {
            tempCardIndex = i;
        }
    }
    *_indexOutput = tempCardIndex;
    return OK;
}
GAME_ERRORS FindHighestCard(CARD *_hand, size_t _numOfCardsInHand, size_t *_indexOutput)
{
    int i, tempCardIndex = _numOfCardsInHand - 1;
    if(_numOfCardsInHand == 0)
    {
        return EMPTY_HAND;
    }
    for(i = _numOfCardsInHand - 2; i >= 0; i--)
    {
        if(CARD_RANK(_hand[i]) > CARD_RANK(_hand[tempCardIndex]))
        {
            tempCardIndex = i;
        }
    }
    *_indexOutput = tempCardIndex;
    return OK;
}


/***************************************************************************************************************************/

/*  Helper Functions */

size_t FindStartingPlayer(Player **_playersArray, size_t _numOfPlayers)   /*    return the index of the player that holds 2 clubs               */
{
    size_t i;
    for(i = 0; i < _numOfPlayers; i++)
    {
        if (PlayerCardIsFound(_playersArray[i], club_2) == CARD_FOUND)
        {
            return i;
        }
    }
}




static void SendRoundScoreToGameScoreboard(Round* _roundPtr)   /*      append the current round's score to the game scoreboard           */
{
    size_t i;
    for(i = 0; i < _roundPtr->m_numOfPlayers; i++)
    {
        _roundPtr->m_gameScoreboard[i] +=_roundPtr->m_roundScoreArr[i];
    }
}


static void DealCards(Player **_playersArray, size_t _numOfPlayers) /*V*/
{
    Deck* newDeck;
    size_t playerIndex, cardIndex;
    CARD cardHolder;
    newDeck = DeckCreate(NUM_OF_DECKS);
    DeckShuffle(newDeck);
    for(playerIndex = 0; playerIndex < _numOfPlayers; playerIndex++)
    {
        for(cardIndex = 0; cardIndex < (NUM_OF_DECKS * NUM_OF_CARDS / _numOfPlayers); cardIndex++)
        {
            DeckCardDisribute(newDeck, &cardHolder);
            PlayerGiveCard(_playersArray[playerIndex], cardHolder);
        }
        PlayerSortHand(_playersArray[playerIndex]);
    }
    DeckDestroy(newDeck);
}

/*************************************************************************************************************/




/************************************ Table Functions **********************************************/

Table* TableCreate(size_t _numOfPlayers, int _heartBrokenFlag)
{
    Table* newTableStruct = malloc(sizeof(Table));
    int i;
    if(newTableStruct == NULL)
    {
        return NULL;
    }
    newTableStruct->m_table = malloc(sizeof(CARD) * _numOfPlayers);
    if(newTableStruct->m_table == NULL)
    {
        free(newTableStruct);
        return NULL;
    }
    for(i = 0; i < _numOfPlayers; i++)
    {
        newTableStruct->m_table[i] = NONE_CARD;
    }
    newTableStruct->m_leadingSuite = NONE_SUIT;
    newTableStruct->m_numOfCards = 0;
    newTableStruct->m_heartBrokenFlag = 0;
    newTableStruct->m_numOfPlayers = _numOfPlayers;
    newTableStruct->m_heartBrokenFlag = _heartBrokenFlag;
    return newTableStruct;    
}

size_t TableFindLoser(Table* _table)
{
    size_t currentPlayer, tempLoser = _table->m_startingPlayer;
    for(currentPlayer = (_table->m_startingPlayer + 1) % _table->m_numOfPlayers; currentPlayer != _table->m_startingPlayer; currentPlayer = (currentPlayer + 1) % _table->m_numOfPlayers)
    {
        if(CARD_SUITE (_table->m_table[currentPlayer]) == _table->m_leadingSuite && CARD_RANK (_table->m_table[currentPlayer]) > CARD_RANK (_table->m_table[tempLoser]) )
        {
            tempLoser = currentPlayer;
        }
    }
    return tempLoser;
}

GAME_ERRORS TableAddCard(Table* _table, CARD _card, size_t _playerIndex)
{
    _table->m_table[_playerIndex] = _card;
    if(_table->m_numOfCards == 0)
    {
        _table->m_startingPlayer = _playerIndex;
        _table->m_leadingSuite = CARD_SUITE(_card);
    }
    if(CARD_SUITE(_card) == HEARTS)
    {
        _table->m_heartBrokenFlag = HEART_BROKEN;
    }
    _table->m_numOfCards +=1 ;
}


size_t TablePenaltyPoints(Table* _table)
{
    size_t i, score = 0;
    for(i = 0; i < _table->m_numOfCards; i++)
    {
        if(_table->m_table[i] == spade_Q)
        {
            score += 13;
        }
        else if( CARD_SUITE(_table->m_table[i])  == HEARTS)
        {
            score++;
        }
    }
    return score;
}


void TableDestroy(Table* _table)
{
    if(_table == NULL)
    {
        return;
    }
    free(_table->m_table);
    free(_table);
}



/* Table UI functions */

void TableShow(Table* _table, Round* _gameRound)
{
    int i;
    char name[15];
    ShowLeadingSuite(_table->m_leadingSuite);
    for(i = 0; i < _table->m_numOfCards; i++)
    {
        PlayerGetName(_gameRound->m_players[(_table->m_startingPlayer + i) % _table->m_numOfPlayers], name);
        ShowPlayerTableCard(name, _table->m_table[(_table->m_startingPlayer + i) % _table->m_numOfPlayers]);
    }
}

/*************************************************************************************************************/










/************************************ PASS STARTING 3 CARDS **********************************************/

static void PassStarting3Cards(Player **_playersArray, size_t _numOfPlayers, size_t _currentRoundNumber)
{
    size_t i, step = 0;
    CARD *cardArray;
    if((_currentRoundNumber + 1) % 4 == 0) /* every fourth round do not pass! */
    {
        return;
    }
    cardArray = malloc(sizeof(CARD) * 3 * _numOfPlayers);
    for(i = 0; i < _numOfPlayers; i++)
    {
        Get3CardInput(_playersArray[i], cardArray + (i * 3));
    }
    switch ((_currentRoundNumber + 1) % 4)
    {
    case 1:
        step = 1; /* pass to the next player */
        break;
    case 2:
        step = 3; /* pass to the prev player  */
        break;
    case 3: /*  pass to the player in front - jump by 2  */
        step = 2;
        break;
    }
    for(i = 0; i < _numOfPlayers; i++)
    {
        Pass3Cards(_playersArray[(i + step) % _numOfPlayers], &cardArray[i * 3]);
        PlayerSortHand(_playersArray[(i + step) % _numOfPlayers]);
    }
    free(cardArray);
}





static void Pass3Cards(Player *_player, CARD *_cardInput)
{
    size_t i;
    for(i = 0; i < 3; i++)
    {
        PlayerGiveCard(_player, _cardInput[i]);
    }
}


static void Get3CardInput(Player *_player, CARD *_cardOutput)
{    
    PLAYER_TYPE identity;
    PlayerGetIdentity(_player, &identity);    
    if(identity == HUMAN_PLAYER)
    {
        GetHuman3CardsInput(_player, _cardOutput);
    }
    else if(identity == COMPUTER_PLAYER)
    {
        GetComputer3CardsInputs(_player, _cardOutput);
    }    
}



static void GetHuman3CardsInput(Player *_player, CARD *_cardOutput)
{
    int cardOutputIndex = 0, cardNumOfChoice;
    size_t numOfCards = START_CARD_AMOUNT;
    CARD playersHand[START_CARD_AMOUNT]; 
    while (cardOutputIndex < 3)
    {
        ShowDeclareCardPass();
        PlayerPrintHand(_player);
        ShowGetPlayerChoice(&cardNumOfChoice, numOfCards);
        PlayerTakeCardByIndex(_player, &_cardOutput[cardOutputIndex], cardNumOfChoice - 1);
        cardOutputIndex++; 
        numOfCards--;
    }
}

static void GetComputer3CardsInputs(Player *_player, CARD *_cardOutput)   /*  Goes by the highest cards  */
{
    size_t cardCnt = 0, numOfCards = START_CARD_AMOUNT;
    while(cardCnt != 3)
    {
        PlayerTakeCardByRuleFunction(_player, &_cardOutput[cardCnt], FindHighestCard);
        numOfCards--;
        cardCnt++;
    }
}



/****************************************************************************************************************/


/* UI Functions */

void ShowCurrentScoreboardState(Round* _roundPtr)
{
    size_t i;
    char name[15];
    for(i = 0; i < _roundPtr->m_numOfPlayers; i++)
    {
        PlayerGetName(_roundPtr->m_players[i], name);
        ShowPlayerScoreState(name, _roundPtr->m_gameScoreboard[i]);
    }
} 



void ShowDeclareLosers(Round* _roundPtr)
{
    size_t i;
    char name[15];
    for(i = 0; i < _roundPtr->m_numOfPlayers; i++)
    {
        if(_roundPtr->m_gameScoreboard[i] >= 100)
        {
            PlayerGetName(_roundPtr->m_players[i], name);
            ShowGameLoser(name, _roundPtr->m_gameScoreboard[i]);
        }
    }
}


void TableShow1(Round *_roundPtr, Table *_cardTable)
{
    size_t i;
    char *names[4];
    CARD cards[4];
    for(i = 0; i < _cardTable->m_numOfPlayers; i++)
    {
        names[i] = malloc(sizeof(char) * 6);
        PlayerGetName(_roundPtr->m_players[i], names[i]);
        cards[i] = _cardTable->m_table[i];
    }
    ShowTable(_cardTable->m_leadingSuite, names, cards);
    for(i = 0; i < _cardTable->m_numOfPlayers; i++)
    {
        free(names[i]);
    }
}