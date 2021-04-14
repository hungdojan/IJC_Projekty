/*
 * htab_move.c
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_mvoe funkci
 */
#include "htab.h"
#include "htab_private.h"

/**
 * @brief Hleda posledni zaznam ve vetvi
 *
 * @param line  Ukazatel na prvni zaznam ve vetvi
 * @return Posledni zaznam ve vetvi; NULL pokud vetev je prazda
 */
static htab_item_t *get_last(htab_item_t *line)
{
    htab_item_t *ret_item = NULL;
    if (line)
    {
        // pruchod vetvi
        for (ret_item = line; ret_item->next; ret_item = ret_item->next)
            ;   // zamerne
    }
    return ret_item;
}

htab_t *htab_move(size_t n, htab_t *from)
{
    htab_t *to = htab_init(n);
    if (to)
    {
        to->size = from->size;
        for (size_t i = 0; i < from->arr_size; i++)
        {
            while (from->ptr[i])
            {
                // zaznam, ktery se ma presunout
                htab_item_t *item   = from->ptr[i];
                from->ptr[i]        = item->next;
                item->next          = NULL;

                // index v poli ukazatelu nove tabulky
                size_t index = htab_hash_function(item->pair->key) % n;

                // zaznam, za ktery se ma zaznam pripojit
                htab_item_t *last_item = get_last(to->ptr[index]);
                if (!last_item) // pokud se jedna o prvni prvek
                    to->ptr[index]  = item;
                else
                    last_item->next = item;
            } // while(from->ptr[i])
        } // for (size_t i = 0; ... )
    } // if (to != NULL)
    return to;
}
/* htab_move.c */
