#include "elmt_t.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(int *e)
{
	if (e == NULL)
		return;
	printf("%d", *e);
}

int compare_int(int *e1, int *e2)
{
	if (e1 == NULL || e2 == NULL)
		return 0;
	return *e1 - *e2;
}

Elmt_t *new_elmt(Elmt_t e)
{
	Elmt_t *elem;

	elem = malloc(sizeof(Elmt_t));
	if (elem == NULL)
		return NULL;
	*elem = e;
	return elem;
}

void free_elmt(Elmt_t *e)
{
	free(e);
}
