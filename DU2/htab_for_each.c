/*
 * htab_for_each.c
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_for_each funkci
 */
#include "htab.h"
#include "htab_private.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data))
{
    // pruchod tabulkou
    for (size_t i = 0; i < htab_bucket_count(t); i++)
    {
        // pruchod jednou vetvi
        for (htab_item_t *item = t->ptr[i]; item != NULL; item = item->next)
            (*f)(item->pair);
    }
}
/* htab_for_each.c */
