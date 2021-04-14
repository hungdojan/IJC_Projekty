/*
 * htab_size.c        
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_size funkci
 */
#include "htab.h"
#include "htab_private.h"

size_t htab_size(const htab_t *t)
{
    return t->size;
}
/* htab_size.c */
