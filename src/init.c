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

/** Initialize board. Each of the fifty dark squares has a number (1 through 50). Number 46 is at the left corner 
seen from the player with the light pieces. Number 5 is at the left corner seen from the player with the dark pieces. */
void initBoard(){

    int n = 50, x, y, z, i, e;

	/*Initialize dark pieces.*/
	for (i = 1; i < 21; i++) {
		scac[i].simb = DARK;
		scac[i].pos = i;
	}/*Initialize empty pieces.*/
	for (i = 21; i < 31; i++) {
		scac[i].simb = EMPTY;
		scac[i].pos = i;
	}/*Initialize light pieces.*/
	for (i = 31; i < 51; i++) {
		scac[i].simb = LIGHT;
		scac[i].pos = i;
	}

	/*Initialize each pieces with the close one through pointer. Four pointers for each diagonal direction.*/
	/*Initialize the pointers with a view to the right side*/
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
	/*Initialize the pointers with a view to the lefth side*/
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
}

/** Initializes player. */
player initPlayer(char color){

	player g_tmp = malloc(sizeof(gioc));

    g_tmp->num_p = 20;
    g_tmp->num_d = 0;
    g_tmp->color = color;
    g_tmp->program = false;
    g_tmp->lista_p = initPlayerList(color);
    g_tmp->lista_d = NULL;

    return g_tmp;
}

/** Initializes player list pieces. */
lista initPlayerList(char c){
	lista tmp_list = NULL;
	int position;

    if (c == DARK) {//The lower-leftmost square should be dark
    	for(position = 20; position > 0; position--)
    		tmp_list = createList(tmp_list, position);
    }else{
    	for(position = 31; position < 51 ; position++)
    		tmp_list = createList(tmp_list, position);
    }
    return tmp_list;
}

char chooseColor(){
    char color[21];

    do {
    	printf(MSG_CHOSE_COLOR);
    	fgets(color, 21, stdin);
	} while (!(*color == LIGHT || *color == DARK) || (int)strlen(color)-1 != 1);

    printf(MSG_COLOR);
  	(*color == LIGHT)? printf("%s.\n", PLAYER_LIGHT) : printf("%s.\n", PLAYER_DARK);
    
    return (*color);
}

/*Prints gameboard*/
void printGameBoard(player player_b, player player_n) {
    printf("\n\n%s\n%s\n%s\n%s\n",	"____________________________________________________________________________", MSG_BOARD_PLAYER_D,
    							"          _______       _______       _______       _______       _______   ",
    							" ||||||||1       ||||||2       ||||||3       ||||||4       ||||||5       || ");
    printf("%s%c%s%c%s%c%s%c%s%c%s\n", " |||||||||   ", scac[1].simb, "   |||||||   ", scac[2].simb, "   |||||||   ", scac[3].simb, "   |||||||   ", scac[4].simb, "   |||||||   ", scac[5].simb, "   || ");
    printf("%s%s%d\n", 			" |||||||||_______|||||||_______|||||||_______|||||||_______|||||||_______|| ", MSG_BOARD_PIECES_D, player_n->num_p);
    printf("%s%s%d\n",			 " |6       ||||||7       ||||||8       ||||||9       |||||10       ||||||||| ", MSG_BOARD_KING_D, player_n->num_d);
    printf("%s%c%s%c%s%c%s%c%s%c%s\n", " ||   ", scac[6].simb, "   |||||||   ", scac[7].simb, "   |||||||   ", scac[8].simb, "   |||||||   ", scac[9].simb, "   |||||||   ", scac[10].simb, "   ||||||||| ");
    printf("%s\n%s\n", 			" ||_______|||||||_______|||||||_______|||||||_______|||||||_______||||||||| ",	" |||||||11       |||||12       |||||13       |||||14       |||||15       || ");
    printf("%s%c%s%c%s%c%s%c%s%c%s\n", " |||||||||   ", scac[11].simb, "   |||||||   ", scac[12].simb, "   |||||||   ", scac[13].simb, "   |||||||   ", scac[14].simb, "   |||||||   ", scac[15].simb, "   || ");
    printf("%s\n%s\n", 			" |||||||||_______|||||||_______|||||||_______|||||||_______|||||||_______|| ",	" 16       |||||17       |||||18       |||||19       |||||20       ||||||||| ");
    printf("%s%c%s%c%s%c%s%c%s%c%s\n", " ||   ", scac[16].simb, "   |||||||   ", scac[17].simb, "   |||||||   ", scac[18].simb, "   |||||||   ", scac[19].simb, "   |||||||   ", scac[20].simb, "   ||||||||| ");
    printf("%s\n%s\n", 			" ||_______|||||||_______|||||||_______|||||||_______|||||||_______||||||||| ",	" |||||||21       |||||22       |||||23       |||||24       |||||25       || ");
    printf("%s%c%s%c%s%c%s%c%s%c%s\n", " |||||||||   ", scac[21].simb, "   |||||||   ", scac[22].simb, "   |||||||   ", scac[23].simb, "   |||||||   ", scac[24].simb, "   |||||||   ", scac[25].simb, "   || ");
    printf("%s\n%s\n", 			" |||||||||_______|||||||_______|||||||_______|||||||_______|||||||_______|| ",	" 26       |||||27       |||||28       |||||29       |||||30       ||||||||| ");
    printf("%s%c%s%c%s%c%s%c%s%c%s\n", " ||   ", scac[26].simb, "   |||||||   ", scac[27].simb, "   |||||||   ", scac[28].simb, "   |||||||   ", scac[29].simb, "   |||||||   ", scac[30].simb, "   ||||||||| ");
    printf("%s\n%s\n", 			" ||_______|||||||_______|||||||_______|||||||_______|||||||_______||||||||| ",	" |||||||31       |||||32       |||||33       |||||34       |||||35       || ");
    printf("%s%c%s%c%s%c%s%c%s%c%s\n", " |||||||||   ", scac[31].simb, "   |||||||   ", scac[32].simb, "   |||||||   ", scac[33].simb, "   |||||||   ", scac[34].simb, "   |||||||   ", scac[35].simb, "   || ");
    printf("%s%s%d\n", 			" |||||||||_______|||||||_______|||||||_______|||||||_______|||||||_______|| ", MSG_BOARD_PIECES_L, player_b->num_p);
    printf("%s%s%d\n", 				" 36       |||||37       |||||38       |||||39       |||||40       ||||||||| ", MSG_BOARD_KING_L, player_b->num_d);
    printf("%s%c%s%c%s%c%s%c%s%c%s\n", " ||   ", scac[36].simb, "   |||||||   ", scac[37].simb, "   |||||||   ", scac[38].simb, "   |||||||   ", scac[39].simb, "   |||||||   ", scac[40].simb, "   ||||||||| ");
    printf("%s\n%s\n", 			" ||_______|||||||_______|||||||_______|||||||_______|||||||_______||||||||| ",	" |||||||41       |||||42       |||||43       |||||44       |||||45       || ");
    printf("%s%c%s%c%s%c%s%c%s%c%s\n", " |||||||||   ", scac[41].simb, "   |||||||   ", scac[42].simb, "   |||||||   ", scac[43].simb, "   |||||||   ", scac[44].simb, "   |||||||   ", scac[45].simb, "   || ");
    printf("%s\n%s\n", 			" |||||||||_______|||||||_______|||||||_______|||||||_______|||||||_______|| ", " 46       |||||47       |||||48       |||||49       |||||50       ||||||||| ");
    printf("%s%c%s%c%s%c%s%c%s%c%s\n", " ||   ", scac[46].simb, "   |||||||   ", scac[47].simb, "   |||||||   ", scac[48].simb, "   |||||||   ", scac[49].simb, "   |||||||   ", scac[50].simb, "   ||||||||| ");
    printf("%s\n%s\n%s\n\n",		" ||_______|||||||_______|||||||_______|||||||_______|||||||_______||||||||| ",
    								" __________________________________________________________________________ ", MSG_BOARD_PLAYER_L);
}

/*Frees player memory structure*/
void deletePlayer(player  player_x) {
	player_x->lista_d = deleteList(player_x->lista_d);
	player_x->lista_p = deleteList(player_x->lista_p);
	free(player_x);
	player_x = NULL;
}
