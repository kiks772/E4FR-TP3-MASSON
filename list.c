#include "list.h"
#include <stdlib.h>
#include <stdio.h>

int is_empty(List l)
{
	return l == NULL;
}

List create_empty_list(void)
{
	return NULL;
}

void print_list(List l, void (*print_elmt)(Elmt_t *))
{
	Cell *current;

	printf("[");
	current = l;
	while (current != NULL)
	{
		print_elmt(current->data);
		current = current->next;
		if (current != NULL)
			printf(", ");
	}
	printf("]");
}

Cell *create_cell(Elmt_t *n)
{
	Cell *cell;

	cell = malloc(sizeof(Cell));
	if (cell == NULL)
		return NULL;
	cell->data = n;
	cell->next = NULL;
	return cell;
}

void free_cell(Cell *c)
{
	free(c);
}

Cell *insert_first(Elmt_t *n, List *l)
{
	Cell *new_cell;

	new_cell = create_cell(n);
	if (new_cell == NULL)
		return NULL;
	new_cell->next = *l;
	*l = new_cell;
	return new_cell;
}

void free_list(List *l)
{
	Cell *current;
	Cell *next;

	current = *l;
	while (current != NULL)
	{
		next = current->next;
		free_elmt(current->data);
		free_cell(current);
		current = next;
	}
	*l = NULL;
}

void insert_after(Cell *new_cell, Cell *previous)
{
	new_cell->next = previous->next;
	previous->next = new_cell;
}

Cell *insert_last(Elmt_t *n, List *l)
{
	Cell *new_cell;
	Cell *current;

	new_cell = create_cell(n);
	if (new_cell == NULL)
		return NULL;
	if (is_empty(*l))
	{
		*l = new_cell;
		return new_cell;
	}
	current = *l;
	while (current->next != NULL)
		current = current->next;
	insert_after(new_cell, current);
	return new_cell;
}

Cell *search(Elmt_t *e, List l, int (*compare_elmt)(Elmt_t *, Elmt_t *))
{
	Cell *current;

	current = l;
	while (current != NULL)
	{
		if (compare_elmt(current->data, e) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}

int length(List l)
{
	int count;
	Cell *current;

	count = 0;
	current = l;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return count;
}

void concatenate(List *l1, List l2)
{
	Cell *current;

	if (is_empty(*l1))
	{
		*l1 = l2;
		return;
	}
	current = *l1;
	while (current->next != NULL)
		current = current->next;
	current->next = l2;
}

static void _mirror_rec_helper(Cell *current, Cell **prev)
{
	if (current == NULL)
		return;
	_mirror_rec_helper(current->next, prev);
	if (*prev != NULL)
		(*prev)->next = current;
	current->next = NULL;
	*prev = current;
}

void mirror_rec(List *l)
{
	Cell *prev;

	if (is_empty(*l) || (*l)->next == NULL)
		return;
	prev = NULL;
	_mirror_rec_helper(*l, &prev);
	*l = prev;
}

void mirror_it(List *l)
{
	Cell *prev;
	Cell *current;
	Cell *next;

	if (is_empty(*l) || (*l)->next == NULL)
		return;
	prev = NULL;
	current = *l;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*l = prev;
}

Cell *search_k(int k, List l)
{
	int count;
	Cell *current;

	if (k <= 0)
		return NULL;
	count = 1;
	current = l;
	while (current != NULL && count < k)
	{
		current = current->next;
		count++;
	}
	return current;
}

int sorted_search(Elmt_t *e, List l, Cell **res,
				  int (*compare_elmt)(Elmt_t *, Elmt_t *))
{
	Cell *current;

	*res = NULL;
	current = l;
	while (current != NULL && compare_elmt(current->data, e) < 0)
	{
		*res = current;
		current = current->next;
	}
	if (current != NULL && compare_elmt(current->data, e) == 0)
		return (*res = current, 1);
	return 0;
}

int remove_cell(Cell *c, List *l)
{
	Cell *current;

	if (c == NULL || l == NULL || is_empty(*l))
		return 0;
	if (*l == c)
	{
		*l = c->next;
		return 1;
	}
	current = *l;
	while (current->next != NULL)
	{
		if (current->next == c)
		{
			current->next = c->next;
			return 1;
		}
		current = current->next;
	}
	return 0;
}

List remove_all(List *l, Elmt_t *e,
				int (*compare_elmt)(Elmt_t *, Elmt_t *))
{
	List removed;
	Cell *current;
	Cell *next;

	removed = create_empty_list();
	current = *l;
	while (current != NULL)
	{
		next = current->next;
		if (compare_elmt(current->data, e) == 0)
		{
			remove_cell(current, l);
			current->next = NULL;
			if (is_empty(removed))
				removed = current;
			else
			{
				Cell *temp = removed;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = current;
			}
		}
		current = next;
	}
	return removed;
}

List cut_sup(List *l, Elmt_t *e,
			 int (*compare_elmt)(Elmt_t *, Elmt_t *))
{
	List cut;
	Cell *current;
	Cell *next;

	cut = create_empty_list();
	current = *l;
	while (current != NULL)
	{
		next = current->next;
		if (compare_elmt(current->data, e) > 0)
		{
			remove_cell(current, l);
			current->next = NULL;
			if (is_empty(cut))
				cut = current;
			else
			{
				Cell *temp = cut;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = current;
			}
		}
		current = next;
	}
	return cut;
}

List cut_inf(List *l, Elmt_t *e,
			 int (*compare_elmt)(Elmt_t *, Elmt_t *))
{
	List cut;
	Cell *current;
	Cell *next;

	cut = create_empty_list();
	current = *l;
	while (current != NULL)
	{
		next = current->next;
		if (compare_elmt(current->data, e) < 0)
		{
			remove_cell(current, l);
			current->next = NULL;
			if (is_empty(cut))
				cut = current;
			else
			{
				Cell *temp = cut;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = current;
			}
		}
		current = next;
	}
	return cut;
}

List canonicalyze(List l, int (*compare_elmt)(Elmt_t *, Elmt_t *))
{
	List duplicates;
	Cell *current;
	Cell *check;
	Cell *next_check;

	duplicates = create_empty_list();
	current = l;
	while (current != NULL && current->next != NULL)
	{
		check = current->next;
		while (check != NULL)
		{
			next_check = check->next;
			if (compare_elmt(current->data, check->data) == 0)
			{
				remove_cell(check, &l);
				check->next = NULL;
				if (is_empty(duplicates))
					duplicates = check;
				else
				{
					Cell *temp = duplicates;
					while (temp->next != NULL)
						temp = temp->next;
					temp->next = check;
				}
			}
			check = next_check;
		}
		current = current->next;
	}
	return duplicates;
}
