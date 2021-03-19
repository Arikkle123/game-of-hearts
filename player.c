#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "player.h"
#define MAGIC 4654712

#define PLAYER_MAX_CARDS_INITIALIZE 15
#define HAND_INCREASE_BLOCK 5

struct Player {
    char m_name[15];
    PLAYER_TYPE m_identity;
    CARD *m_hand;
    size_t m_maxNumOfCards; /* PLAYER_MAX_CARDS_INITIALIZE - dynamic */
    size_t m_currentNumOfCards;
    int m_magicNum;
} ;


/* HELPER FUNCTIONS */
void PlayerOrganizeHand(Player *_player, size_t _startIndex);
void SwapHandCards(CARD *_hand, size_t _index1, size_t _index2);
/* HELPER_END */



/* Player Main */
Player *PlayerCreate(char *_name, PLAYER_TYPE _identity)
{
    Player* player;
    CARD *hand;
    if(_name == NULL || strlen(_name) < 1 || !(_identity == HUMAN_PLAYER || _identity == COMPUTER_PLAYER))
    {
        return NULL;
    }

    player = malloc(sizeof(Player));
    if(player == NULL)
    {
        return NULL;
    }
    hand = malloc(sizeof(CARD) * PLAYER_MAX_CARDS_INITIALIZE);
    if(hand == NULL)
    {
        free(player);
        return NULL;
    }
    player->m_hand = hand;
    strcpy(player->m_name, _name);
    player->m_identity = _identity;
    player->m_maxNumOfCards = PLAYER_MAX_CARDS_INITIALIZE;
    player->m_magicNum = MAGIC;
    player->m_currentNumOfCards = 0;
    return player;
}


void PlayerDestroy(Player *_player)
{
    if(_player == NULL || _player->m_magicNum != MAGIC)
    {
        return;
    }
    free(_player->m_hand);
    _player->m_magicNum = 0;
    free(_player);
}

/*********************************************************************************************************************************/

/*  Player Card Functions */

GAME_ERRORS PlayerGiveCard(Player *_player, CARD _card)
{
    CARD* tempHand;
    if(_player == NULL || _player->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_card < 0 || _card >= NUM_OF_CARDS)
    {
        return ILLEGAL_CARD;
    }
    if(_player->m_currentNumOfCards == _player->m_maxNumOfCards)
    {
        tempHand = realloc(_player->m_hand, sizeof(CARD) * (_player->m_maxNumOfCards + HAND_INCREASE_BLOCK));
        if(tempHand == NULL)
        {
            return HAND_REALLOCATION_FAIL;
        }
        (_player->m_maxNumOfCards) += HAND_INCREASE_BLOCK;
        _player->m_hand = tempHand;
    }
    _player->m_hand[_player->m_currentNumOfCards] = _card;
    (_player->m_currentNumOfCards)++;
    return OK;
}

GAME_ERRORS PlayerTakeCardByRuleFunction(Player *_player, CARD *_cardOutput, GAME_ERRORS (*_cardFindIndexFunction)(CARD *_hand, size_t _numOfCardsInHand, size_t *_indexOutput))
{
    size_t cardToTakeI;
    if(_player == NULL || _player->m_magicNum != MAGIC || _cardOutput == NULL || _cardFindIndexFunction == NULL)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    if(_cardFindIndexFunction(_player->m_hand, _player->m_currentNumOfCards, &cardToTakeI) != OK)
    {
        return CARD_NOT_FOUND;
    }
    *_cardOutput = _player->m_hand[cardToTakeI];   
    PlayerOrganizeHand(_player, cardToTakeI);
    (_player->m_currentNumOfCards)--;
    return OK;
}



GAME_ERRORS PlayerTakeCardByIndex(Player *_player, CARD *_cardOutput, size_t _cardIndex)
{
    if(_player == NULL || _player->m_magicNum != MAGIC || _cardOutput == NULL)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    if(_cardIndex >= _player->m_currentNumOfCards)
    {
        return ILLEGAL_INDEX;
    }
    *_cardOutput = _player->m_hand[_cardIndex];    
    PlayerOrganizeHand(_player, _cardIndex);
    (_player->m_currentNumOfCards)--;
    return OK;
}

GAME_ERRORS PlayerTakeCardByCardType(Player *_player, CARD *_cardOutput, CARD _cardType)
{
    int i, cardIndex = -1;
    if(_player == NULL || _player->m_magicNum != MAGIC || _cardOutput == NULL)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_cardType > 51 || _cardType < 0)
    {
        return ILLEGAL_CARD;
    }
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    for(i = 0; i < _player->m_currentNumOfCards; i++)
    {
        if(_player->m_hand[i] == _cardType)
        {
            cardIndex = i;
        }
    }
    if(cardIndex == -1)
    {
        return CARD_NOT_FOUND;
    }
    *_cardOutput = _player->m_hand[cardIndex];    
    PlayerOrganizeHand(_player, cardIndex);
    (_player->m_currentNumOfCards)--;
    return OK;
}



GAME_ERRORS PlayerSortHand(Player *_player)
{
    int outIndex, inIndex, numOfCards;
    if(_player == NULL || _player->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }    
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    for(outIndex = _player->m_currentNumOfCards - 1; outIndex >= 0  ; outIndex--)
    {
        for(inIndex = 0; inIndex < outIndex; inIndex++)
        {
            if(_player->m_hand[inIndex] > _player->m_hand[inIndex + 1])
            {
                SwapHandCards(_player->m_hand, inIndex, inIndex + 1);
            }
        }
    }
    return OK;
}

/*********************************************************************************************************************************/



/* Player Check Functions  */

GAME_ERRORS PlayerCheckHandForSuite(Player *_player, CARD_SUITS _suite)
{
    size_t i;
    if(_player == NULL || _player->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if( _suite != SPADES && _suite != DIAMONDS && _suite != HEARTS && _suite != CLUBS)
    {
        return ILLEGAL_SUITE;
    }
    for(i = 0; i < _player->m_currentNumOfCards; i++)
    {
        if(CARD_SUITE(_player->m_hand[i]) == _suite)
        {
            return FOUND;
        }
    }
    return NOT_FOUND;
}


GAME_ERRORS PlayerHandIsEmpty(Player *_player)
{
    if(_player == NULL || _player->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }    
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    else{
        return HAND_NOT_EMPTY;
    }
}

GAME_ERRORS PlayerCardIsFound(Player *_player, CARD _card)
{
    size_t i;
    if(_player == NULL || _player->m_magicNum != MAGIC )
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(!(spade_A <= _card && _card < NUM_OF_CARDS))
    {
        return ILLEGAL_CARD;
    }
    for(i = 0; i < _player->m_currentNumOfCards; i++)
    {
        if(_player->m_hand[i] == _card)
        {
            return CARD_FOUND;
        }
    }
    return CARD_NOT_FOUND;
}


GAME_ERRORS CheckHandForAllHearts(Player *_player)
{
    size_t i;
    if(_player == NULL || _player->m_magicNum != MAGIC )
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    for(i = 0; i < _player->m_currentNumOfCards; i++)
    {
        if( CARD_SUITE( _player->m_hand[i]) != HEARTS)
        {
            return FALSE;
        }
    }
    return TRUE;
}


/*********************************************************************************************************************************/
/* UI FUNCTIONS  */


void PlayerPrintHand(Player *_player)
{
    size_t i;
    if(_player == NULL || _player->m_magicNum != MAGIC || _player->m_currentNumOfCards == 0)
    {
        return;
    }
    PrintGivenCards(_player->m_hand, _player->m_currentNumOfCards);
}

/*********************************************************************************************************************************/
/*  Player Get Cards Function */
GAME_ERRORS PlayerGetMinCard(Player *_player, CARD *_cardHolder)
{
    size_t i;
    CARD currentMin;
    if(_player == NULL || _player->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    currentMin = _player->m_hand[0];
    for(i = 1; i < _player->m_currentNumOfCards; i++)
    {
        if( (_player->m_hand[i] % CARDS_IN_SUITE) < (currentMin % CARDS_IN_SUITE) )
        {
            currentMin = _player->m_hand[i];
        }
    }
    *_cardHolder = currentMin;
    return OK;
}

GAME_ERRORS PlayerGetMinCardBySuite(Player *_player, CARD *_cardHolder, CARD_SUITS _cardSuite)
{
    int i = 0;
    CARD currentMin;
    if(_player == NULL || _player->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    while(CARD_SUITE(_player->m_hand[i]) != _cardSuite)
    {
        i++;
        if(i >= _player->m_currentNumOfCards)
        {
            return CARD_NOT_FOUND;
        }
    }
    currentMin =  _player->m_hand[i];
    for(;i < _player->m_currentNumOfCards; i++)
    {
        if( CARD_SUITE(_player->m_hand[i]) ==  _cardSuite && _player->m_hand[i] < currentMin)
        {
            currentMin = _player->m_hand[i];
        }
    }
    *_cardHolder = currentMin;
    return OK;
}

GAME_ERRORS PlayerGetMaxCardBySuite(Player *_player, CARD *_cardHolder, CARD_SUITS _cardSuite)
{
    int i = 0;
    CARD currentMax;
    if(_player == NULL || _player->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    while(CARD_SUITE(_player->m_hand[i]) != _cardSuite)
    {
        i++;
        if(i >= _player->m_currentNumOfCards)
        {
            return CARD_NOT_FOUND;
        }
    }
    currentMax =  _player->m_hand[i];
    for(;i < _player->m_currentNumOfCards; i++)
    {
        if( CARD_SUITE(_player->m_hand[i]) ==  _cardSuite && _player->m_hand[i] > currentMax)
        {
            currentMax = _player->m_hand[i];
        }
    }
    *_cardHolder = currentMax;
    return OK;
}

GAME_ERRORS PlayerGetMaxCard(Player *_player, CARD *_cardHolder)
{
    size_t i;
    CARD currentMax;
    if(_player == NULL || _player->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    currentMax = _player->m_hand[0];
    for(i = 1; i < _player->m_currentNumOfCards; i++)
    {
        if( (_player->m_hand[i] % CARDS_IN_SUITE) > (currentMax % CARDS_IN_SUITE) )
        {
            currentMax = _player->m_hand[i];
        }
    }
    *_cardHolder = currentMax;
    return OK;
}

GAME_ERRORS PlayerGetCardByIndex(Player *_player, size_t _cardIndex, CARD *_cardHolder)
{
    size_t i;
    if(_player == NULL || _player->m_magicNum != MAGIC)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }
    if(!(0 <= _cardIndex && _cardIndex < _player->m_currentNumOfCards))
    {
        return CARD_NOT_FOUND;
    }
    *_cardHolder = _player->m_hand[_cardIndex];
    return OK;
}
/*********************************************************************************************************************************/


/*Player Get Function  */

GAME_ERRORS PlayerGetName(Player *_player, char *_name)
{
    if(_player == NULL || _player->m_magicNum != MAGIC || _name == NULL)
    {
        return POINTER_NOT_INITIALIZED;
    }
    strcpy(_name, _player->m_name);
    return OK;
}


GAME_ERRORS PlayerGetIdentity(Player *_player, PLAYER_TYPE *_identity)
{
    if(_player == NULL || _player->m_magicNum != MAGIC || _identity == NULL)
    {
        return POINTER_NOT_INITIALIZED;
    }
    *_identity = _player->m_identity;
    return OK;
}

GAME_ERRORS PlayerGetHand(Player *_player, CARD **_hand)
{
    if(_player == NULL || _player->m_magicNum != MAGIC || _hand == NULL)
    {
        return POINTER_NOT_INITIALIZED;
    }
    *_hand = _player->m_hand;
    return OK;
}


GAME_ERRORS PlayerGetNumOfCards(Player *_player, size_t *_numOfCards)
{
    if(_player == NULL || _player->m_magicNum != MAGIC || _numOfCards == NULL)
    {
        return POINTER_NOT_INITIALIZED;
    }
    *_numOfCards = _player->m_currentNumOfCards;
    return OK;
}



GAME_ERRORS PlayerShowHand(Player *_player, CARD *_handOutput)
{
    size_t i;
    if(_player == NULL || _player->m_magicNum != MAGIC || _handOutput == NULL)
    {
        return POINTER_NOT_INITIALIZED;
    }
    if(_player->m_currentNumOfCards == 0)
    {
        return EMPTY_HAND;
    }    
    for(i = 0; i < _player->m_currentNumOfCards; i++)
    {
        _handOutput[i] = _player->m_hand[i];
    }
    return OK;
}







/* HELPER FUNCTIONS */

void PlayerOrganizeHand(Player *_player, size_t _startIndex)
{
    size_t i;
    for(i = _startIndex; (i + 1) < _player->m_currentNumOfCards; i++)
    {
        _player->m_hand[i] = _player->m_hand[i + 1];
    }
}

void SwapHandCards(CARD *_hand, size_t _index1, size_t _index2)
{
    CARD temp = _hand[_index1];
    _hand[_index1] = _hand[_index2];
    _hand[_index2] = temp;
}