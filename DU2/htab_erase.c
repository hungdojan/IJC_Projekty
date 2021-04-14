/*
 * htab_erase.c
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_erase funkci
 */
#include <string.h>
#include "htab.h"
#include "htab_private.h"

bool htab_erase(htab_t *t, htab_key_t key)
{
    // hledani indexu vetve
    size_t index = htab_hash_function(key) % htab_bucket_count(t);
    bool ret_val = false;
    
    htab_item_t *item = t->ptr[index];
    if (item != NULL)
    {
        // hledany prvek je ten prvni
        if (!strcmp(item->pair->key, key))
        {
            item = htab_item_free(item);
            (t->size)--;
            ret_val = true;
        }
        else
        {
            // pruchod vetvi
            for (; item->next != NULL && strcmp(item->next->pair->key, key);
                    item = item->next)
                ;   // zamerne
            if (item->next != NULL) // odstraneni item->next
            {
                item->next = htab_item_free(item->next);
                (t->size)--;
                ret_val = true;
            }
        }
    }
    return ret_val;
}
/* htab_erase.c */
