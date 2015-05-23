#include <p33FJ128MC802.h>

#include "time.h"

void pause_ms(unsigned short n)
{
    unsigned short i,j;
    for(j=0; j<n; j++)
        for(i=0; i<4000; i++)
            Nop();
}

void pause_s(unsigned short n)
{
    unsigned short i;
    for(i=0; i<n; i++)
        pause_ms(1000);
}

