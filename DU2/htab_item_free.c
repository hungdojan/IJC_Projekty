/*
 * htab_item_free.c        
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_item_free funkci
 */
#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

htab_item_t *htab_item_free(htab_item_t *item)
{
    if (item == NULL)
        return NULL;

    // uklada si ukazatel na dalsi zaznam, ktery vraci
    htab_item_t *next = item->next;
    free((char *)(item->pair->key));
    free(item->pair);
    free(item);
    return next;
}
/* htab_item_free.c */
