/*
 * ppm.h
 * Reseni IJC-DU1, priklad b), 23.03.2021
 * Autor: Hung Do, FIT
 * Prelozeno: gcc 9.3
 */
#ifndef _PPM_H
#define _PPM_H

struct ppm
{
    unsigned xsize;
    unsigned ysize;
    char data[];
};

/**
 * @brief Nacteni obsahu souboru do struktury
 *
 * Pokud nebyl soubor nalezen nebo alokace neprobehla uspecne,
 * vypise program chybove hlaseni a ukoncuje funkci
 *
 * @param filename Nazev souboru
 * @return Dynamicky alokovanou pamet; v pripade neuspechu vraci #NULL
 */
struct ppm *ppm_read(const char *filename);

/**
 * #brief Uvolnuje alokovanou pamet
 *
 * @param name Jmeno struktury
 */
void ppm_free(struct ppm *p);

#endif
/* ppm.h */
