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

/*We differentiate the player's move from the program.*/
void makeMove(player attacking, player attacked) {

	int num_max_pieces_captured = 0;

	/*Must eat first, then choose the list with the maximum number of pieces eaten, is used by the program
	 as a move to be made and by the human player as the type of move to be made, based on the number of pieces on the list*/
	lista list = listMaxNumberOfPiecesTaken(attacking);

	/*Program move.*/
	if(attacking->program){
		/*If it can not eat it moves a piece or king.*/
    	if(list == NULL) programMakeMove(attacking, attacked);
    	/*Otherwise, eat the list with the highest number of pieces*/
    	else list = captureAllElementOnList(list, attacking, attacked);
    }
	/*Player move.*/
    else{
    	if(list) {
    		num_max_pieces_captured = numElementsPerList(list)-2;
    		list = deleteList(list);
    	}
    	/*The player must choose which move he wants to make.*/
    	chooseMove(attacking, attacked, num_max_pieces_captured);
    }
	/*Increase the number of moves made by the players.*/
	N_MOVEMENTS++;
}

/*Return the list with the most number of pieces taken*/
lista listMaxNumberOfPiecesTaken(player attacking){
	char simb = attacking->color;
	int n_max = 1, n_tmp = 0, max = 0;
	lista list = NULL, l_d_gioc = NULL, l_pieces_player = NULL;
	cella cell = NULL;

	/*check in the list of the kings if I can eat*/
	for(l_d_gioc = attacking->lista_d; l_d_gioc != NULL; l_d_gioc = l_d_gioc->next){
		cell = &scac[l_d_gioc->pos_p];
		list = l_max_d(cell, list, simb);
		if (list){
			/*If the returned list is not NULL, register the number of elements present, if this exceeds the maximum value
			We update the maximum with the new value and store the pieces that has created this list*/
			n_tmp = numElementsPerList(list);
			list = deleteList(list);
			if (n_tmp > n_max){
				n_max = n_tmp;
				max = l_d_gioc->pos_p;
			}
		}
	}
	/*check in the list of the pieces if I can eat.*/
	for(l_pieces_player = attacking->lista_p; l_pieces_player != NULL; l_pieces_player = l_pieces_player->next){
		cell = &scac[l_pieces_player->pos_p];
		list = l_max_p(cell, cell->a_dx, cell->a_sx, cell->b_dx, cell->b_sx, list, simb);
		if (list){
			n_tmp = numElementsPerList(list);
			list = deleteList(list);
			if (n_tmp > n_max){
				n_max = n_tmp;
				max = l_pieces_player->pos_p;
			}
		}
	}

	/*If max is non-zero it means that it is the attacking piece with the greatest number of eaten pieces*/
	if(max){
		cell = &scac[max];

		if(dama(cell->simb)){
			list = createList(l_max_d(cell, list, simb), max);
		}else{
			list = createList(l_max_p(cell, cell->a_dx, cell->a_sx, cell->b_dx, cell->b_sx, list, simb), max);
		}
	}
	return list;
}

/*Update the data structures of the players and the board based on the pieces eaten.*/
lista captureAllElementOnList(lista l_player_move, player attacking, player attacked){

	lista l_tmp = l_player_move;

	/*The first elements of the list are the pieces eaten by the attacker and then update the attacker*/
	while(!isEmptyCell(l_player_move->pos_p)){
		updateAttackedPlayer(attacked, l_player_move->pos_p);
		l_player_move = l_player_move->next;
	}
	
	/* the last two elements of the list are respectively the destination cell and the origin cell
	   from which the attacker's move started. */
	updateAttackingPlayer(attacking, l_player_move->next->pos_p, l_player_move->pos_p);
	l_tmp = deleteList(l_tmp);

	return l_tmp;
}

/*Update the members of the attacked player by deleting the pieces 'pos' in his list*/
void updateAttackedPlayer(player attacked, int pos){
	/*If it has been eaten a king*/
	if(dama(scac[pos].simb)){
		attacked->lista_d = deleteElement(attacked->lista_d, pos);
		attacked->num_d--;
	}else {
		attacked->lista_p = deleteElement(attacked->lista_p, pos);
		attacked->num_p--;
	}
	/*Update the chessboard*/
	scac[pos].simb = EMPTY;
}

/*Update the cells in the chessboard after any move, and the members of the attacking player*/
void updateAttackingPlayer(player attacking, int orig, int dest){

	char c = scac[orig].simb;

	/*Is a king.*/
	if(dama(c))	modifyListOfKings(attacking->lista_d, orig, dest);

	/*Check if a piece became a king.*/
	else if((c == LIGHT && (base_dama_b(dest))) || (c == DARK && (base_dama_n(dest)))){
		attacking->num_p--;
		attacking->num_d++;
		attacking->lista_d = createList(attacking->lista_d, dest);
		attacking->lista_p = deleteElement(attacking->lista_p, orig);
		c = c-32;
	}
	/*Is a normal piece.*/
	else attacking->lista_p = modifyListOfPieces(attacking->lista_p, orig, dest);
	
	/*Update destination and origin cells after a move.*/
	scac[dest].simb = c; scac[orig].simb = EMPTY;
}
