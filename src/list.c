/*
*   Copyright (C) <2012>  <eemb3d at gm...ail dot com>
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "../include/dama.h"

/* Creates list of pieces. Add the element at the end of the list.*/
lista createList(lista list, int n) {
	lista l_tmp, l_inc, elem = createNewElementOnList(n);

	if (list == NULL) return elem;

	for (l_tmp = list, l_inc = list->next; l_inc != NULL; l_tmp = l_tmp->next, l_inc = l_inc->next)
		;

	/*Add the new element in the list.*/
	l_tmp->next = elem;
	l_tmp = NULL;
	return list;
}

/*Creates a new element of the list with the position passed.*/
lista createNewElementOnList(int posizione_cella) {
	lista elem = NULL;

	if (!(elem = (lista) malloc(sizeof(struct pedina)))) {
		fprintf(stderr, ERR_MALLOC);
		exit(EXIT_FAILURE);
	}

	elem->pos_p = posizione_cella;
	elem->next = NULL;

	return elem;
}

/*Delete List*/
lista deleteList(lista list) {
	lista list_tmp = NULL;

	if (list != NULL) {
		for (list_tmp = list->next; list_tmp != NULL; list = list_tmp, list_tmp = list_tmp->next)
			free(list);

		free(list);
		list = NULL;
		list_tmp = NULL;
	}
	return NULL;
}

/*Counts number of elements in the list*/
int numElementsPerList(lista l) {
	int i = 0;

	for (; l != NULL; l = l->next, i++)
		;
	return i;
}

/*Check repetition. Check if in the list we have already considered the same element or position*/
boolean checkDuplicates(lista list, int ped) {
	for (; (list && list->pos_p != ped); list = list->next)
		;
	if (list && list->pos_p == ped)
		return true;

	return false;
}

/*Delete the element from the list.*/
lista deleteElement(lista list, int pos) {
	
	lista list_tmp = list, l = list;

	if (list != NULL) {
		/*Check if it is in the first position (head).*/
		if (list->pos_p == pos) {
			l = l->next;
			free(list);
			list = NULL;
		} else {

			for (list = list->next; (list && list->pos_p != pos); list_tmp = list_tmp->next, list = list->next)
				;
			
			if (list != NULL && list->pos_p == pos) {
				/*Concatenate the "two" list.*/
				list_tmp->next = list->next;
				free(list);
				list = NULL;
			}
		}
		list_tmp = NULL;
	}
	return l;
}

/*Modifies the list to make it in order ...*/
lista modifyListOfPieces(lista l_pass, int vechia_pos, int nuova_pos) {
	lista new_element = NULL, l_tmp = NULL, l_inc = NULL;

	new_element = createNewElementOnList(nuova_pos);
	l_pass = deleteElement(l_pass, vechia_pos);

	if (l_pass == NULL)	return new_element;

	l_tmp = l_pass;
	l_inc = l_pass->next;

	/*... increasing*/
	if (scac[vechia_pos].simb == LIGHT) {
		if (nuova_pos < l_tmp->pos_p) {
			new_element->next = l_tmp;
			l_pass = new_element;
		} else {
			for (; (l_inc != NULL && nuova_pos > l_inc->pos_p); l_tmp = l_tmp->next, l_inc = l_inc->next)
				;
			if (nuova_pos > l_tmp->pos_p) {
				l_tmp->next = new_element;
				new_element->next = l_inc;
			}
		}
	}
	/*... decreasing*/
	else {
		if (nuova_pos > l_tmp->pos_p) {
			new_element->next = l_tmp;
			l_pass = new_element;
		}
		for (; (l_inc != NULL && nuova_pos < l_inc->pos_p);	l_tmp = l_tmp->next, l_inc = l_inc->next)
			;
		if (nuova_pos < l_tmp->pos_p) {
			l_tmp->next = new_element;
			new_element->next = l_inc;
		}
	}
	l_tmp = NULL;
	l_inc = NULL;
	return l_pass;
}

/*Modify list of kings*/
void modifyListOfKings(lista lista_dame, int x, int y) {
	for (; (lista_dame && lista_dame->pos_p != x); lista_dame = lista_dame->next)
		;
	if (lista_dame && lista_dame->pos_p == x)
		lista_dame->pos_p = y;
}

/*Clone the list*/
lista cloneList(lista lista_da_clonare) {
	lista l_tmp = NULL;
	for (; lista_da_clonare; l_tmp = createList(l_tmp, lista_da_clonare->pos_p), lista_da_clonare =	lista_da_clonare->next)
		;
	return l_tmp;
}
