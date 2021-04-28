/*
 * tail.c        
 * Reseni IJC-DU2, priklad 1), 20.04.2021
 * Autor: Hung Do, FIT VUT
 * Prelozeno: gcc 9.3
 *
 * Implementace GNU programu "tail" jazykem C
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 511
#define DEFAULT_LINES 10

// Vraci index prvniho znaku v poli
#define GET_INDEX(index, len) ((index) * (len))

/**
 * @brief Naalokuje pamet pro pole retezcu
 * Vyuziti jednorozmerneho pole pro ulozeni nekolika retezcu
 * Pristup k poli:
 *      arr[index * num_of_lines + offset];
 *
 * @param num_of_lines  Pocet prvku v poli (pocet radku k naalokovani)
 * @param str_length    Maximalni velikost retezce
 * @return Odkaz na prvni prvek v poli, NULL pokud se nepovede alokovat
 */
char *malloc_lines(const int num_of_lines, const int str_length)
{
    // alokace delky retezce + 2 dodatecne znaky pro znak konce radku a retezce
    char *lines = calloc(num_of_lines * (str_length + 2), 1);
    return lines;
}

/**
 * @brief Preskoci prvnich X radku a vypise zbytek souboru
 *
 * @param num_of_lines  Pocet preskocenych radku
 * @param str_length    Maximalni velikost retezce
 * @param file          Ukazatel na otevreny soubor
 */
void print_without_head(const int num_of_lines, const int str_length, FILE *f)
{
    int c;              /** Nacteny znak */
    int counter = 0;    /** Pocita pocet nactenych radku */
    int overflow = 0;   /** Prepinac indikuje, zda nacteny radek je delsi nez limit */
    int index = 1;      /** Poradi radku */

    while ((c = fgetc(f)) != EOF)
    {
        // nacteni znaku konce radku
        if (c == '\n')
        {
            if (index >= num_of_lines)  { putchar(c); }
            index++;
            counter = 0;
        }
        // prekroceni limitu
        else if (counter == str_length)
        {
            if (!overflow)  // vypis se provede jen jednou
            {
                overflow = 1;
                fprintf(stderr, "Nacteny radek prekrocil maximalni limit delky radku\n");
            }
        }
        // ulozeni znaku do pole
        else
        {
            if (index >= num_of_lines)  { putchar(c); }
            counter++;
        }
    }
}

/**
 * @brief Nacitani dat ze souboru
 * Dochazi k cyklickemu zapisu; Pokud se index pretece, zacne se zapisovat od zacatku
 *     NOL = num_of_lines
 *     0->1->2->...->(NOL-2)->(NOL-1)->0->1->...
 * 
 * @post  index-1 je index posledniho nacteneho retezce
 *        funkce neuzavira soubor
 *
 * @param lines         Pole znaku
 * @param num_of_lines  Velikost pole retezcu
 * @param str_length    Maximalni delka retezce
 * @param index         Index retezce, do ktereho se zacina zapisovat [out]
 * @param file          Ukazatel na otevreny soubor
 */
void load_data(char *lines, const int num_of_lines, 
               const int str_length, int *index, FILE *file)
{
    int c;              /** Nacteny znak */
    int counter = 0;    /** Pocita pocet nactenych znaku */
    int overflow = 0;   /** Prepinac indikuje, zda nacteny radek je delsi nez limit */

    while ((c = fgetc(file)) != EOF)
    {
        // konec nacitani radku
        if (c == '\n')
        {
            lines[GET_INDEX(*index, str_length+2) + counter++] = '\n';
            lines[GET_INDEX(*index, str_length+2) + counter] = '\0';
            counter = 0;
            // posun indexu na dalsi "radek"; uplatneni zacykleni
            (*index)++;
            *index %= num_of_lines;
            overflow = 0;
        }
        // prekroceni limitu
        else if (counter == str_length)
        {
            if (!overflow)  // vypis se provede jen jednou
            {
                overflow = 1;
                fprintf(stderr, "Nacteny radek prekrocil maximalni limit delky radku\n");
            }
        }
        // ulozeni znaku do pole
        else
        {
            lines[GET_INDEX(*index, str_length+2) + counter] = c;
            counter++;
        }
    }
    // pokud nastane EOF driv nez '\n'
    if (counter != 0)
    {
        lines[GET_INDEX(*index, str_length+2) + counter] = '\0';
        (*index)++;
        *index %= num_of_lines;
    }
}

/**
 * @brief Vypise obsah retezcu na STDOUT
 *
 * @param lines         Pole retezcu
 * @param num_of_lines  Velikost pole retezcu
 * @param str_length    Maximalni delka retezce
 * @param index         Index retezce, od ktereho se zacina cist
 */
void print_data(const char *lines, const int num_of_lines,
                const int str_length, int index)
{
    for (int i = 0; i < num_of_lines; i++)
    {
        if (lines[GET_INDEX(index, str_length + 2)])
            printf("%s", &(lines[GET_INDEX(index, str_length+2)]));

        // posun na dalsi radek
        index++;
        index %= num_of_lines;
    }
}

/**
 * @brief Uvolneni pameti
 *
 * @param arr_lines     Pole retezcu
 */
void free_lines(char *lines)
{
    free(lines);
}

int main(int argc, char *argv[])
{
    char *lines = NULL;                 /**< Pole retezcu */
    int num_of_lines = DEFAULT_LINES;   /**< Velikost pole retezcu */
    int index = 0;                      /**< Index v poli retezcu */
    int plus_sign_toggle = 0;           /**< Prepinac vypisu vsech radku krome prvnich X radku */
    FILE *f = NULL;

    // nacitani argumentu
    for (int i = 1; i < argc; i++)
    {
        // -n prepinac
        if (!strcmp(argv[i], "-n") && i+1 < argc)
        {
            char *endptr = NULL;
            int load_number = strtol(argv[i+1], &endptr, 10);
            plus_sign_toggle = argv[i+1][0] == '+';     // nacteni znaku +

            if (load_number <= 0 || endptr == NULL)
                goto error_arguments;
            i++;

            num_of_lines = load_number;
        }
        else        // nacitani souboru/neznamy prikaz
        {
            if (f == NULL)
            {
                f = fopen(argv[i], "r");
                // Nepodarilo se otevrit soubor
                if (f == NULL)
                    goto error_arguments;
            }
            else
                goto error_arguments;
        }
    }

    // Nacitani z STDIN
    if (f == NULL)
        f = stdin;

    // inicializace pole
    if (!plus_sign_toggle)
    {
        lines = malloc_lines(num_of_lines, MAX_LEN);
        if (lines == NULL)     { goto error_memory; }
    }

    // prace s daty
    if (plus_sign_toggle)
        print_without_head(num_of_lines, MAX_LEN, f);
    else
    {
        load_data(lines, num_of_lines, MAX_LEN, &index, f);
        print_data(lines, num_of_lines, MAX_LEN, index);
    }

    // uklid
    free_lines(lines);
    fclose(f);
    return EXIT_SUCCESS;

error_arguments:
    fprintf(stderr, "Error: spatne vstupni argumenty\n");
    if (f != NULL)      { fclose(f); }
    return EXIT_FAILURE;
error_memory:
    fprintf(stderr, "Error: nepodarilo se alokovat pamet\n");
    free_lines(lines);
    return EXIT_FAILURE;
}
/* tail.c */
