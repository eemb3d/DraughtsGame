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

int main(){

	
#if TEST
    /*Test environment.*/
    player player_l = malloc(sizeof(gioc));
    player player_d = malloc(sizeof(gioc));
    initTest(player_l, player_d);
#else

    player player_l, player_d;
    char color;

    /*Strategy board game initialization*/
    initBoard();
    player_l = initPlayer(LIGHT);
    player_d = initPlayer(DARK);
    color = chooseColor();

    /*Who is the program?*/
    if (color == LIGHT)
    	player_d->program = true;
    else
    	player_l->program = true;

#endif

    player_exit = false;
    program_exit = false;
    N_MOVEMENTS = 0;

    /*Start trace*/
    mtrace();

    while(true){
    	/*Light player is playing.*/
    	if(!playerLost(player_l) && !player_exit && !program_exit){
    		printGameBoard(player_l, player_d);
    		makeMove(player_l, player_d);
    	}else break;
    	/*Dark player is playing*/
    	if(!playerLost(player_d) && !player_exit && !program_exit){
    		printGameBoard(player_l, player_d);
    		makeMove(player_d, player_l);
    	}else break;
    }

    /*Prints game board status*/
	printGameBoard(player_l, player_d);

	/*Prints players status*/
	if (playerLost(player_d)) {
		printf("%s%s\n\n", MSG_WINNER, PLAYER_LIGHT);
	} else if (playerLost(player_l)) {
		printf("%s%s\n\n", MSG_WINNER, PLAYER_DARK);
	} else if (player_exit) {
		printf(MSG_SURRENDER);
	} else if (program_exit) {
		printf(MSG_NO_VALID_MOVE_REMAINING);
	}

    /*Frees players memory structures.*/
    deletePlayer(player_l);
    deletePlayer(player_d);

    /* End trace */
	muntrace();

    return EXIT_SUCCESS;
}

