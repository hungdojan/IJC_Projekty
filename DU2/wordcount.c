/*
 * wordcount.c        
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Vypocet poctu vyskytu slov oddelene bilymi znaky v souboru
 */
#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "io.h"

#define LIMIT 128
#define N_OF_PTR 65599 //256

#ifdef HASHTEST
// hash funkce typu djb2
size_t htab_hash_function(htab_key_t str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
#endif

void print_data(htab_pair_t *data)
{
    printf("%s\t%d\n", data->key, data->value);
}

int main()
{
    htab_t *table = htab_init(N_OF_PTR);
    if (table == NULL)  { goto htab_alloc_error; }

    char input[LIMIT];
    int length, over_limit = 0;
    // cteni slov
    while ((length = read_word(input, LIMIT, stdin)) != EOF)
    {
        // prazdne slovo (bily znak)
        if (!length)        { continue; }
        if (length > LIMIT-1 && !over_limit)
        {
            fprintf(stderr, "Error: delka slove je delsi nez je maximalni limit\n");
            over_limit = 1;
        }
        htab_pair_t *pair = htab_lookup_add(table, input);
        if (pair == NULL)   { goto new_item_failed; }
        (pair->value)++;
    }

    void (*f)(htab_pair_t *data) = &print_data;
#ifdef MOVETEST
    // testovani htab_move
    const size_t new_size = 256;
    htab_t *t2 = htab_move(new_size, table);
    if (!t2)
    {
        htab_free(table);
        goto htab_alloc_error;
    }
    htab_for_each(t2, f);
    htab_free(t2);
#else
    htab_for_each(table, f);
#endif


    htab_free(table);
    return EXIT_SUCCESS;

htab_alloc_error:
    fprintf(stderr, "Nepodarilo se alokovat misto pro tabulku.\n");
    return EXIT_FAILURE;
new_item_failed:
    fprintf(stderr, "Nepodarilo se alokovat misto pro novy zaznam.\n");
    htab_free(table);
    return EXIT_FAILURE;
}
/* wordcount.c */
