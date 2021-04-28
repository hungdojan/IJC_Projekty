/*
 * htab_find.c
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_find funkci
 */
#include "htab.h"
#include "htab_private.h"

htab_pair_t *htab_find(htab_t *t, htab_key_t key)
{
    // hledani vetve zaznamu, ve kterem se nachazi dvojice
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    htab_item_t *item = t->ptr[index];  // hledana vetev
    htab_pair_t *pair = NULL;           // navratova dvojice

    // pruchod vetvi
    for ( ; item != NULL && strcmp(item->pair->key, key); item = item->next)
        ;   // zamerne  
    if (item != NULL)   { pair = item->pair; }

    return pair;
}
/* htab_find.c */
