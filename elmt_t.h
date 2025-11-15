#ifndef ELMT_T_H
#define ELMT_T_H

#include <stddef.h>

/* Type de l'élément */
typedef int Elmt_t;

/**
 * print_int - Affiche un int passé par adresse
 * @e: pointeur vers l'int à afficher
 */
void print_int(int *e);

/**
 * compare_int - Compare deux ints passés par adresse
 * @e1: pointeur vers le premier int
 * @e2: pointeur vers le deuxième int
 *
 * Retourne:
 *  un nombre négatif si e1 < e2
 *  0 si e1 == e2
 *  un nombre positif si e1 > e2
 */
int compare_int(int *e1, int *e2);

/**
 * new_elmt - Alloue dynamiquement un Elmt_t
 * @e: valeur à copier
 *
 * Retourne: adresse de l'Elmt_t alloué ou NULL en cas d'erreur
 */
Elmt_t *new_elmt(Elmt_t e);

/**
 * free_elmt - Libère la mémoire associée à un Elmt_t
 * @e: pointeur vers l'Elmt_t à libérer
 */
void free_elmt(Elmt_t *e);

#endif /* ELMT_T_H */
