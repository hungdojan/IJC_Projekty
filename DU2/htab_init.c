/*
 * htab_init.c        
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_init funkci
 */
#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

htab_t *htab_init(size_t n)
{
    htab_t *table = malloc(sizeof(htab_t) + n * sizeof(htab_item_t *));
    if (table != NULL)  // uspesne alokovani
    {
        table->arr_size = n;
        table->size = 0;
        for (size_t i = 0; i < n; i++)
            table->ptr[i] = NULL;
    }
    return table;
}
/* htab_init.c */
