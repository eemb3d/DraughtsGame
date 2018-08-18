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

#ifndef DAMA_H_
#define DAMA_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mcheck.h>

/*Testing mode, 0 (false) test off, 1 (true) test on.*/
#define TEST			 0

/*Five available notations/simbols*/
#define LIGHT          	'b' /*Light piece notation*/
#define DARK           	'n' /*Dark piece notation.*/
#define LIGHT_KING		'B' /*Light king piece notation.*/
#define DARK_KING		'N' /*Dark king piece notation.*/
#define EMPTY     		' ' /*Empty piece notation.*/

/*Before a proposal for a draw can be made, at least 40 moves must have been made by each player.*/
#define WITHDRAW     	 40

/* ################## Naming Convention #######################
	Example ...
	a_dx -> Pointer to right above.
	a_sx -> Pointer to left above.
	b_dx -> Pointer to right below.
	b_sx -> Pointer to left below.

	lista_p -> list of pieces (p stands for piece)
	lista_d -> list of kings (d stands for king)
*/

/*boolean*/
typedef enum {false, true} boolean;

/*Cells structure*/
typedef struct cell{
    int pos; /*Cells position*/
	char simb; /*Simbol or notation.*/
	struct cell * a_dx; /*Pointer to right above.*/
	struct cell * a_sx; /*Pointer to left above.*/
	struct cell * b_dx; /*Pointer to right below.*/
	struct cell * b_sx; /*Pointer to left below.*/
}cell;

typedef cell *cella;

/* List structure */
typedef struct pedina{
	int    pos_p; /*Piece position on the board.*/
	struct pedina * next; /*Next piece.*/
}pedina;

typedef pedina *lista;

/*Player structure.*/
typedef struct gioc{
	int  num_p; /*Player number pieces.*/
	int  num_d; /*Player number kings.*/
	char color; /*Player color*/
	boolean program; /*Player is a program?*/
	lista lista_p; /*Player list pieces.*/
	lista lista_d; /*Player list kings .*/
}gioc;

/*Player type*/
typedef gioc * player;

/*Array of all 50 squares on the board*/
cell scac[51];

boolean player_exit;
boolean program_exit;

/* Count the number of movements.*/
int N_MOVEMENTS;

/*Macro.*/
#include "macro-par.h"

/*Function prototypes.*/
#include "prototype.h"

/*Internationalization*/
#include "../utils/en.h"   //English
//#include "../utils/it.h" //Italian


#endif /* DAMA_H_ */
