#include <stdio.h> /* for Printing */
#include "ui.h"
#include "cards.h"

#define BOLD_ON "\x1b[1m"
#define BOLD_OFF "\x1b[21m"

/* cards suites symbols */
#define HEART_SYM "\xE2\x99\xA5"
#define SPADE_SYM "\xE2\x99\xA0"
#define DIAMOND_SYM "\xE2\x99\xA6"
#define CLUB_SYM "\xE2\x99\xA3"

/* colors */
#define NORMAL "\x1B[0m"
#define BLACK "\x1b[30m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define GRAY "\x1b[90m"


void ShowGameStartDeclaration()
{
    printf("\n**************************************************************************\n");
    printf("*                              %sGame Start!%s                               *", BOLD_ON, NORMAL);
    printf("\n**************************************************************************\n");
}


void ShowInvalidCardError()
{
    printf("Please choose a valid card!\n");
}


void ShowTrickNumber(size_t _num)
{
    printf("%s%s\n**********************************************************************\n", BOLD_ON, CYAN);
    printf("\t\t\t Trick Number: %ld \n", _num);
    printf("**********************************************************************%s\n", NORMAL);
    putchar('\n');
    putchar('\n');
}

void ShowDeclareNewRound(size_t _num)
{
    printf("%s%s\n*********************************************************************************************\n", BOLD_ON, BLUE);
    printf("\t\t\t\t ROUND NUMBER: %ld \n", _num);
    printf("*********************************************************************************************%s\n", NORMAL);
    putchar('\n');
    putchar('\n');
}

void ShowPlayersName(char *_name)
{
    printf("%s ", _name);
}

void ShowPlayerTableCard(char *_name, CARD _card)
{
    printf("%s's card is\t ", _name);
    PrintCard(_card);
    putchar('\n');
}


void ShowStartingPlayer(char *_name)
{
    printf("\t\tStarting Player is %s!\n", _name);
    printf("%s\t\t                       %s\n\n", BOLD_OFF, NORMAL);
}

void ShowTrickLoser(char *_name, size_t _currentScore)
{
    putchar('\n');
    printf("\t\t%s%s LOST this trick!%s\n", BOLD_ON, _name, NORMAL);
    if(_currentScore > 0)
    {
        printf("\t\t%s earned %s%s%ld%s penalty points.\n", _name, RED, BOLD_ON,  _currentScore, NORMAL);
    }
    else
    {
        printf("\t\t%s earned no penalty points.\n", _name);
    }
}

void ShowGameLoser(char *_name, size_t _currentScore)
{
    putchar('\n');
    printf("%s\n**************************************************************************\n", YELLOW);
    printf("               \t%s LOST this game!!       \n", _name);
    printf("               \t%s earned %ld penalty points. ", _name, _currentScore);
    printf("\n**************************************************************************%s\n", NORMAL);
}

void ShowPlayerScoreState(char *_name, size_t _currentScore)
{
    printf("%s score:\t %ld\n", _name, _currentScore);
}

void ShowHand(CARD *_cardsArr, size_t _numOfCards)
{
    int i = 0;
    if(_cardsArr == NULL || _numOfCards == 0)
    {
        return;
    }
    putchar('\n');
    printf("Your hand: \n");
    for(i = 0; i < _numOfCards; i++)
    {
        printf("%d card: ", i + 1);
        PrintCard(_cardsArr[i]);
        putchar('\n');
    }
}

void ShowDeclareCardPass()
{
    printf("Please choose a card to pass:\n");
}

void ShowGetPlayerChoice(int *_input, size_t numOfCards)
{
    int choice;
    do{
        printf("\nPlease choose a card between 1 and %ld: ", numOfCards);
        scanf("%d", &choice);
    } while (choice > numOfCards || choice < 1);
    putchar('\n');
    *_input = choice;
}

void ShowLeadingSuite(CARD_SUITS _suite)
{
    printf("Current leading suite: ");
    PrintSuite(_suite);
    putchar('\n');
    putchar('\n');
}


void PrintGivenCards(CARD *_cardsArr, size_t _numOfCards)
{
    int i = 0;
    if(_cardsArr == NULL || _numOfCards == 0)
    {
        return;
    }
    putchar('\n');
    for(i = 0; i < _numOfCards; i++)
    {
        printf("%d card: ", i + 1);
        PrintCard(_cardsArr[i]);
        putchar('\n');
    }
}

void PrintCard(CARD _card)
{
    int currentRank;
    CARD_SUITS currentSuite = CARD_SUITE(_card);
    switch (currentSuite)
    {
    case SPADES:
        printf("%sSpades %s %s", GRAY, SPADE_SYM, NORMAL);
        break;
    case HEARTS:
        printf("%sHearts %s %s", RED, HEART_SYM, NORMAL);
        break;
    case DIAMONDS:
        printf("%sDiamonds %s %s", RED, DIAMOND_SYM, NORMAL);
        break;
    case CLUBS:
        printf("%sClubs %s %s", GRAY ,CLUB_SYM, NORMAL);
        break;
    default:
        break;
    }
    currentRank = CARD_RANK(_card);
    if(0 <= currentRank && currentRank <= 8)
    {
        printf("%d", currentRank + 2);
        return;
    }
    else
    {
        switch (currentRank)
        {
        case 9:
            printf("J");
            break;
        case 10:
            printf("Q");
            break;
        case 11:
            printf("K");
            break;
        case ACE:
            printf("A");
            break;
        default:
            break;
        }
    }
}

void PrintCardNoWord(CARD _card)
{
    int currentRank;
    CARD_SUITS currentSuite = CARD_SUITE(_card);
    if(_card == NONE_CARD)
    {
        putchar(' ');
        return;
    }
    switch (currentSuite)
    {
    case SPADES:
        printf("%s%s %s", GRAY, SPADE_SYM, NORMAL);
        break;
    case HEARTS:
        printf("%s%s %s", RED, HEART_SYM, NORMAL);
        break;
    case DIAMONDS:
        printf("%s%s %s", RED, DIAMOND_SYM, NORMAL);
        break;
    case CLUBS:
        printf("%s%s %s", GRAY ,CLUB_SYM, NORMAL);
        break;
    default:
        break;
    }
    currentRank = CARD_RANK(_card);
    if(0 <= currentRank && currentRank <= 8)
    {
        printf("%d", currentRank + 2);
        return;
    }
    else
    {
        switch (currentRank)
        {
        case 9:
            printf("J");
            break;
        case 10:
            printf("Q");
            break;
        case 11:
            printf("K");
            break;
        case ACE:
            printf("A");
            break;
        default:
            break;
        }
    }
}


void PrintSuite(CARD_SUITS _suite)
{
    switch (_suite)
    {
    case SPADES:
        printf("%sSpades %s %s", GRAY, SPADE_SYM, NORMAL);
        break;
    case HEARTS:
        printf("%sHearts %s %s", RED, HEART_SYM, NORMAL);
        break;
    case DIAMONDS:
        printf("%sDiamonds %s %s", RED, DIAMOND_SYM, NORMAL);
        break;
    case CLUBS:
        printf("%sClubs %s %s", GRAY ,CLUB_SYM, NORMAL);
        break;
    default:
        printf("None ");
        break;
    }
}

void ShowTable(CARD_SUITS _leadingSuite, char **_names, CARD *_cards)
{
    size_t i;
    printf("\t Table Leading Suite is: ");
    PrintSuite(_leadingSuite);
    putchar('\n');
    
    
    printf("\n\t\t\t%s%s%s", BOLD_ON,_names[2], NORMAL);
    printf("\n\t\t\t");
    putchar('[');
    PrintCardNoWord(_cards[2]);
    putchar(']');
    putchar('\n');
    putchar('\n');

    printf("\t%s%s%s ", BOLD_ON,_names[3], NORMAL);
    putchar('[');
    PrintCardNoWord(_cards[3]);
    putchar(']');

    printf("\t\t    ");
    putchar('[');
    PrintCardNoWord(_cards[1]);
    putchar(']');
    printf(" %s%s%s ", BOLD_ON,_names[1], NORMAL);
    putchar('\n');

    
    
    putchar('\n');
    putchar('\n');

    
    printf("\t\t\t");
    putchar('[');
    PrintCardNoWord(_cards[0]);
    putchar(']');
    printf("\n\t\t\t%s%s%s\n", BOLD_ON,_names[0], NORMAL);
    
    putchar('\n');
   
}