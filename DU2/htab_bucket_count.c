/*
 * htab_bucket_count.c
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_bucket_count funkci
 */
#include "htab.h"
#include "htab_private.h"

size_t htab_bucket_count(const htab_t *t)
{
    return t->arr_size;
}
/* htab_bucket_count.c */
