/*
 * steg-encode.c
 * Reseni IJC-DU1, priklad b), 23.3.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Zasifruje zpravu do souboru ppm.
 * Slo o volitelnou ulohu
 */
#include <stdio.h>
#include <stdlib.h>
#include "eratosthenes.h"
#include "bitset.h"
#include "ppm.h"

#define MAX_LEN 1000

/**
 * @brief Zapis data se zasifrovanou zpravou do souboru ppm
 *
 * @param filename Jmeno souboru ppm
 * @param p Struktura ppm s daty o souboru
 */
void file_write(const char *filename, struct ppm *p)
{
    FILE *f = fopen(filename, "w");
    fprintf(f, "P6\n");
    fprintf(f, "%d %d\n", p->xsize, p->ysize);
    fprintf(f, "255\n");
    for (unsigned i = 0; i < p->xsize * p->ysize * 3; i++)
        fputc(p->data[i], f);

    fclose(f);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return EXIT_FAILURE;

    struct ppm *p = ppm_read(argv[1]);
    if (p == NULL)
        exit(0);    // nepodarilo se alokovat

    bitset_alloc(arr, p->xsize * p->ysize * 3);
    Eratosthenes(arr);

    // nacte zpravu od uzivatele
    char bit_place=0;   // pozice bitu
    int c;              // nacteny znak ze stdin
    ul i = 23UL;        // pozice prvniho bajtu k uprave
    printf("Napiste zpravu:\n");

    // nastaveni LSb hodnot podle znaku na prvociselnych pozicich souboru ppm
    // zacina u 23. bajtu souboru
    while ((c = getchar()) != EOF)
    {
        for (; i < bitset_size(arr) && bit_place < 8; i++)
        {
            if (!bitset_getbit(arr, i))
            {
                if ((c >> bit_place++) & 1)
                    p->data[i] |= 1;
                else
                    p->data[i] &= ~1;
            }
        }
        bit_place = 0;  
    }

    // pridani '\0'
    for (; i < bitset_size(arr) && bit_place < 8; i++)
    {
        if (!bitset_getbit(arr, i))
        {
            p->data[i] &= ~1;
            bit_place++;
        }
             
    }

    file_write(argv[1], p);    

    ppm_free(p);
    bitset_free(arr);

    return EXIT_SUCCESS;
}
/* steg-encode.c */
