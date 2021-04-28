/*
 * io.c        
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Deklarace funkce pro cteni slov ze souboru
 */
#include "io.h"
#include <ctype.h>  // isspace

int read_word(char *s, int max, FILE *f)
{
    if (f == NULL)
    {
        fprintf(stderr, "Nepodarilo se otevrit soubor\n");
        return EOF;
    }

    int c, index = 0, length = 0;
    // proces nacitani
    while((c = fgetc(f)) != EOF)
    {
        if (isspace(c)) // konec slova
            break;
        else
        {
            length++;
            if (index < max-1)  // nacitani do max-1 pozice
                s[index++] = c;
        }
    }
    s[index] = '\0';
    if (c == EOF)   // osetreni konce souboru
        length = c;
    return length;
}
/* io.c */
