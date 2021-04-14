/*
 * htab_hash_function.c
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Modul s deklaraci htab_hash_function funkci
 */
#include "htab.h"
#include <stdint.h>

size_t htab_hash_function(htab_key_t str)
{
    uint32_t h=0;
    const unsigned char *p;
    for (p = (const unsigned char *)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}
/* htab_hash_function.c */
