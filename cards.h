#ifndef CARDS_H
#define CARDS_H

#define ACE 12
#define CARDS_IN_SUITE 13

#define CARD_SUITE(_card) (CARD_SUITS)(int)(_card / CARDS_IN_SUITE)
#define CARD_RANK(_card) (int)(_card % CARDS_IN_SUITE)



typedef enum CARD_SUITS{
    SPADES, 
    HEARTS,
    DIAMONDS,
    CLUBS,
    NONE_SUIT = 10
} CARD_SUITS;

typedef enum CARD{
    spade_2, /*0 */
    spade_3,
    spade_4,
    spade_5,
    spade_6,
    spade_7,
    spade_8,
    spade_9,
    spade_10,
    spade_J,
    spade_Q,
    spade_K,
    spade_A, /* 12 */

    heart_2, /*13 */
    heart_3,
    heart_4,
    heart_5,
    heart_6,
    heart_7,
    heart_8,
    heart_9,
    heart_10,
    heart_J,
    heart_Q,
    heart_K,
    heart_A, /* 25 */ 

    diamond_2, /* 26 */
    diamond_3,
    diamond_4,
    diamond_5,
    diamond_6,
    diamond_7,
    diamond_8,
    diamond_9,
    diamond_10,
    diamond_J,
    diamond_Q,
    diamond_K,
    diamond_A, /* 38 */  

    club_2, /* 39 */
    club_3,
    club_4,
    club_5,
    club_6,
    club_7,
    club_8,
    club_9,
    club_10,
    club_J,
    club_Q,
    club_K,
    club_A, /* 51 */

    NUM_OF_CARDS,  /*52*/
    NONE_CARD = 100
} CARD;



#endif
