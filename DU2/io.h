/*
 * io.h        
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Hlavickovy soubor obsahujici prototyp funkce read_word
 */
#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>

/**
 * @brief Cte slova ze souboru
 * Precte slova ze souboru, obsah uklada do pole a vraci delku slova
 * @param s     Pole znaku/retezec
 * @param max   Delka pole
 * @param f     Ukazatel na otevreny soubor
 * @return Delku nacteneho retezce; EOF pokud nastal konec souboru
 */
int read_word(char *s, int max, FILE *f);
#endif
/* io.h */
