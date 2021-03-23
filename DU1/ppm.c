/*
 * ppm.h
 * Reseni IJC-DU1, priklad b), 23.03.2021
 * Autor: Hung Do, FIT
 * Prelozeno: gcc 9.3
 *
 * Cteni ze souboru .ppm a operace nad daty struktury ppm
 */
#include <stdio.h>
#include <stdlib.h>     // malloc(), free()
#include <string.h>     // strcmp()
#include "ppm.h"
#include "error.h"

#define MAX_LIMIT 8000*8000*3

struct ppm *ppm_read(const char *filename)
{
    struct ppm *filedata = NULL;
    FILE *f;
    int xsize, ysize, c, i=0;
    char format[3];

    // kontrola pritomnosti souboru
    if ((f = fopen(filename, "rb")) == NULL)
    {
        warning_msg("ppm_read: Soubor %s nebyl nalezen\n", filename);
        return NULL;
    }

    // kontrola formatu P6
    if (fgets(format, 3, f) == NULL)
    {
        warning_msg("ppm_read: Soubor %s je prazdny\n", filename);
        return NULL;
    }
    else if (strcmp(format, "P6"))
        error_exit("ppm_read: Soubor %s neni formatu P6\n", filename);

    // cteni hlavicky souboru
    c = fscanf(f, "%d %d\n255\n", &xsize, &ysize);

    if (xsize * ysize * 3 > MAX_LIMIT)
    {
        warning_msg("ppm_read: Soubor prekrocil maximalni velikost\n");
        return NULL;
    }

    filedata = malloc(sizeof(struct ppm) + xsize * ysize * 3);
    if (filedata == NULL)
    {
        warning_msg("ppm_read: Chyba alokoce struktury\n");
        return NULL;
    }

    filedata->xsize = xsize;
    filedata->ysize = ysize;

    // cteni ze souboru
    while ((c = fgetc(f)) != EOF)
        filedata->data[i++] = c;

    fclose(f);
    return filedata;
}

void ppm_free(struct ppm *p)
{
    free(p);
}
/* ppm.c */
