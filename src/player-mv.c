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

/* ################## Naming Convention #######################
	es.
	a_dx -> Pointer to right above.
	a_sx -> Pointer to left above.
	b_dx -> Pointer to right below.
	b_sx -> Pointer to left below.

	lista_p -> list of pieces (p stands for piece)
	lista_d -> list of kings (d stands for king)
*/


/*Player makes move. Has to respect the syntax xx-xx...*/
void chooseMove(player attacking, player attacked, int numero_max_pedine_mangiabili) {

	boolean mossa_valida = false;
	int numero_caratteri_mossa;
	int num_letters;
	/*Max number of letters needed to capture 20 pieces.*/
	char line[56];

	while (!mossa_valida) {

		printf(MSG_MAKE_MOVE);

		while (fgets(line, 56, stdin) == NULL)
			fprintf(stderr, ERR_MOVE);
		
		/*Less the return carriage.*/
		numero_caratteri_mossa = (int) strlen(line) - 1;
		
		/*Check if the player wants to exit.*/
		num_letters = strlen(MSG_EXIT) - 1;
		if (strncmp(line, MSG_EXIT, num_letters) == 0 && numero_caratteri_mossa == num_letters) {
			if (N_MOVEMENTS >= WITHDRAW) {
				mossa_valida = true;
				player_exit = true;
			} else
				fprintf(stderr, ERR_SURRENDER);
		}
		
		/*Move is not correct.*/
		else if (numero_caratteri_mossa > 5 && numero_max_pedine_mangiabili < 2)
			fprintf(stderr, ERR_SINTASSI_MOSSA);
		
		/*Check if we have captured the max number of pieces*/
		else if (numero_caratteri_mossa < 6 && numero_max_pedine_mangiabili > 1)
			fprintf(stderr, ERR_MUST_CAPTURE_MAX_NUMBER); 
		
		/*If we have more then one pieces to be captured.*/
		else if (numero_max_pedine_mangiabili > 1)
			mossa_valida = checkHaveChosenToCaptureTheMax(attacking, attacked, line, numero_max_pedine_mangiabili);
		
		/*Moves or captures just one piece.*/
		else
			mossa_valida = checkMoveValidity(attacking, attacked, line, numero_max_pedine_mangiabili);
	}
}

/*Check the move and if we have chosen to capture the max one.*/
boolean checkHaveChosenToCaptureTheMax(player attacking, player attacked, char *mossa, int num) {

	char *cell = NULL, simb;
	int ped = 0, inizio = 0, cont = 0;
	boolean mossa_lunga_effettuata = false, mossa_lunga_valida = true;
	lista l_pedine_vuote = NULL, l_pedine_mangiate = NULL;

	/*The first piece should be from the opposite side ...*/
	cell = strtok(mossa, "-");
	if (cell) inizio = atoi(cell);

	/*... Start check it*/
	if (inizio && inizio > 0 && inizio < 51 && myPieces(inizio, attacking->color)) {
		
		/*Start list of empty pieces that we have indicated*/
		l_pedine_vuote = createList(l_pedine_vuote, inizio);
		simb = scac[inizio].simb;
		
		cell = strtok(NULL, "-");
		
		if (cell) ped = atoi(cell);

		while (cell != NULL && mossa_lunga_valida) {
			/*Check the validity of empty pieces...*/
			if (!cell || !ped || ped < 1 || ped > 50 || !isEmptyCell(ped)	|| checkDuplicates(l_pedine_vuote, ped) || cont == num) {
				fprintf(stderr, ERR_MOVE);
				mossa_lunga_valida = false;
			} else {
				l_pedine_vuote = createList(l_pedine_vuote, ped);
				cont++;
			}
			cell = strtok(NULL, "-");
			if (cell) ped = atoi(cell);
		}
		
		/*... checked the syntax, now we have to check the semantic*/
		if (mossa_lunga_valida && cont == num) {
			/*Now we start list of pieces eaten*/
			l_pedine_mangiate =	(dama(simb)) ? listPiecesCapturedByKing(l_pedine_vuote, simb + 32, num) : listPiecesCapturedByPiece(l_pedine_vuote, simb, num);
		
			if (l_pedine_mangiate) {
				l_pedine_mangiate = captureAllElementOnList(l_pedine_mangiate, attacking, attacked);
				mossa_lunga_effettuata = true;
			} else
				fprintf(stderr, ERR_MOVE);
		}
		
		/*Delete lists*/
		l_pedine_mangiate = deleteList(l_pedine_mangiate);
		l_pedine_vuote = deleteList(l_pedine_vuote);
	} else
		fprintf(stderr, ERR_MOVE);

	return mossa_lunga_effettuata;
}

/*Check moves validity ...*/
boolean checkMoveValidity(player attacking, player attacked, char* mossa, int max_num_eatable_pieces) {
	
	char *origin = NULL, *destination = NULL;
	int p_orig = 0, p_dest = 0;
	boolean found = false;

	origin = strtok(mossa, "-");
	destination = strtok(NULL, "\n");

	if (origin) p_orig = atoi(origin);
	if (destination) p_dest = atoi(destination);
	
	origin = NULL;
	destination = NULL;

	if (!p_orig || !p_dest)
		fprintf(stderr, ERR_SINTASSI_MOSSA);

	else if (p_orig < 0 || p_orig > 50 || p_dest < 0 || p_dest > 50)
		fprintf(stderr, ERR_ORIGIN_CELL_INVALID);

	else if (isEmptyCell(p_orig) || enemyPieces(p_orig, attacking->color))
		fprintf(stderr, ERR_ORIGIN_PIECE_IS_NOT_YOUR_COLOR);

	else if (!isEmptyCell(p_dest))
		fprintf(stderr, ERR_DESTINATION_CELL_OCCUPIED);

	else
		found = checkSemanticMove(attacking, attacked, p_orig, p_dest, max_num_eatable_pieces);
	
	return found;
}

/* Check the semantics move, in case there are errors, a message will be printed. */
boolean checkSemanticMove(player attacking, player attacked, int orig,	int dest, int max_num_eatable_pieces) {

	cella cel = &scac[orig], a_d = cel->a_dx, a_s = cel->a_sx, b_d = cel->b_dx, b_s = cel->b_sx;
	char simb = cel->simb;
	boolean check_move = false;
	lista list = NULL, list_eatable_piece = NULL;

	/*If max_num_eatable_pieces is zero we can only move, so we check if the move is correct.*/
	if (max_num_eatable_pieces == 0) {
		
		/*Light move*/
		if (simb == LIGHT && (found(a_d, dest) || found(a_s, dest)))
			check_move = true;
		
		/*Dark move*/
		else if (simb == DARK && (found(b_d, dest) || found(b_s, dest)))
			check_move = true;
		
		/*The king is moving*/
		else if (dama(simb)) {
		
			findDestinationRightAbove(a_d, dest);
			if (found(a_d, dest))	
				check_move = true;

			if (!check_move) {
				findDestinationLeftAbove(a_s, dest);
				if (found(a_s, dest))	check_move = true;
			}

			if (!check_move) {
				findDestinationRightBelow(b_d, dest);
				if (found(b_d, dest))	check_move = true;
			}

			if (!check_move) {
				findDestinationLeftBelow(b_s, dest);
				if (found(b_s, dest))	check_move = true;
			}
		}

		if (!check_move)
			fprintf(stderr, ERR_DESTINATION_CELL_INVALID);
		else
			updateAttackingPlayer(attacking, orig, dest);
	} else {
		/*Create the list with two element, the origin and destination piece.*/
		list = createList(createList(list, orig), dest);
		
		/*Create the list of captured pieces.*/
		list_eatable_piece =
				(dama(simb)) ? listPiecesCapturedByKing(list, simb + 32, max_num_eatable_pieces) : listPiecesCapturedByPiece(list, simb, max_num_eatable_pieces);
		list = deleteList(list);
		
		/*If null the origin and or destination are incorrect.*/
		if (list_eatable_piece) {
			if (found(cel->a_dx, dest) || found(cel->a_sx, dest) || found(cel->b_dx, dest) || found(cel->b_sx, dest)) {
				/*Has decided to move not to eat.*/
				list_eatable_piece = deleteList(list_eatable_piece);
				fprintf(stderr, ERR_MUST_CAPTURED);
			} else {
				list_eatable_piece = captureAllElementOnList(list_eatable_piece, attacking, attacked);
				check_move = true;
			}
		} else fprintf(stderr, ERR_MUST_CAPTURED);
	}
	return check_move;
}

/* It is used to return the list of pieces eaten by another piece, when we don't know the origin and destination*/
lista listPiecesCapturedByPiece(lista list, char c, int max_num_eatable_pieces) {
	
	int captured = 0, cont = 0, p_attacking = list->pos_p;
	cella orig = NULL, dest = NULL;
	lista lista_inc = NULL, lista_ped = NULL;

	for (lista_inc = list->next; lista_inc; lista_inc = lista_inc->next, list =
			list->next, cont++) {
		orig = &scac[list->pos_p];
		dest = &scac[lista_inc->pos_p];
		captured = 0;
	
		if (orig->a_dx && enemyPieces(orig->a_dx->pos, c) && found(orig->a_dx->a_dx, dest->pos))
			captured = orig->a_dx->pos;
		else if (orig->a_sx && enemyPieces(orig->a_sx->pos, c) && found(orig->a_sx->a_sx, dest->pos))
			captured = orig->a_sx->pos;
		else if (orig->b_dx && enemyPieces(orig->b_dx->pos, c) && found(orig->b_dx->b_dx, dest->pos))
			captured = orig->b_dx->pos;
		else if (orig->b_sx && enemyPieces(orig->b_sx->pos, c) && found(orig->b_sx->b_sx, dest->pos))
			captured = orig->b_sx->pos;
		if (captured)
			lista_ped = createList(lista_ped, captured);
		else
			break;
	}

	/*If the move is correct we add the last element (destination position) in the list ...*/
	if (captured && max_num_eatable_pieces == cont) {
		lista_ped = createList(createList(lista_ped, list->pos_p), p_attacking);
	}/*... if not delete it*/ 
	else 		
		lista_ped = deleteList(lista_ped);
	
	return lista_ped;
}

/*It is used to return the pieces captured from a king, when we don't know the origin and destination of the move*/
lista listPiecesCapturedByKing(lista l, char simb, int max_num_eatable_pieces) {
	
	int captured = 0, direction = 1, p_attacking = l->pos_p;
	lista l_p = NULL, l_inc = l->next;
	cella orig = &scac[l->pos_p], dest = &scac[l_inc->pos_p];
	int cont = 0;
	
	captured = checkRightAboveByKing(orig->a_dx, dest->pos, simb);
	
	/*If the piece captured is on the top left we set the direction to two, which for us has the meaning of left above*/
	if (!captured) {
		captured = checkLeftAboveByKing(orig->a_sx, dest->pos, simb);
		if (captured) direction = 2;
	}
	if (!captured) {
		captured = checkRightBelowByKing(orig->b_dx, dest->pos, simb);
		if (captured) direction = 3;
	}
	if (!captured) {
		captured = checkLeftBelowByKing(orig->b_sx, dest->pos, simb);
		if (captured) direction = 4;
	}
	if (captured) {
		l_p = createList(l_p, captured);
		for (cont++, l_inc = l_inc->next, l = l->next; (l_inc != NULL); l_inc =	l_inc->next, l = l->next, cont++) {
			orig = &scac[l->pos_p];
			dest = &scac[l_inc->pos_p];
			/*1 = ad, 2 = as, 3 = bd e 4 = bs.*/
			switch (direction) {
			case 1:
				/*The right direction to capture a piece is right above*/
				captured = checkRightAboveByKing(orig, dest->pos, simb);
				if (!captured) {
					/*Set the direction a 2, means left above in case later gose to right below, there is not other pieces
					in the first direction (right above)*/
					direction = 2;
					/*If we don't find it straigh in our direction, we check it below or above the cells right above*/
					tillFindEatablePieceRightAbove(captured, dest, orig, simb)
				}
				break;
			case 2:
				captured = checkLeftAboveByKing(orig, dest->pos, simb);
				if (!captured) {
					direction = 1;
					tillFindEatablePieceLeftAbove(captured, dest, orig, simb)
				}
				break;
			case 3:
				captured = checkRightBelowByKing(orig, dest->pos, simb);
				if (!captured) {
					direction = 1;
					tillFindEatablePieceRightBelow(captured, dest, orig,simb)
				}
				break;
			case 4:
				captured = checkLeftBelowByKing(orig, dest->pos, simb);
				if (!captured) {
					direction = 2;
					tillFindEatablePieceLeftBelow(captured, dest, orig, simb)
				}
				break;
			}
			/*Add the element to the list*/
			if (captured)
				l_p = createList(l_p, captured);			
			else/*Error, the move is wrong*/
				break;
		}
	}
	
	/*We add the last piece found, 'l->pos_p' is the destination piece  where end the attack*/
	if (captured && max_num_eatable_pieces == cont) {
		l_p = createList(createList(l_p, l->pos_p), p_attacking);
	} else
		l_p = deleteList(l_p);
	
	return l_p;
}


/*The king checks if the destination cell and the capturable piece are correctly right above*/
int checkRightAboveByKing(cella ad, int dest, char simb) {
	
	int captured;
	cella a_d = m_d_a_d(ad, simb);
	
	/* If we have captured the piece ... */
	if (a_d) {
		captured = a_d->pos;
		/*... now we check the destination cell.*/
		a_d = a_d->a_dx;
		findDestinationRightAbove(a_d, dest);
	}
	
	return (found(a_d, dest)) ? captured : 0;
}

/*The king checks if the destination cell and the capturable piece are correctly left above*/
int checkLeftAboveByKing(cella as, int dest, char simb) {
	int captured;
	cella a_s = m_d_a_s(as, simb);

	if (a_s) {
		captured = a_s->pos;
		a_s = a_s->a_sx;
		findDestinationLeftAbove(a_s, dest);
	}
	return (found(a_s, dest)) ? captured : 0;
}

/*The king checks if the destination cell and the capturable piece are correctly right below*/
int checkRightBelowByKing(cella bd, int dest, char simb) {
	int captured;
	cella b_d = m_d_b_d(bd, simb);

	if (b_d) {
		captured = b_d->pos;
		b_d = b_d->b_dx;
		findDestinationRightBelow(b_d, dest);
	}
	return (found(b_d, dest)) ? captured : 0;
}

/*The king checks if the destination cell and the capturable piece are correctly left below*/
int checkLeftBelowByKing(cella bs, int dest, char simb) {
	int captured;
	cella b_s = m_d_b_s(bs, simb);

	if (b_s) {
		captured = b_s->pos;
		b_s = b_s->b_sx;
		findDestinationLeftBelow(b_s, dest);
	}
	return (found(b_s, dest)) ? captured : 0;
}
