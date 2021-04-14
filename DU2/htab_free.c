/*
 * htab_free.c
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_free funkci
 */
#include "htab.h"
#include <stdlib.h>

void htab_free(htab_t *t)
{
    htab_clear(t);
    free(t);
}
/* htab_free.c */
