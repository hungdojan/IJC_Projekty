/*
 * steg-decode.c
 * Reseni IJC-DU1, priklad b), 23.3.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Desifruje tajnou zpravu ukrytou v souboru typu ppm.
 */
#include <stdio.h>      // printf()
#include <stdlib.h>     // malloc(), free()
#include "bitset.h"
#include "eratosthenes.h"
#include "ppm.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
        exit(1);

    struct ppm *filedata = ppm_read(argv[1]);
    if (filedata == NULL)   // nepodarilo se alokovat
        exit(0);

    bitset_alloc(arr, filedata->xsize * filedata->ysize * 3);
    Eratosthenes(arr);
    char *output = malloc(filedata->xsize * filedata->ysize * 3 / 8);

    char c = 0;             // nacteny znak
    int bit_place = 0;      // pozice bitu
    int index_char = 0;     // index znaku v poli output
    int lsb_value;          // hodnota Least Significant Bit u nacteneho znaku

    // desifrovani zpravy
    for (ul i = 23UL; i < filedata->xsize * filedata->ysize * 3; i++)
    {
        if (!bitset_getbit(arr, i))                 // kontrola prvocisel
        {
            lsb_value = filedata->data[i] & 1;      // kontrola LSb
            c ^= lsb_value << bit_place++;          // zapis bitu
            if (bit_place == 8)                     // vypis znaku
            {
                output[index_char++] = c;
                if (c == '\0')
                    break;
                bit_place = 0;                      // nulovani hodnot
                c = 0;
            }
        }
    }

    ppm_free(filedata);
    bitset_free(arr);

    if (c != '\0')      // kontrola znaku konce zpravy
    {
        free(output);
        error_exit("\nsteg-decode: Pole znaku nebylo ukonceno znakem \\0\n");
    }
    else
    {
        printf("%s\n", output);
        free(output);
    }

    return EXIT_SUCCESS;
}
/* steg-decode.c */
