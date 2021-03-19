#include "cards.h"
#include <stdio.h>

int main(void)
{
    CARD card;
    for(card = spade_2; card < NUM_OF_CARDS; card++)
    {
        PrintCard(card);
        putchar('\n');
    }
}