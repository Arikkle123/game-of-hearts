#include <stdio.h>
#include <string.h>
#include "player.h"

void PlayerCreateWithIllegalNameTest();
void PlayerCreateWithIllegalIdentityTest();
void PlayerCreateTest1();
void PlayerCreateTest2();

void PlayerDoubleDestroyTest();

void PlayerGiveCardNotInitializedPlayerTest();
void PlayerGiveCardIllegalCardTest();
void PlayerGiveCardTest1();
void PlayerGiveCardTest2();
void PlayerGiveCardTest3();
void PlayerGiveCardFullHandTest();

void PlayerTakeCardByIndexNotInitializedPlayerTest();
void PlayerTakeCardByIndexToNotInitializedCardHolderTest();
void PlayerTakeCardByIndexIllegalIndexTest();
void PlayerTakeCardByIndexEmptyHandTest();
void PlayerTakeCardByIndexTest1();
void PlayerTakeCardByIndexTest2();
void PlayerTakeCardByIndexTest3();

void PlayerTakeCardByCardTypeNotInitializedPlayerTest();
void PlayerTakeCardByCardTypeToNotInitializedCardHolderTest();
void PlayerTakeCardByCardTypeIllegalCardTest();
void PlayerTakeCardByCardTypeNotExistingCardTest();
void PlayerTakeCardByCardTypeEmptyHandTest();
void PlayerTakeCardByCardTypeTest1();
void PlayerTakeCardByCardTypeTest2();
void PlayerTakeCardByCardTypeTest3();

void PlayerSortHandNotInitializedPlayerTest();
void PlayerSortHandEmptyHandTest();
void PlayerSortHandTest1();
void PlayerSortHandTest2();

void PlayerHandIsEmptyNotInitailizedPlayerTest();
void PlayerHandIsEmptyEmptyHandTest();
void PlayerHandIsEmptyNotEmptyHandTest();

void PlayerCardIsFoundNotInitailizedPlayerTest();
void PlayerCardIsFoundIllegalCardTest();
void PlayerCardIsFoundEmptyHandTest();
void PlayerCardIsFoundNotFoundTest();
void PlayerCardIsFoundTest();

void PlayerFindCurrentMinNotInitailizedPlayerTest();
void PlayerFindCurrentMinEmptyHandTest();
void PlayerFindCurrentMinTest1();
void PlayerFindCurrentMinTest2();

void PlayerFindCurrentMinBySuiteNotInitailizedPlayerTest();
void PlayerFindCurrentMinBySuiteEmptyHandTest();
void PlayerFindCurrentMinBySuiteNOTFOUNDTest();
void PlayerFindCurrentMinBySuiteTest1();
void PlayerFindCurrentMinBySuiteTest2();

void PlayerShowHandTest1();

int main(void)
{
    PlayerCreateWithIllegalNameTest();
    PlayerCreateWithIllegalIdentityTest();
    PlayerCreateTest1();
    PlayerCreateTest2();
    putchar('\n');

    PlayerDoubleDestroyTest();
    putchar('\n');

    PlayerGiveCardNotInitializedPlayerTest();
    PlayerGiveCardIllegalCardTest();
    PlayerGiveCardTest1();
    PlayerGiveCardTest2();
    PlayerGiveCardTest3();
    PlayerGiveCardFullHandTest();
    putchar('\n');

    PlayerTakeCardByIndexNotInitializedPlayerTest();
    PlayerTakeCardByIndexToNotInitializedCardHolderTest();
    PlayerTakeCardByIndexIllegalIndexTest();
    PlayerTakeCardByIndexEmptyHandTest();
    PlayerTakeCardByIndexTest1();
    PlayerTakeCardByIndexTest2();
    PlayerTakeCardByIndexTest3();
    putchar('\n');

    PlayerTakeCardByCardTypeNotInitializedPlayerTest();
    PlayerTakeCardByCardTypeToNotInitializedCardHolderTest();
    PlayerTakeCardByCardTypeIllegalCardTest();
    PlayerTakeCardByCardTypeNotExistingCardTest();
    PlayerTakeCardByCardTypeEmptyHandTest();
    PlayerTakeCardByCardTypeTest1();
    PlayerTakeCardByCardTypeTest2();
    PlayerTakeCardByCardTypeTest3();
    putchar('\n');

    PlayerSortHandNotInitializedPlayerTest();
    PlayerSortHandEmptyHandTest();
    PlayerSortHandTest1();
    PlayerSortHandTest2();
    putchar('\n');

    PlayerHandIsEmptyNotInitailizedPlayerTest();
    PlayerHandIsEmptyEmptyHandTest();
    PlayerHandIsEmptyNotEmptyHandTest();
    putchar('\n');

    PlayerCardIsFoundNotInitailizedPlayerTest();
    PlayerCardIsFoundIllegalCardTest();
    PlayerCardIsFoundEmptyHandTest();
    PlayerCardIsFoundNotFoundTest();
    PlayerCardIsFoundTest();
    putchar('\n');

    PlayerFindCurrentMinNotInitailizedPlayerTest();
    PlayerFindCurrentMinEmptyHandTest();
    PlayerFindCurrentMinTest1();
    PlayerFindCurrentMinTest2();
    putchar('\n');

    PlayerFindCurrentMinBySuiteNotInitailizedPlayerTest();
    PlayerFindCurrentMinBySuiteEmptyHandTest();
    PlayerFindCurrentMinBySuiteNOTFOUNDTest();
    PlayerFindCurrentMinBySuiteTest1();
    PlayerFindCurrentMinBySuiteTest2();
    putchar('\n');

    PlayerShowHandTest1();
}







/************************** Player Create tests ****************************************/
void PlayerCreateWithIllegalNameTest()
{
    char name[] = "";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    if(playPtr == NULL)
    {
        printf("Create player with illegal name test PASS!\n");
    }
    else
    {
        printf("Create player with illegal name test FAIL!\n");
    }
}

void PlayerCreateWithIllegalIdentityTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, 5);
    if(playPtr == NULL)
    {
        printf("Create player with illegal identity test PASS!\n");
    }
    else
    {
        printf("Create player with illegal identity test FAIL!\n");
    }
}
void PlayerCreateTest1()
{
    char name[] = "Ariel", getName[15];
    size_t currentNumOfCards;
    PLAYER_TYPE playersIdentity;
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    PlayerGetIdentity(playPtr, &playersIdentity);
    PlayerGetName(playPtr, getName);
    if(playPtr != NULL && strcmp(getName, name) == 0 & playersIdentity == HUMAN_PLAYER && currentNumOfCards == 0)
    {
        printf("Create player test 1 PASS!\n");
    }
    else
    {
        printf("Create player test 1 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerCreateTest2()
{
    char name[] = "Alice", getName[15];
    size_t currentNumOfCards;
    PLAYER_TYPE playersIdentity;
    Player *playPtr = PlayerCreate(name, COMPUTER_PLAYER);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    PlayerGetIdentity(playPtr, &playersIdentity);
    PlayerGetName(playPtr, getName);
    if(playPtr != NULL && strcmp(getName, name) == 0 & playersIdentity == COMPUTER_PLAYER && currentNumOfCards == 0)
    {
        printf("Create player test 2 PASS!\n");
    }
    else
    {
        printf("Create player test 2 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}





/************************** Player destroy tests ****************************************/


void PlayerDoubleDestroyTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    printf("Player double Destroy Test - first destroy:\n");
    PlayerDestroy(playPtr);
    printf("Player double Destroy Test - second destroy:\n");
    PlayerDestroy(playPtr);
}





/************************** Player give card tests ****************************************/

void PlayerGiveCardNotInitializedPlayerTest()
{
    Player *playPtr = NULL;
    if(PlayerGiveCard(playPtr, spade_4) == POINTER_NOT_INITIALIZED)
    {
        printf("Player give card to not initialized player test PASS!\n");
    }
    else{
        printf("Player give card to not initialized player test FAIL!\n");
    }
}
void PlayerGiveCardIllegalCardTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    if(PlayerGiveCard(playPtr, 157) == ILLEGAL_CARD)
    {
        printf("Player give card illegal card test PASS!\n");
    }
    else{
        printf("Player give card illegal card test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}

void PlayerGiveCardTest1()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    size_t currentNumOfCards;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    if(currentNumOfCards == 1 )
    {
        printf("Player give card test 1 PASS!\n");
    }
    else{
        printf("Player give card test 1 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerGiveCardTest2()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    size_t currentNumOfCards;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    if(currentNumOfCards == 3 )
    {
        printf("Player give card test 2 PASS!\n");
    }
    else{
        printf("Player give card test 2 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerGiveCardTest3()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    size_t currentNumOfCards;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_6);
    PlayerGiveCard(playPtr, club_7);
    PlayerGiveCard(playPtr, club_5);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    if(currentNumOfCards == 8 )
    {
        printf("Player give card test 3 PASS!\n");
    }
    else{
        printf("Player give card test 3 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}

void PlayerGiveCardFullHandTest()
{
    char name[] = "Ariel";
    size_t i;
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    size_t currentNumOfCards;
    for(i = 0; i < 3; i++)
    {
        PlayerGiveCard(playPtr, spade_4);
        PlayerGiveCard(playPtr, spade_4);
        PlayerGiveCard(playPtr, heart_J);
        PlayerGiveCard(playPtr, diamond_7);
        PlayerGiveCard(playPtr, heart_4);
        PlayerGiveCard(playPtr, heart_8);
    }
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    if(currentNumOfCards == 18)
    {
        printf("Player give card hand full reallocation PASS!\n");
    }
    else{
        printf("Player give card hand full reallocation FAIL!\n");
    }
    PlayerDestroy(playPtr);
}





/************************** Player take card by index tests ****************************************/

void PlayerTakeCardByIndexNotInitializedPlayerTest()
{
    Player *playPtr = NULL;
    CARD cardHolder;
    if(PlayerTakeCardByIndex(playPtr, &cardHolder, 0) == POINTER_NOT_INITIALIZED)
    {
        printf("Player take card by index from not initialized player test PASS!\n");
    }
    else
    {
        printf("Player take card by index from not initialized player test FAIL!\n");
    }
}
void PlayerTakeCardByIndexToNotInitializedCardHolderTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD *cardHolder = NULL;
    PlayerGiveCard(playPtr, spade_4);
    if(PlayerTakeCardByIndex(playPtr, cardHolder, 0) == POINTER_NOT_INITIALIZED)
    {
        printf("Player take card by index to not initialized card holder test PASS!\n");
    }
    else
    {
        printf("Player take card by index to not initialized card holder test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}

void PlayerTakeCardByIndexIllegalIndexTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    if(PlayerTakeCardByIndex(playPtr, &cardHolder, 6) == ILLEGAL_INDEX)
    {
        printf("Player take card by index illegal index test PASS!\n");
    }
    else
    {
        printf("Player take card by index illegal index test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerTakeCardByIndexEmptyHandTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder;
    if(PlayerTakeCardByIndex(playPtr, &cardHolder, 0) == EMPTY_HAND)
    {
        printf("Player take card by index from empty hand test PASS!\n");
    }
    else
    {
        printf("Player take card by index from empty hand test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerTakeCardByIndexTest1()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder;
    size_t currentNumOfCards;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerTakeCardByIndex(playPtr, &cardHolder, 1);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    if( currentNumOfCards == 3 && cardHolder == diamond_7)
    {
        printf("Player take card by index test 1 PASS!\n");
    }
    else
    {
        printf("Player take card by index test 1 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerTakeCardByIndexTest2()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder1, cardHolder2;
    size_t currentNumOfCards;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerTakeCardByIndex(playPtr, &cardHolder1, 1);
    PlayerTakeCardByIndex(playPtr, &cardHolder2, 1);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    if( currentNumOfCards == 2 && cardHolder1 == diamond_7 && cardHolder2 == heart_4)
    {
        printf("Player take card by index test 2 PASS!\n");
    }
    else
    {
        printf("Player take card by index test 2 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerTakeCardByIndexTest3()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder1, cardHolder2, cardHolder3;
    size_t currentNumOfCards;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerTakeCardByIndex(playPtr, &cardHolder1, 0);
    PlayerTakeCardByIndex(playPtr, &cardHolder2, 0);
    PlayerTakeCardByIndex(playPtr, &cardHolder3, 0);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    if( currentNumOfCards == 0 && cardHolder1 == spade_4 && cardHolder2 == diamond_7 && cardHolder3 == heart_4)
    {
        printf("Player take card by index test 3 PASS!\n");
    }
    else
    {
        printf("Player take card by index test 3 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}


/************************** Player take card by type tests ****************************************/



void PlayerTakeCardByCardTypeNotInitializedPlayerTest()
{
    Player *playPtr = NULL;
    CARD cardHolder;
    if(PlayerTakeCardByCardType(playPtr, &cardHolder, heart_10) == POINTER_NOT_INITIALIZED)
    {
        printf("Player take card by type from not initialized player test PASS!\n");
    }
    else
    {
        printf("Player take card by type from not initialized player test FAIL!\n");
    }
}
void PlayerTakeCardByCardTypeToNotInitializedCardHolderTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD *cardHolder = NULL;
    PlayerGiveCard(playPtr, spade_4);
    if(PlayerTakeCardByCardType(playPtr, cardHolder, 0) == POINTER_NOT_INITIALIZED)
    {
        printf("Player take card by type to not initialized card holder test PASS!\n");
    }
    else
    {
        printf("Player take card by type to not initialized card holder test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}

void PlayerTakeCardByCardTypeIllegalCardTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    if(PlayerTakeCardByCardType(playPtr, &cardHolder, 124) == ILLEGAL_CARD)
    {
        printf("Player take card by type illegal card test PASS!\n");
    }
    else
    {
        printf("Player take card by type illegal card test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerTakeCardByCardTypeNotExistingCardTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    if(PlayerTakeCardByCardType(playPtr, &cardHolder, diamond_4) == CARD_NOT_FOUND)
    {
        printf("Player take card by type not existing card test PASS!\n");
    }
    else
    {
        printf("Player take card by type not existing card test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerTakeCardByCardTypeEmptyHandTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder;
    if(PlayerTakeCardByCardType(playPtr, &cardHolder, 0) == EMPTY_HAND)
    {
        printf("Player take card by type from empty hand test PASS!\n");
    }
    else
    {
        printf("Player take card by type from empty hand test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerTakeCardByCardTypeTest1()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder;
    size_t currentNumOfCards;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerTakeCardByCardType(playPtr, &cardHolder, diamond_7);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    if( currentNumOfCards == 3 && cardHolder == diamond_7)
    {
        printf("Player take card by type test 1 PASS!\n");
    }
    else
    {
        printf("Player take card by type test 1 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerTakeCardByCardTypeTest2()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder1, cardHolder2;
    size_t currentNumOfCards;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerTakeCardByCardType(playPtr, &cardHolder1, diamond_7);
    PlayerTakeCardByCardType(playPtr, &cardHolder2, heart_4);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    if( currentNumOfCards == 2 && cardHolder1 == diamond_7 && cardHolder2 == heart_4)
    {
        printf("Player take card by type test 2 PASS!\n");
    }
    else
    {
        printf("Player take card by type test 2 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerTakeCardByCardTypeTest3()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder1, cardHolder2, cardHolder3;
    size_t currentNumOfCards;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerTakeCardByCardType(playPtr, &cardHolder1, spade_4);
    PlayerTakeCardByCardType(playPtr, &cardHolder2, heart_4);
    PlayerTakeCardByCardType(playPtr, &cardHolder3, diamond_7);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    if( currentNumOfCards == 0 && cardHolder1 == spade_4 && cardHolder2 == heart_4 && cardHolder3 == diamond_7)
    {
        printf("Player take card by type test 3 PASS!\n");
    }
    else
    {
        printf("Player take card by type test 3 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}


/************************** Player sort hand tests ****************************************/

void PlayerSortHandNotInitializedPlayerTest()
{
    Player *playPtr = NULL;
    if(PlayerSortHand(playPtr) == POINTER_NOT_INITIALIZED)
    {
        printf("Player sort hand not initailized player test PASS!\n");
    }
    else
    {
        printf("Player sort hand not initailized player test FAIL!\n");
    }
}
void PlayerSortHandEmptyHandTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    if(PlayerSortHand(playPtr) == EMPTY_HAND)
    {
        printf("Player sort hand empty hand test PASS!\n");
    }
    else
    {
        printf("Player sort hand empty hand test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerSortHandTest1()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolder1, cardHolder2, cardHolder3;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerSortHand(playPtr);
    PlayerTakeCardByIndex(playPtr, &cardHolder1, 0);
    PlayerTakeCardByIndex(playPtr, &cardHolder2, 0);
    PlayerTakeCardByIndex(playPtr, &cardHolder3, 0);
    if(cardHolder1 == spade_4 && cardHolder2 == heart_4 && cardHolder3 == diamond_7)
    {
        printf("Player sort hand 3 card hand test PASS!\n");
    }
    else
    {
        printf("Player sort hand 3 card hand test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerSortHandTest2()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD cardHolderPrev, cardHolderNext;
    size_t currentNumOfCards;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_6);
    PlayerGiveCard(playPtr, club_7);
    PlayerGiveCard(playPtr, club_5);
    PlayerSortHand(playPtr);
    PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    PlayerTakeCardByIndex(playPtr, &cardHolderPrev, 0);
    PlayerTakeCardByIndex(playPtr, &cardHolderNext, 0);
    while(currentNumOfCards != 0)
    {
        if(cardHolderPrev > cardHolderNext)
        {
            printf("Player sort hand test 2 FAIL!\n");
            PlayerDestroy(playPtr);
            return;
        }
        cardHolderPrev = cardHolderNext;
        PlayerTakeCardByIndex(playPtr, &cardHolderNext, 0);
        PlayerGetNumOfCards(playPtr, &currentNumOfCards);
    }
    printf("Player sort hand test 2 PASS!\n");
    PlayerDestroy(playPtr);
}


/************************** Player hand is empty tests ****************************************/

void PlayerHandIsEmptyNotInitailizedPlayerTest()
{
    Player *playPtr = NULL;
    if(PlayerHandIsEmpty(playPtr) == POINTER_NOT_INITIALIZED)
    {
        printf("Player Hand Is Empty Player Not initialized test PASS!\n");
    }
    else
    {
        printf("Player Hand Is Empty Player Not initialized test FAIL!\n");
    }
}
void PlayerHandIsEmptyEmptyHandTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    if(PlayerHandIsEmpty(playPtr) == EMPTY_HAND)
    {
        printf("Player Hand Is Empty empty hand test PASS!\n");
    }
    else
    {
        printf("Player Hand Is Empty empty hand test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerHandIsEmptyNotEmptyHandTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    PlayerGiveCard(playPtr, spade_4);
    if(PlayerHandIsEmpty(playPtr) == HAND_NOT_EMPTY)
    {
        printf("Player Hand Is Empty not empty hand test PASS!\n");
    }
    else
    {
        printf("Player Hand Is Empty not empty hand test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}




/************************** Player card if found tests ****************************************/


void PlayerCardIsFoundNotInitailizedPlayerTest()
{
    Player *playPtr = NULL;
    if(PlayerCardIsFound(playPtr, club_J) == POINTER_NOT_INITIALIZED)
    {
        printf("Player card is found not initialized player test PASS!\n");
    }
    else
    {
        printf("Player card is found not initialized player test FAIL!\n");
    }
}
void PlayerCardIsFoundIllegalCardTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    PlayerGiveCard(playPtr, spade_4);
    if(PlayerCardIsFound(playPtr, 354) == ILLEGAL_CARD)
    {
        printf("Player card is found illegal card test PASS!\n");
    }
    else
    {
        printf("Player card is found illegal card test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerCardIsFoundEmptyHandTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    if(PlayerCardIsFound(playPtr, spade_4) == CARD_NOT_FOUND)
    {
        printf("Player card is empty hand test PASS!\n");
    }
    else
    {
        printf("Player card is empty hand test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerCardIsFoundNotFoundTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_6);
    PlayerGiveCard(playPtr, club_7);
    if(PlayerCardIsFound(playPtr, spade_10) == CARD_NOT_FOUND)
    {
        printf("Player card not found test PASS!\n");
    }
    else
    {
        printf("Player card not found test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerCardIsFoundTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_6);
    PlayerGiveCard(playPtr, club_7);
    if(PlayerCardIsFound(playPtr, diamond_7) == CARD_FOUND)
    {
        printf("Player card found test PASS!\n");
    }
    else
    {
        printf("Player card found test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}


/************************** Player find current min card tests ****************************************/

void PlayerFindCurrentMinNotInitailizedPlayerTest()
{
    Player *playPtr = NULL;
    CARD minCard;
    if(PlayerGetMinCard(playPtr, &minCard) == POINTER_NOT_INITIALIZED)
    {
        printf("Player find min player not initialized test PASS!\n");
    }
    else
    {
        printf("Player find min player not initialized test FAIL!\n");
    }
}
void PlayerFindCurrentMinEmptyHandTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD minCard;
    if(PlayerGetMinCard(playPtr, &minCard) == EMPTY_HAND)
    {
        printf("Player card min is empty hand test PASS!\n");
    }
    else
    {
        printf("Player card min is empty hand test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerFindCurrentMinTest1()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD minCard;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGetMinCard(playPtr, &minCard);
    if(minCard == spade_4)
    {
        printf("player find current min test 1 PASS!\n");
    }
    else
    {
        printf("player find current min test 1 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerFindCurrentMinTest2()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD minCard;    
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_6);
    PlayerGiveCard(playPtr, club_7);
    PlayerGetMinCard(playPtr, &minCard);
    if(minCard == spade_4)
    {
        printf("player find current min test 2 PASS!\n");
    }
    else
    {
        printf("player find current min test 2 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}



/************************** Player find current min by suite card tests ****************************************/

void PlayerFindCurrentMinBySuiteNotInitailizedPlayerTest()
{
    Player *playPtr = NULL;
    CARD minCard;
    if(PlayerGetMinCardBySuite(playPtr, &minCard, CLUBS) == POINTER_NOT_INITIALIZED)
    {
        printf("Player find min By Suite player not initialized test PASS!\n");
    }
    else
    {
        printf("Player find min By Suite player not initialized test FAIL!\n");
    }
}
void PlayerFindCurrentMinBySuiteEmptyHandTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD minCard;
    if(PlayerGetMinCardBySuite(playPtr, &minCard, CLUBS) == EMPTY_HAND)
    {
        printf("Player card min BySuite is empty hand test PASS!\n");
    }
    else
    {
        printf("Player card min BySuite is empty hand test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerFindCurrentMinBySuiteNOTFOUNDTest()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD minCard;
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, heart_4);
    if(PlayerGetMinCardBySuite(playPtr, &minCard, CLUBS) == CARD_NOT_FOUND)
    {
        printf("Player card min BySuite suite not found test PASS!\n");
    }
    else
    {
        printf("Player card min BySuite suite not found test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerFindCurrentMinBySuiteTest1()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD minCard;
    PlayerGiveCard(playPtr, spade_4);
    PlayerGetMinCardBySuite(playPtr, &minCard, SPADES);
    if(minCard == spade_4)
    {
        printf("player find current min BySuite test 1 PASS!\n");
    }
    else
    {
        printf("player find current min BySuite test 1 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}
void PlayerFindCurrentMinBySuiteTest2()
{
    char name[] = "Ariel";
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD minCard;    
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_6);
    PlayerGiveCard(playPtr, club_7);
    PlayerGetMinCardBySuite(playPtr, &minCard, HEARTS);
    if(minCard == heart_4)
    {
        printf("player find current min BySuite test 2 PASS!\n");
    }
    else
    {
        printf("player find current min BySuite test 2 FAIL!\n");
    }
    PlayerDestroy(playPtr);
}


void PlayerShowHandTest1()
{
    char name[] = "Ariel";
    CARD showHand[13];
    Player *playPtr = PlayerCreate(name, HUMAN_PLAYER);
    CARD minCard;    
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_7);
    PlayerGiveCard(playPtr, spade_4);
    PlayerGiveCard(playPtr, heart_4);
    PlayerGiveCard(playPtr, heart_J);
    PlayerGiveCard(playPtr, diamond_6);
    PlayerGiveCard(playPtr, club_7);
    PlayerShowHand(playPtr, showHand);
    if(showHand[0] == heart_J && showHand[5] == diamond_6 && showHand[2] == spade_4)
    {
        printf("Player Show hand test PASS!\n");
    }
    else
    {
        printf("Player Show hand test FAIL!\n");
    }
    PlayerDestroy(playPtr);
}