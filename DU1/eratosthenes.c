/*
 * eratosthenes.c
 * Reseni IJC-DU1, priklad a), 23.03.2021
 * Autor: Hung Do, FIT
 * Prelozeno: gcc 9.3
 *
 * Vyznaceni prvocisel v bitsetu pomoci Eratosthenova sita
 */
#include <string.h>     // memset()
#include <math.h>       // sqrt()
#include "eratosthenes.h"

void Eratosthenes(bitset_t name)
{
    // nastaveni sudych bitu na 1 a lichych bitu na 0
    memset(&name[1], 0x55, bitset_size(name) / 8 + 1);

    // oprava prvnich 4 bitu na 0011
    bitset_setbit(name, 1UL, 1);
    bitset_setbit(name, 2UL, 0);

    // samotny algoritmus
    for (ul i = 3UL; i <= sqrt(bitset_size(name)); i += 2)
    {
        if (!bitset_getbit(name, i))
            // odstranovani nasobku prvocisel
            for (ul j = i*i; j <= bitset_size(name); j += 2*i)
                bitset_setbit(name, j, 1);
    }
}
/* eratosthenes.c */
