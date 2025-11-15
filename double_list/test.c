#include <stdio.h>
#include <stdlib.h>
#include "double_list.h"
#include "elmt_t.h"

int main(void)
{
	List list;
	List list2;
	List removed;
	Cell *found;
	Elmt_t *e1, *e2, *e3, *e4, *e5, *e6;
	Elmt_t target;

	printf("=== Test 1 : Création d'une liste vide ===\n");
	list = create_empty_list();
	printf("La liste est-elle vide ? %d\n", is_empty(list));
	printf("Liste : ");
	print_list(list, print_int);
	printf("\n\n");

	printf("=== Test 2 : Insertion en tête ===\n");
	e1 = new_elmt(10);
	e2 = new_elmt(20);
	e3 = new_elmt(30);
	insert_first(e1, &list);
	insert_first(e2, &list);
	insert_first(e3, &list);
	printf("Après insertion de 30, 20, 10 en tête :\n");
	printf("Liste : ");
	print_list(list, print_int);
	printf("\nLongueur : %d\n\n", length(list));

	printf("=== Test 3 : Insertion en queue ===\n");
	e4 = new_elmt(40);
	e5 = new_elmt(50);
	insert_last(e4, &list);
	insert_last(e5, &list);
	printf("Après insertion de 40, 50 en queue :\n");
	printf("Liste : ");
	print_list(list, print_int);
	printf("\nLongueur : %d\n\n", length(list));

	printf("=== Test 4 : Recherche ===\n");
	target = 30;
	found = search(&target, list, compare_int);
	printf("Recherche de 30 : %s\n", found != NULL ? "Trouvé" : "Non trouvé");
	target = 100;
	found = search(&target, list, compare_int);
	printf("Recherche de 100 : %s\n\n", found != NULL ? "Trouvé" : "Non trouvé");

	printf("=== Test 5 : Recherche k-ième élément ===\n");
	found = search_k(1, list);
	printf("1er élément : ");
	if (found) print_int(found->data);
	printf("\n");
	found = search_k(3, list);
	printf("3ème élément : ");
	if (found) print_int(found->data);
	printf("\n\n");

	printf("=== Test 6 : Parcours en sens inverse ===\n");
	Cell *last = list;
	while (last != NULL && last->next != NULL)
		last = last->next;
	printf("Dernier élément : ");
	if (last) print_int(last->data);
	printf("\nÉlément précédent : ");
	if (last && last->prev)
		print_int(last->prev->data);
	printf("\n\n");

	printf("=== Test 7 : Concaténation ===\n");
	list2 = create_empty_list();
	e6 = new_elmt(60);
	Elmt_t *e7 = new_elmt(70);
	insert_last(e6, &list2);
	insert_last(e7, &list2);
	printf("Liste 1 : ");
	print_list(list, print_int);
	printf("\nListe 2 : ");
	print_list(list2, print_int);
	printf("\n");
	concatenate(&list, list2);
	printf("Après concaténation : ");
	print_list(list, print_int);
	printf("\n\n");

	printf("=== Test 8 : Suppression de toutes les occurrences ===\n");
	List list3 = create_empty_list();
	for (int i = 0; i < 5; i++)
	{
		Elmt_t *tmp = new_elmt(i % 2 == 0 ? 5 : 10);
		insert_last(tmp, &list3);
	}
	printf("Liste 3 (avec doublons) : ");
	print_list(list3, print_int);
	printf("\n");
	Elmt_t target_remove = 5;
	removed = remove_all(&list3, &target_remove, compare_int);
	printf("Après suppression de tous les 5 : ");
	print_list(list3, print_int);
	printf("\nSupprimés : ");
	print_list(removed, print_int);
	printf("\n\n");

	printf("=== Test 9 : Découpage sup et inf ===\n");
	List list4 = create_empty_list();
	for (int i = 1; i <= 5; i++)
	{
		Elmt_t *tmp = new_elmt(i * 10);
		insert_last(tmp, &list4);
	}
	printf("Liste 4 : ");
	print_list(list4, print_int);
	printf("\n");
	Elmt_t threshold = 25;
	List sup = cut_sup(&list4, &threshold, compare_int);
	printf("Après cut_sup(25) : ");
	print_list(list4, print_int);
	printf("\nSupprimés (>25) : ");
	print_list(sup, print_int);
	printf("\n");
	Elmt_t threshold2 = 35;
	List inf = cut_inf(&list4, &threshold2, compare_int);
	printf("Après cut_inf(35) : ");
	print_list(list4, print_int);
	printf("\nSupprimés (<35) : ");
	print_list(inf, print_int);
	printf("\n\n");

	printf("=== Test 10 : Canonicalisation ===\n");
	List list5 = create_empty_list();
	int values[] = {1, 2, 2, 3, 3, 3, 4, 4, 5};
	for (int i = 0; i < 9; i++)
	{
		Elmt_t *tmp = new_elmt(values[i]);
		insert_last(tmp, &list5);
	}
	printf("Liste 5 (avec doublons) : ");
	print_list(list5, print_int);
	printf("\n");
	List duplicates = canonicalyze(list5, compare_int);
	printf("Après canonicalisation : ");
	print_list(list5, print_int);
	printf("\nDoublons : ");
	print_list(duplicates, print_int);
	printf("\n\n");

	printf("=== Test 11 : Recherche triée ===\n");
	List sorted_list = create_empty_list();
	int sorted_values[] = {10, 20, 30, 40, 50};
	for (int i = 0; i < 5; i++)
	{
		Elmt_t *tmp = new_elmt(sorted_values[i]);
		insert_last(tmp, &sorted_list);
	}
	printf("Liste triée : ");
	print_list(sorted_list, print_int);
	printf("\n");
	Elmt_t search_val = 25;
	Cell *res = NULL;
	int found_flag = sorted_search(&search_val, sorted_list, &res, compare_int);
	printf("Recherche 25 : %s, position avant : %s\n",
		   found_flag ? "Trouvé" : "Non trouvé",
		   res != NULL ? "ok" : "NULL");

	/* Free all lists */
	free_list(&list);
	free_list(&list3);
	free_list(&list4);
	free_list(&sup);
	free_list(&inf);
	free_list(&list5);
	free_list(&duplicates);
	free_list(&sorted_list);
	free_list(&removed);

	printf("Tous les tests sont terminés !\n");
	return 0;
}
