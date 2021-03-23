/*
 * error.h
 * Reseni IJC-DU1, priklad b), 23.03.2021
 * Autor: Hung Do, FIT
 * Prelozeno: gcc 9.3
 */
#ifndef _ERROR_H
#define _ERROR_H

/**
 * @brief Vytiskne na stderr chybove hlaseni
 *
 * @param fmt Formatovaci text
 */
extern void warning_msg(const char *fmt, ...);

/**
 * @brief Vytiskne na stderr chybove hlaseni a ukonci program
 *      s odpovidaji navratovou hodnotou
 *
 * @param fmt Formatovaci text
 */
extern void error_exit(const char *fmt, ...);

#endif
/* error.h */
