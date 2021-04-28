/*
 * htab_lookup_add.c
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_lookup_add funkci
 */
#include <string.h>
#include "htab.h"
#include "htab_private.h"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
    // hledani vetve zaznamu, ve kterem se nachazi dvojice
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    htab_item_t *item = t->ptr[index];  // hledana vetev
    htab_pair_t *pair = NULL;           // navratova dvojice
    
    // vetev je prazdna
    if (item == NULL)
    {
        t->ptr[index] = htab_item_init(key);
        if (t->ptr[index] == NULL)      // nepodarilo se alokovat zaznam
            pair = NULL;
        else
        {
            pair = t->ptr[index]->pair;
            (t->size)++;
        }
    }

    // prvni prvek
    else if (!strcmp(item->pair->key, key))
    {
        pair = item->pair;
    }
    else
    {
        // pruchod tabulkou
        for (; item->next != NULL && strcmp(item->next->pair->key, key); item = item->next)
            ;   // zamerne

        if (item->next == NULL) // pokud prvek neni v seznamu
        {
            item->next = htab_item_init(key);
            // kontrola, zda se povedlo spravne naalokovat
            if (item->next == NULL)
                return NULL;
            else
                (t->size)++;
        } // if (item->next == NULL)
        pair = item->next->pair;
    } // if (!strcmp(item->pair->key, key))

    return pair;
}
/* htab_lookup_add.c */
