/*
 * bitset.c
 * Reseni IJC-DU1, priklad a), 23.03.2021
 * Autor: Hung Do, FIT
 * Prelozeno: gcc 9.3
 *
 * Deklarace externich inline funkci
 */
#include "bitset.h"

#ifdef USE_INLINE
    extern ul bitset_size(const bitset_t name);
    extern void bitset_setbit(bitset_t name, const bitset_index_t index, const int value);
    extern ul bitset_getbit(const bitset_t name, const bitset_index_t index);
#endif
/* bitset.c */
