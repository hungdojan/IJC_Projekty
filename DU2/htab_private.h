/*
 * htab_private.h        
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Privatni hlavickovy soubor s definicemi struktur a
 *      funkci htab_item
 */
#ifndef __HTAB_PRIVATE_H__
#define __HTAB_PRIVATE_H__

#include "htab.h"

/**
 * @struct Struktura jedne polozky v tabulce
 * Vyuziti linked listu
 */
typedef struct htab_item
{
    htab_pair_t *pair;      /**< Zaznam skladajici se z klice a hodnoty */
    struct htab_item *next; /**< Ukazatel na nasledujici polozku */
} htab_item_t;

/**
 * @struct Struktura hashovaci tabulky
 */
struct htab
{
    size_t size;            /**< Aktualni pocet zaznamu */
    size_t arr_size;        /**< Velikost nasledujiciho pole */
    htab_item_t *ptr[];     /**< Flexibilni pole ukazatelu na polozku se zaznamy */
};

/**
 * @brief Inicializace zaznamu
 * Nastavuje vychozi hodnotu htab_pair_t::value na 0
 *
 * @param key Jmeno klice
 * @return Ukazatel na alokovanou pamet inicializovane struktury; NULL pokud se to nepovedlo
 */
htab_item_t *htab_item_init(htab_key_t key);

/**
 * @brief Uvolni alokovanou pamet zaznamu
 *
 * @param item Ukazatel na pamet zaznamu
 * @return Ukazatel na nasledujici zaznam; NULL pokud je zaznam posledni ve vetvi
 */
htab_item_t *htab_item_free(htab_item_t *item);

#endif
/* htab_private.h */
