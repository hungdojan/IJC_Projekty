/*
 * error.c
 * Reseni IJC-DU1, priklad b), 23.03.2021
 * Autor: Hung Do, FIT
 * Prelozeno: gcc 9.3
 *
 * Kostra pro vypis chybovych hlasek
 */
#include <stdarg.h>
#include <stdlib.h>     // exit()
#include <stdio.h>      // fprintf()
#include "error.h"

void warning_msg(const char *fmt, ... )
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Chyba:\n");
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void error_exit(const char *fmt, ... )
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Chyba:\n");
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}
/* error.c */
