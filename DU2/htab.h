/*
 * htab.h
 * Reseni IJC-DU2, priklad 2), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * API se strukturou a funkcemi tabulky s rozptylenymi polozkami (hash table)
 */
#ifndef __HTAB_H__
#define __HTAB_H__

#include <string.h>     // size_t
#include <stdbool.h>    // bool

// Definice struktury; pretypovani nekterych tabulkovych datovych typu
struct htab;
typedef struct htab htab_t;

typedef const char *htab_key_t;
typedef int htab_value_t;

/**
 * @struct Struktura dvojice
 */
typedef struct htab_pair
{
    htab_key_t    key;    /**< Klic; identifikator dvojice   */
    htab_value_t  value;  /**< Hodnota; ulozena data dvojice */
} htab_pair_t;

/**
 * @brief Hashovaci funkce
 * Vypocita podle zadaneho algoritmu ciselnou hodnotu klice
 *
 * @param str   Klic zaznamu
 * @return      Ciselna hodnota klice
 */
size_t htab_hash_function(htab_key_t str);

/**
 * @brief Inicializuje strukturu
 *
 * @param n     Velikost pole ukazatelu
 * @return      Ukazatel na alokovanou pamet; NULL v pripade neuspechu
 */
htab_t *htab_init(size_t n);

/**
 * @brief Presune data z jedne tabulky do druhe
 *
 * @param n     Velikost pole uzakatelu
 * @return      Ukazatel na novou tabulku
 */
htab_t *htab_move(size_t n, htab_t *from);

/**
 * @breif Vraci pocet polozek v tabulce
 *
 * @param t     Ukazatel na tabulku
 * @return      Pocet polozek v tabulce
 */
size_t htab_size(const htab_t *t);

/**
 * @brief Vraci velikost pole ukazatelu na polozky
 *
 * @param t     Ukazatel na tabulku
 * @return      Velikost pole ukazatelu na polozky
 */
size_t htab_bucket_count(const htab_t *t);

/**
 * @brief Hleda zaznam v tabulce podle klice
 *
 * @param t     Ukazatel na tabulku
 * @param key   Klic zaznamu
 * @return      Ukazatel na nalezeny zaznam; 
 *     pokud zadny zaznam s klicem nebyl nalezen, je vracen NULL
 */
htab_pair_t * htab_find(htab_t * t, htab_key_t key);

/**
 * @brief Vyhleda zaznma v tabulce podle klice
 * V pripadene nenalezeni vytvori novy zaznam
 *
 * @param t     Ukazatel na tabulku
 * @param key   Klic zaznamu
 * @return      Ukazatel na zaznam s danym klicem
 */
htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key);

/**
 * @brief Hleda zaznam s klicem v tabulce a smaze ho
 *
 * @param t     Ukazatel na tabulku
 * @oaram key   Klic, podle ktereho se vyhledava
 * @return      true, pokud se podarilo smazat zaznam (zaznam se nachazel v tabulce)
 */
bool htab_erase(htab_t * t, htab_key_t key);

/**
 * @brief Uplatni na vsechny zaznamy v tabulce zadanou funkci
 *
 * @param t     Ukazatel na tabulku
 * @param *f    Ukazatel na funkci; ktera se provede nad vsemi daty
 */
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t * data));

/**
 * @brief Odstrani vsechny zaznmy v tabulce
 *
 * @param t     Ukazatel na tabulku
 */
void htab_clear(htab_t *t);

/**
 * @brief Uvolni vsechnu alokovanou pamet v tabulce
 *
 * @param t     Ukazatel na tabulku
 */
void htab_free(htab_t *t);

#endif
/* htab.h */
