/*
 * htab_clear.c
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_clear funkci
 */
#include "htab.h"
#include "htab_private.h"

void htab_clear(htab_t *t)
{
    // pokud se v tabulce stale nachazi nejaky prvek
    if (htab_size(t))
    {
        for (size_t i = 0; i < htab_bucket_count(t); i++)
        {
            while (t->ptr[i] != NULL)
                t->ptr[i] = htab_item_free(t->ptr[i]);
        }
        t->size = 0;
    }
}
/* htab_clear.c */
