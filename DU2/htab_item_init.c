/*
 * htab_item_init.c        
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_item_init funkci
 */
#include "htab.h"
#include "htab_private.h"
#include <stdlib.h>

htab_item_t *htab_item_init(htab_key_t key)
{
    htab_item_t *item = malloc(sizeof(htab_item_t));    // alokovany zaznam
    htab_pair_t *pair;                                  // alokovana dvojice
    char *string;                                       // alokovany retezec obsahujici klic
    if (item)   // uspesna alokace
    {
        pair = malloc(sizeof(htab_pair_t));
        if (pair == NULL)   { goto pair_alloc_fail; }

        string = calloc(strlen(key) + 1, sizeof(char));
        if (string == NULL) { goto key_alloc_fail;  }

        // inicializace dvojice
        strcpy(string, key);
        pair->key = string;
        pair->value = 0;

        // inicializace zaznamu
        item->pair = pair;
        item->next = NULL;
    }
    return item;

// osetreni nepovedenych alokaci
key_alloc_fail:
    free(pair);
pair_alloc_fail:
    free(item);
    return NULL;
}
/* htab_item_free.c */
