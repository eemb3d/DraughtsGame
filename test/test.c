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

#if 0
Test Vari
/*Insieme di pedine e dame poste in modo casuale nello scacchiere*/
	int N_P_B = 4; /*Numero pedine bianche.*/
	int N_P_N = 4; /*Numero pedine nere.*/
	int P_P_B[] = { 11, 31, 32, 40 }; /*Posizione pedine bianche - Ordine crescente*/
	int P_P_N[] = { 39, 22, 14, 7 }; /*Posizione pedine nere - Ordine decrescente*/
	/*Dame*/
	int N_D_B = 4; /*Numero dame bianche.*/
	int N_D_N = 3; /*Numero dame nere.*/
	int P_D_B[] = { 26, 33, 41, 35 }; /*Posizione dame bianche*/
	int P_D_N[] = { 1, 2, 3 }; /*Posizione dame nere*/
/*################################################################################*/
/*Verifica della presa lunda da parte della Dama*/
	int N_P_B = 0; /*Numero pedine bianche.*/
	int N_P_N = 4; /*Numero pedine nere.*/
	int P_P_B[0]; /*Posizione pedine bianche - Ordine crescente*/
	int P_P_N[] = {27, 20, 13, 10}; /*Posizione pedine nere - Ordine decrescente*/
	/*Dame*/
	int N_D_B = 2; /*Numero dame bianche.*/
	int N_D_N = 4; /*Numero dame nere.*/
	int P_D_B[] = {3, 25}; /*Posizione dame bianche*/
	int P_D_N[] = {2, 8, 11, 35}; /*Posizione dame nere*/

	/*--Un altro esempio dello stesso tipo- Verifica figura 8 del sito "pergioco.net..."*/
	int N_P_B = 0; /*Numero pedine bianche.*/
	int N_P_N = 4; /*Numero pedine nere.*/
	int P_P_B[0]; /*Posizione pedine bianche - Ordine crescente*/
	int P_P_N[] = {27, 18, 11, 8}; /*Posizione pedine nere - Ordine decrescente*/
	/*Dame*/
	int N_D_B = 1; /*Numero dame bianche.*/
	int N_D_N = 1; /*Numero dame nere.*/
	int P_D_B[] = {36}; /*Posizione dame bianche*/
	int P_D_N[] = {9}; /*Posizione dame nere*/

	/*--Un altro esempio dello stesso tipo- Verifica figura 12 del sito "wikipedia.org..."*/
	int N_P_B = 0; /*Numero pedine bianche.*/
	int N_P_N = 10; /*Numero pedine nere.*/
	int P_P_B[] = {0}; /*Posizione pedine bianche - Ordine crescente*/
	int P_P_N[] = {44, 43, 33, 31, 30, 20, 19, 17, 9, 7}; /*Posizione pedine nere - Ordine decrescente*/
	/*Dame*/
	int N_D_B = 1; /*Numero dame bianche.*/
	int N_D_N = 0; /*Numero dame nere.*/
	int P_D_B[] = {1}; /*Posizione dame bianche*/
	int P_D_N[] = {0}; /*Posizione dame nere*/
	/* Risultato di "valgrind --leak-check=full ./dama" relativo alla mossa precedente!!!!
	==7499==
	==7499== HEAP SUMMARY:
	==7499==     in use at exit: 0 bytes in 0 blocks
	==7499==   total heap usage: 265,052 allocs, 265,052 frees, 4,240,864 bytes allocated
	==7499==
	==7499== All heap blocks were freed -- no leaks are possible
	==7499==
	==7499== For counts of detected and suppressed errors, rerun with: -v
	==7499== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 4 from 4)*/
/*#################################################################################*/
/*Verifica della presa lunga da parte della pedina normale.*/
	int N_P_B = 1; /*Numero pedine bianche.*/
	int N_P_N = 5; /*Numero pedine nere.*/
	int P_P_B[] = {47}; /*Posizione pedine bianche - Ordine crescente*/
	int P_P_N[] = {42, 32, 23, 22, 24}; /*Posizione pedine nere - Ordine decrescente*/
	/*Dame*/
	int N_D_B = 2; /*Numero dame bianche.*/
	int N_D_N = 2; /*Numero dame nere.*/
	int P_D_B[] = {3, 25}; /*Posizione dame bianche*/
	int P_D_N[] = {2, 8}; /*Posizione dame nere*/
/*Cinque pedine per player.*/
	int N_P_B = 5; /*Numero pedine bianche.*/
	int N_P_N = 5; /*Numero pedine nere.*/
	int P_P_B[] = {41, 42, 43, 44, 45}; /*Posizione pedine bianche - Ordine crescente*/
	int P_P_N[] = {10, 9, 8, 7, 6}; /*Posizione pedine nere - Ordine decrescente*/
	/*Dame*/
	int N_D_B = 0; /*Numero dame bianche.*/
	int N_D_N = 0; /*Numero dame nere.*/
	int P_D_B[] = {0}; /*Posizione dame bianche*/
	int P_D_N[] = {0}; /*Posizione dame nere*/

/*##################################################################################*/

#endif

void initTest(player g_b, player g_n) {

	int N_P_B = 0; /*Num. light pieces.*/
	int N_P_N = 10; /*Num. dark pieces.*/
	int P_P_B[] = {0}; /*Places light pieces*/
	int P_P_N[] = {44, 43, 33, 31, 30, 20, 19, 17, 9, 7}; /*Places dark pieces*/
	
	/*kings/crowned*/
	int N_D_B = 1; /*Num. king light pieces.*/
	int N_D_N = 0; /*Num. king dark pieces.*/
	int P_D_B[] = {1}; /*Places king light pieces*/
	int P_D_N[] = {0}; /*Places king dark pieces*/

	/*########################################################################*/
	int n = 50, x, y, z, i, e;

	/*Init empty cells.*/
	for (i = 1; i < 51; i++) {
		scac[i].simb = EMPTY;
		scac[i].pos = i;
	}

	/*Init pieces cells.*/
	for (i = 0; N_P_N != 0 && i < N_P_N; i++) {
		scac[P_P_N[i]].simb = DARK;
		scac[P_P_N[i]].pos = P_P_N[i];
	}
	for (i = 0; N_P_B != 0 && i < N_P_B; i++) {
		scac[P_P_B[i]].simb = LIGHT;
		scac[P_P_B[i]].pos = P_P_B[i];
	}

	/*Init kings/crowned cells.*/
	for (i = 0; N_D_N != 0 && i < N_D_N; i++) {
		scac[P_D_N[i]].simb = DARK_KING;
		scac[P_D_N[i]].pos = P_D_N[i];
	}
	for (i = 0; N_D_B != 0 && i < N_D_B; i++) {
		scac[P_D_B[i]].simb = LIGHT_KING;
		scac[P_D_B[i]].pos = P_D_B[i];
	}

	/*Init gameboard pointers cells */
	for (z = 1; z <= 5; z++) {
		for (y = z; y < n; y += 10) {
			x = y + 5;
			scac[y].b_sx = &scac[x];
			scac[x].a_dx = &scac[y];
			e = y + 10;
			if (e < n) {
				scac[x].b_dx = &scac[e];
				scac[e].a_sx = &scac[x];
			}
		}
	}
	for (z = 1; z < 5; z++) {
		for (y = z; y < n; y += 10) {
			x = y + 6;
			scac[y].b_dx = &scac[x];
			scac[x].a_sx = &scac[y];
			e = y + 10;
			if (e < n) {
				scac[x].b_sx = &scac[e];
				scac[e].a_dx = &scac[x];
			}
		}
	}

	/*Init light player*/
	g_b->num_p = N_P_B;
	g_b->num_d = N_D_B;
	g_b->color = LIGHT;
	g_b->program = true;
	g_b->lista_p = initTestList(P_P_B, N_P_B);
	g_b->lista_d = initTestList(P_D_B, N_D_B);
	
	/*Init dark player*/
	g_n->num_p = N_P_N;
	g_n->num_d = N_D_N;
	g_n->color = DARK;
	g_n->program = false;
	g_n->lista_p = initTestList(P_P_N, N_P_N);
	g_n->lista_d = initTestList(P_D_N, N_D_N);

}

/*Initialization player test list.*/
lista initTestList(int *a, int n) {
	int i = 0;
	lista list = NULL;
	for (; n != 0 && i < n; i++)
		list = createList(list, a[i]);
	return list;
}
