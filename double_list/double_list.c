#include "double_list.h"
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
	cell->prev = NULL;
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
	if (!is_empty(*l))
		(*l)->prev = new_cell;
	new_cell->next = *l;
	new_cell->prev = NULL;
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
	new_cell->prev = previous;
	if (previous->next != NULL)
		previous->next->prev = new_cell;
	previous->next = new_cell;
}

void insert_before(Cell *new_cell, Cell *next_cell)
{
	new_cell->prev = next_cell->prev;
	new_cell->next = next_cell;
	if (next_cell->prev != NULL)
		next_cell->prev->next = new_cell;
	next_cell->prev = new_cell;
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
		if (l2 != NULL)
			l2->prev = NULL;
		return;
	}
	current = *l1;
	while (current->next != NULL)
		current = current->next;
	insert_after(l2, current);
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
		if (c->next != NULL)
			c->next->prev = NULL;
		return 1;
	}
	current = *l;
	while (current->next != NULL)
	{
		if (current->next == c)
		{
			current->next = c->next;
			if (c->next != NULL)
				c->next->prev = current;
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
			current->prev = NULL;
			if (is_empty(removed))
				removed = current;
			else
			{
				Cell *temp = removed;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = current;
				current->prev = temp;
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
			current->prev = NULL;
			if (is_empty(cut))
				cut = current;
			else
			{
				Cell *temp = cut;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = current;
				current->prev = temp;
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
			current->prev = NULL;
			if (is_empty(cut))
				cut = current;
			else
			{
				Cell *temp = cut;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = current;
				current->prev = temp;
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
				check->prev = NULL;
				if (is_empty(duplicates))
					duplicates = check;
				else
				{
					Cell *temp = duplicates;
					while (temp->next != NULL)
						temp = temp->next;
					temp->next = check;
					check->prev = temp;
				}
			}
			check = next_check;
		}
		current = current->next;
	}
	return duplicates;
}
