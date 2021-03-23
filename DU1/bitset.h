/*
 * bitset.h
 * Reseni IJC-DU1, priklad a), 23.03.2021
 * Autor: Hung Do, FIT
 * Prelozeno: gcc 9.3
 *
 * Definice maker a inline funkci pro praci s bitset
 */
#ifndef _BITSET_H
#define _BITSET_H
#include <assert.h>     // assert()
#include <stdlib.h>     // calloc(), free()
#include <limits.h>     // CHAR_BIT
#include "error.h"

typedef unsigned long ul;
typedef ul bitset_index_t;
typedef ul * bitset_t;

#define GET_INDEX(index) ((index) / (sizeof(ul) * CHAR_BIT) + 1)
#define GET_BIT(index)   ((index) % (sizeof(ul) * CHAR_BIT))

/**
 * @brief Vytvori staticke/automaticke pole bitu
 *
 * @param name Jmeno pole
 * @param size Pocet bitu
 */
#define bitset_create(name, size) \
    ul name[GET_INDEX(size) + 1] = { 0, };                    \
    static_assert(size > 0, "Pole je spatne inicializovane"); \
    name[0] = (size)    // ulozeni poctu bitu do prvniho prvku

/**
 * @brief Alokuje misto pro pole bitu
 * 
 * Pokud neprobehne alokace uspesne, vypise se chybove hlaseni a ukoknci se program
 *
 * @param name Jmeno pole
 * @param size Pocet bitu
 */
#define bitset_alloc(name, size) \
    assert((size) > 0);                                             \
    bitset_t name = calloc(GET_INDEX(size) + 1 , sizeof(ul));       \
    if (name == NULL)                                               \
        error_exit("bitset_alloc: Chyba alokace paměti\n");         \
    name[0] = (size)    // ulozeni poctu bitu do prvniho prvku

/**
 * @brief Uvolni alokovanou pamet
 *
 * @param name Jmeno pole
 */
#define bitset_free(name) \
    free(name)

#ifdef USE_INLINE
/**
 * @brief Vraci pocet pouzitelnych bitu
 *
 * @param name Bitove pole
 * @return Index nejvetisho mozneho pouzitelneho bitu
 */
inline ul bitset_size(const bitset_t name) {
    return name[0];
}

/**
 * @brief Nastavuje hodnotu bitu
 *
 * Pokud VALUE nebude 0 nebo 1 a INDEX bude mimo rozsah 0..bitset_size(),
 * program vypise chybove hlaseni a ukonci program
 *
 * @param name Bitove pole
 * @param index Index bitu, jehoz hodnota se ma nastavit
 * @param value Hodnota, ktera se ma nastavit
 */
inline void bitset_setbit(bitset_t name, const bitset_index_t index, const int value) {
    // kontrola rozsahu 0..bitset_size()
    if (index > bitset_size(name))
        error_exit("bitset_setbit: Index %lu je mimo rozsah 0..%lu\n", 
                  (ul)index, (ul)(bitset_size(name)));

    if (value)
        name[GET_INDEX(index)] |= 1UL << GET_BIT(index);
    else
        name[GET_INDEX(index)] ^= 1UL << GET_BIT(index);
}

/**
 * @brief Vraci hodnotu na vybranem indexu
 *
 * Pokud je INDEX mimo rozsah 0..bitset_size(),
 * vypise program chybove hlaseni a ukonci program
 *
 * @param name Bitove pole
 * @param index Index bitu, jehoz hodnota se ma nastavit
 * @return 0UL, pokud je na danem bitu nastavena hodnota 0; jinak kladne cislo
 */
inline ul bitset_getbit(const bitset_t name, const bitset_index_t index) {
    // kontrola rozsahu 0..bitset_size()
    if (index > bitset_size(name))
        error_exit("bitset_setbit: Index %lu je mimo rozsah 0..%lu\n",
                  (ul)index, (ul)(bitset_size(name)));
    
    return name[GET_INDEX(index)] & (1UL << GET_BIT(index));
}

#else
    /**
     * @brief Vraci pocet pouzitelnych bitu
     *
     * @param name Jmeno pole
     */
    #define bitset_size(name) name[0]

    /**
     * @brief Nastavuje bit na vybranem indexu
     * 
     * Pokud INDEX bude mimo rozsah 0..bitset_size(),
     * program vypise chybove hlaseni a ukonci program
     *
     * @param name Jmeno pole
     * @param index Urcuje, na kolikatem bitu se na hodnota nastavit
     * @param value Hodnota, ktera se ma nastavit
     */
    #define bitset_setbit(name, index, value) do {                          \
        if ((index) > bitset_size(name))                                    \
            error_exit("bitset_setbit: Index %lu je mimo rozsah 0..%lu\n",  \
                   (ul)index, (ul)(bitset_size(name)));                     \
        \
        if (value)                                                          \
            name[GET_INDEX(index)] |= 1UL << GET_BIT(index);                \
        else                                                                \
            name[GET_INDEX(index)] ^= 1UL << GET_BIT(index);                \
    } while(0)

    /**
     * @brief Vraci hodnotu na vybranem indexu
     *
     * Pokud je INDEX mimo rozsah 0..bitset_size(),
     * vypise program chybove hlaseni a ukonci program
     *
     * @param name Jmeno pole
     * @param index Urcuje, na hodnotu kolikate bitu se uzivatel pta
     */
    #define bitset_getbit(name, index)                                   \
        (((index) > bitset_size(name)) ?                                 \
         (error_exit("bitset_setbit: Index %lu je mimo rozsah 0..%lu\n", \
                   (ul)index, (ul)(bitset_size(name))), 0) :             \
         name[GET_INDEX(index)] & (1UL << GET_BIT(index)))
#endif

#endif
/* bitset.h */
