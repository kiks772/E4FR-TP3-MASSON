#ifndef LIST_H
#define LIST_H

#include "elmt_t.h"

/* Structure d'une cellule */
typedef struct Cell
{
	Elmt_t *data;
	struct Cell *next;
} Cell;

/* Type d'une liste (pointeur vers une cellule) */
typedef Cell *List;

/**
 * is_empty - Teste si une liste est vide
 * @l: la liste
 *
 * Retourne: 1 si vide, 0 sinon
 */
int is_empty(List l);

/**
 * create_empty_list - Crée une liste vide
 *
 * Retourne: une liste vide (NULL)
 */
List create_empty_list(void);

/**
 * print_list - Affiche une liste
 * @l: la liste
 * @print_elmt: pointeur vers la fonction d'affichage d'un élément
 *
 * Affiche les éléments séparés par des virgules, entre [ et ]
 */
void print_list(List l, void (*print_elmt)(Elmt_t *));

/**
 * create_cell - Crée une cellule
 * @n: pointeur vers l'Elmt_t
 *
 * Retourne: adresse de la nouvelle cellule ou NULL en cas d'erreur
 */
Cell *create_cell(Elmt_t *n);

/**
 * free_cell - Libère une cellule
 * @c: pointeur vers la cellule à libérer
 */
void free_cell(Cell *c);

/**
 * insert_first - Insère un élément en tête de liste
 * @n: pointeur vers l'Elmt_t
 * @l: pointeur vers la liste
 *
 * Retourne: adresse de la nouvelle liste ou NULL en cas d'erreur
 */
Cell *insert_first(Elmt_t *n, List *l);

/**
 * free_list - Libère toute une liste
 * @l: pointeur vers la liste
 */
void free_list(List *l);

/**
 * insert_last - Insère un élément en queue de liste
 * @n: pointeur vers l'Elmt_t
 * @l: pointeur vers la liste
 *
 * Retourne: adresse de la nouvelle liste ou NULL en cas d'erreur
 */
Cell *insert_last(Elmt_t *n, List *l);

/**
 * insert_after - Insère une cellule après une autre
 * @new_cell: cellule à insérer
 * @previous: cellule après laquelle insérer
 */
void insert_after(Cell *new_cell, Cell *previous);

/**
 * search - Recherche un élément dans la liste (non triée)
 * @e: élément à rechercher
 * @l: liste
 * @compare_elmt: fonction de comparaison
 *
 * Retourne: pointeur vers la cellule contenant l'élément ou NULL
 */
Cell *search(Elmt_t *e, List l, int (*compare_elmt)(Elmt_t *, Elmt_t *));

/**
 * length - Retourne la taille d'une liste
 * @l: liste
 *
 * Retourne: nombre de cellules
 */
int length(List l);

/**
 * concatenate - Concatène deux listes
 * @l1: première liste (modifiée)
 * @l2: deuxième liste (reste inchangée)
 */
void concatenate(List *l1, List l2);

/**
 * mirror_it - Inverse une liste de façon itérative
 * @l: pointeur vers la liste
 */
void mirror_it(List *l);

/**
 * mirror_rec - Inverse une liste de façon récursive
 * @l: pointeur vers la liste
 */
void mirror_rec(List *l);

/**
 * search_k - Retourne la k-ème cellule de la liste
 * @k: position (1-indexée)
 * @l: liste
 *
 * Retourne: pointeur vers la k-ème cellule ou NULL
 */
Cell *search_k(int k, List l);

/**
 * sorted_search - Recherche dans une liste triée
 * @e: élément à rechercher
 * @l: liste triée
 * @res: pointeur vers pointeur (pour stocker la cellule trouvée)
 * @compare_elmt: fonction de comparaison
 *
 * Retourne: 1 si trouvé, 0 sinon
 * res pointera sur la cellule trouvée ou sur le dernier maillon
 * avec un élément plus petit que e
 */
int sorted_search(Elmt_t *e, List l, Cell **res,
				  int (*compare_elmt)(Elmt_t *, Elmt_t *));

/**
 * remove_cell - Retire une cellule de la liste
 * @c: cellule à retirer
 * @l: pointeur vers la liste
 *
 * Retourne: 1 si c était bien dans la liste, 0 sinon
 */
int remove_cell(Cell *c, List *l);

/**
 * remove_all - Retire toutes les occurrences d'un élément
 * @l: pointeur vers la liste
 * @e: élément à retirer
 * @compare_elmt: fonction de comparaison
 *
 * Retourne: liste contenant tous les éléments retirés
 */
List remove_all(List *l, Elmt_t *e,
				int (*compare_elmt)(Elmt_t *, Elmt_t *));

/**
 * cut_sup - Enlève tous les maillons avec une valeur supérieure à e
 * @l: pointeur vers la liste
 * @e: élément de référence
 * @compare_elmt: fonction de comparaison
 *
 * Retourne: liste contenant tous les éléments retirés
 */
List cut_sup(List *l, Elmt_t *e,
			 int (*compare_elmt)(Elmt_t *, Elmt_t *));

/**
 * cut_inf - Enlève tous les maillons avec une valeur inférieure à e
 * @l: pointeur vers la liste
 * @e: élément de référence
 * @compare_elmt: fonction de comparaison
 *
 * Retourne: liste contenant tous les éléments retirés
 */
List cut_inf(List *l, Elmt_t *e,
			 int (*compare_elmt)(Elmt_t *, Elmt_t *));

/**
 * canonicalyze - Enlève tous les doublons
 * @l: liste
 * @compare_elmt: fonction de comparaison
 *
 * Retourne: liste contenant tous les doublons retirés
 */
List canonicalyze(List l, int (*compare_elmt)(Elmt_t *, Elmt_t *));

#endif /* LIST_H */
