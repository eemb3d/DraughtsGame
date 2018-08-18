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

/*
	es.
	a_dx -> Pointer to right above.
	a_sx -> Pointer to left above.
	b_dx -> Pointer to right below.
	b_sx -> Pointer to left below.

	lista_p -> list of pieces (p stands for piece)
	lista_d -> list of kings (d stands for king)
	
	i_ad, i_as, i_bd, i_bs -> respectively int right above, int left above, int right below, int left below
	l_ad, l_as, l_bd, l_bs -> respectively list right above, list left above, list right below, list left below
*/

/*List with max number of pieces eatable from a normal piece.*/
lista l_max_p(cella father, cella a_d, cella a_s, cella b_d, cella b_s, lista list, char c){
	
	/*l_ad, l_as, l_bd, l_bs -> respectively list right above, list left above, list right below, list left below */
	lista l_ad = NULL, l_as = NULL, l_bd = NULL, l_bs = NULL;
	/*i_ad, i_as, i_bd, i_bs -> respectively int right above, int left above, int right below, int left below*/
	int i_ad = 0, i_as = 0, i_bd = 0, i_bs = 0, max = 0;

	if(!((m_p_a_d(a_d, c) && !checkDuplicates(list, a_d->pos)) || (m_p_a_s(a_s, c) && !checkDuplicates(list, a_s->pos)) ||
		 (m_p_b_d(b_d, c) && !checkDuplicates(list, b_d->pos)) || (m_p_b_s(b_s, c) && !checkDuplicates(list, b_s->pos)))){
		return (list != NULL) ? createList(list, father->pos) : list;
	}

	/*Recursively check if it can eat again, in each diagonaly direction.*/
	if (m_p_a_d(a_d, c) && !checkDuplicates(list, a_d->pos)){
		a_d = a_d->a_dx;/*Empty cell from where we start eat.*/
		l_ad = l_max_p(a_d, a_d->a_dx, a_d->a_sx, a_d->b_dx, NULL, createList(cloneList(list), a_d->b_sx->pos), c);
		i_ad = numElementsPerList(l_ad);
	}
	if (m_p_a_s(a_s, c) && !checkDuplicates(list, a_s->pos)){
		a_s = a_s->a_sx;
		l_as = l_max_p(a_s, a_s->a_dx, a_s->a_sx, NULL, a_s->b_sx, createList(cloneList(list), a_s->b_dx->pos), c);
		i_as = numElementsPerList(l_as);
	}
	if (m_p_b_d(b_d, c) && !checkDuplicates(list, b_d->pos)){
		b_d = b_d->b_dx;
		l_bd = l_max_p(b_d, b_d->a_dx, NULL, b_d->b_dx, b_d->b_sx, createList(cloneList(list), b_d->a_sx->pos), c);
		i_bd = numElementsPerList(l_bd);
	}
	if (m_p_b_s(b_s, c) && !checkDuplicates(list, b_s->pos)){
		b_s = b_s->b_sx;
		l_bs = l_max_p(b_s, NULL, b_s->a_sx, b_s->b_dx, b_s->b_sx, createList(cloneList(list), b_s->a_dx->pos), c);
		i_bs = numElementsPerList(l_bs);
	}

	/*Check which list has got the max number of pieces eatable.*/
	max = max4(i_ad, i_as, i_bd, i_bs);

	/*Return the max and delete all the other lists.*/
	if (max) {
		if (max == i_ad) {
			e_liste(l_as, l_bd, l_bs, list);
			list = l_ad;
		} else if (max == i_as) {
			e_liste(l_ad, l_bd, l_bs, list);
			list = l_as;
		} else if (max == i_bd) {
			e_liste(l_ad, l_as, l_bs, list);
			list = l_bd;
		} else if (max == i_bs) {
			e_liste(l_ad, l_as, l_bd, list);
			list = l_bs;
		}
	}
	return list;
}

/*List with max number of pieces eatable from a king.*/
lista l_max_d(cella father, lista list, char simb){

	int i_ad = 0, i_as = 0, i_bd = 0, i_bs = 0, max = 0, n_tmp = 0, p_mang = 0;

	lista l_ad = NULL, l_as = NULL, l_bd = NULL, l_bs = NULL, l_t = NULL;

    cella a_d = m_d_a_d(father->a_dx, simb), a_s = m_d_a_s(father->a_sx, simb),
    		b_d = m_d_b_d(father->b_dx, simb), b_s = m_d_b_s(father->b_sx, simb), c_max = NULL;

	if(!((a_d && !checkDuplicates(list, a_d->pos)) || (a_s && !checkDuplicates(list, a_s->pos)) ||
			(b_d && !checkDuplicates(list, b_d->pos)) || (b_s && !checkDuplicates(list, b_s->pos)))){
		return (list != NULL) ? (createList(list, father->pos)) : list;
	}

	/*Recursively check if it can eat again, in each diagonaly direction with a lot of possible movement,
	because the king can move freely multiple steps in any direction*/
	if (a_d && !checkDuplicates(list, a_d->pos)){
		for(p_mang = a_d->pos, a_d = a_d->a_dx; (a_d && isEmptyCell(a_d->pos)); a_d = a_d->a_dx){
			l_t = l_max_d(a_d, createList(cloneList(list), p_mang), simb);
			n_tmp = numElementsPerList(l_t);
			if (n_tmp > i_ad){
				i_ad = n_tmp;
				c_max = a_d;
			}
			l_t = deleteList(l_t);
		}
		l_ad = l_max_d(c_max, createList(cloneList(list), p_mang), simb);
	}

	if (a_s && !checkDuplicates(list, a_s->pos)){
		for(p_mang = a_s->pos, a_s = a_s->a_sx; (a_s && isEmptyCell(a_s->pos)); a_s = a_s->a_sx){
			l_t = l_max_d(a_s, createList(cloneList(list), p_mang), simb);
			n_tmp = numElementsPerList(l_t);
			if (n_tmp > i_as){
				i_as = n_tmp;
				c_max = a_s;
			}
			l_t = deleteList(l_t);
		}
		l_as = l_max_d(c_max, createList(cloneList(list), p_mang), simb);
	}

	if (b_d && !checkDuplicates(list, b_d->pos)){
		for(p_mang = b_d->pos, b_d = b_d->b_dx; (b_d && isEmptyCell(b_d->pos)); b_d = b_d->b_dx){
			l_t = l_max_d(b_d, createList(cloneList(list), p_mang), simb);
			n_tmp = numElementsPerList(l_t);
			if (n_tmp > i_bd){
				i_bd = n_tmp;
				c_max = b_d;
			}
			l_t = deleteList(l_t);
		}
		l_bd = l_max_d(c_max, createList(cloneList(list), p_mang), simb);
	}

	if (b_s && !checkDuplicates(list, b_s->pos)){
		for(p_mang = b_s->pos, b_s = b_s->b_sx; (b_s && isEmptyCell(b_s->pos)); b_s = b_s->b_sx){
			l_t = l_max_d(b_s, createList(cloneList(list), p_mang), simb);
			n_tmp = numElementsPerList(l_t);
			if (n_tmp > i_bs){
				i_bs = n_tmp;
				c_max = b_s;
			}
			l_t = deleteList(l_t);
		}
		l_bs = l_max_d(c_max, createList(cloneList(list), p_mang), simb);
	}

	max = max4(i_ad, i_as, i_bd, i_bs);

	if (max) {
		if (max == i_ad) {
			e_liste(l_as, l_bd, l_bs, list);
			list = l_ad;
		} else if (max == i_as) {
			e_liste(l_ad, l_bd, l_bs, list);
			list = l_as;
		} else if (max == i_bd) {
			e_liste(l_ad, l_as, l_bs, list);
			list = l_bd;
		} else if (max == i_bs) {
			e_liste(l_ad, l_as, l_bd, list);
			list = l_bs;
		}
	}
	return list;
}

/*Check if the king can eat righ above*/
cella m_d_a_d(cella a_d, char c){
	whileEmptyRightAbove(a_d);
	return (a_d && checkEatableEnemyPiecesForKing(a_d, a_d->a_dx, c)) ? a_d : NULL;
}

/*Check if the king can eat left above*/
cella m_d_a_s(cella a_s, char c){
	whileEmptyLeftAbove(a_s);
	return (a_s && checkEatableEnemyPiecesForKing(a_s, a_s->a_sx, c)) ? a_s : NULL;
}

/*Check if the king can eat righ below*/
cella m_d_b_d(cella b_d, char c){
	whileEmptyRightBelow(b_d);
	return (b_d && checkEatableEnemyPiecesForKing(b_d, b_d->b_dx, c)) ? b_d : NULL;
}

/*Check if the king can eat left below*/
cella m_d_b_s(cella b_s, char c){
	whileEmptyLeftBelow(b_s);
	return (b_s && checkEatableEnemyPiecesForKing(b_s, b_s->b_sx, c)) ? b_s : NULL;
}
