/*
 * primes.c
 * Reseni IJC-DU1, priklad a), 23.03.2021
 * Autor: Hung Do, FIT
 * Prelozeno: gcc 9.3
 *
 * Vypis poslednich NUM_OF_PRIMES prvocisel v rozsahu 0..NUM_BITS
 * s pouzitim bitsetu a Eratosthenova sita
 */
#include <time.h>       // clock()
#include <stdio.h>
#include "eratosthenes.h"
#include "bitset.h"

#define NUM_BITS 200000000UL 
#define NUM_OF_PRIMES 10

int main()
{
    clock_t start = clock();
    bitset_create(array, NUM_BITS);
    Eratosthenes(array);

    // vypis prvocisel
    ul i = bitset_size(array);
    int index = NUM_OF_PRIMES - 1;
    ul primes[NUM_OF_PRIMES];           // pole NUM_OF_PRIMES poslednich prvocisel

    for (; index >= 0; i--) {
        if (!bitset_getbit(array, i))
            primes[index--] = i;
    }

    for (int j = 0; j < NUM_OF_PRIMES; j++)
        printf("%lu\n", primes[j]);

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    return 0;
}
/* primes.c */
