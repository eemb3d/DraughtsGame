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

/*The program move*/
void programMakeMove(player attacking, player attacked) {

	lista list = NULL;

	/*Check if there is a piece that is likely to be eaten by an opponent*/
	boolean effective_move = moveToSafePosition(attacking, attacked);

	/* 1 Check if there is a piece that can be moved without been captured...*/
	for (list = attacking->lista_p; (!effective_move && list); list = list->next) {
		effective_move = movePiece(attacking, &scac[list->pos_p]);
		if (effective_move)
			break;
	}
	
	/* 2 Check if there is at least one king that can move forward without problem*/
	for (list = attacking->lista_d; (!effective_move && list); list = list->next) {
		effective_move = moveKing(attacking, &scac[list->pos_p]);
		if (effective_move)
			break;
	}
	
	/* 3 If not move anyway one*/
	if (!effective_move)
		effective_move = moveAnyway(attacking);
	
	/* 4 if we can not move, the program has!*/
	if (!effective_move)
		program_exit = true;

	list = NULL;
}

/* Move one piece from a risky position*/
boolean moveToSafePosition(player attacking, player attacked) {

	boolean effective_move = false;
	lista l = NULL, l_tmp = NULL, l_inc = NULL;
	cella cel = NULL;
	char c = attacking->color;

	/*List max pieces captured.*/
	l = listMaxNumberOfPiecesTaken(attacked);

	if (l == NULL)
		return effective_move;
	
	/*Move eventualy a king from a bad position.*/
	for (l_tmp = l, l_inc = l->next->next; (!effective_move && l_inc); l_tmp = l_tmp->next, l_inc = l_inc->next) {
		cel = &scac[l_tmp->pos_p];
		if (dama(cel->simb))
			effective_move = moveKing(attacking, cel);
	}
	
	/*Move eventualy a king from a bad position that is not in the list max pieces captured.*/
	for (l_tmp = attacking->lista_d; (!effective_move && l_tmp); l_tmp =	l_tmp->next) {
		cel = &scac[l_tmp->pos_p];
		if (dama(cel->simb)	&& (checkEnemyPiecesOnDiagonal(cel, c)	|| checkEnemyKingOnDiagonal(cel, cel, c)))
			effective_move = moveKing(attacking, cel);
	}
	
	/*Move eventualy a pieces from a bad position.*/
	for (l_tmp = l, l_inc = l->next->next; (!effective_move && l_inc); l_tmp = l_tmp->next, l_inc = l_inc->next) {
		if (!dama(scac[l_tmp->pos_p].simb))
			effective_move = movePiece(attacking, &scac[l_tmp->pos_p]);
	}
	
	l = deleteList(l);
	
	return effective_move;
}

/*Move a piece in a safe cell*/
boolean movePiece(player attacking, cella cel) {
	
	boolean effective_move = false;
	char c = attacking->color;
	int orig = cel->pos;
	cella dest;
	
	/*Light moves*/
	if (c == LIGHT) {
		dest = cel->a_dx;
		if (dest && isEmptyCell(dest->pos) && checkForwardMoveIsFree(dest->a_dx, c)
				&& !checkEnemyPiecesOnLeftDiagonal(dest, c)	&& !checkEnemyKingOnDiagonal(cel, dest, c)) {
			effective_move = true;
		} else {
			dest = cel->a_sx;
			if (dest && isEmptyCell(dest->pos) && checkForwardMoveIsFree(dest->a_sx, c)
					&& !checkEnemyPiecesOnRightDiagonal(dest, c)	&& !checkEnemyKingOnDiagonal(dest, cel, c))
				effective_move = true;
		}
	} else {/*Dark moves*/
		dest = cel->b_dx;
		if (dest && isEmptyCell(dest->pos) && checkForwardMoveIsFree(dest->b_dx, c)
				&& !checkEnemyPiecesOnRightDiagonal(dest, c)	&& !checkEnemyKingOnDiagonal(dest, cel, c)) {
			effective_move = true;
		} else {
			dest = cel->b_sx;
			if (dest && isEmptyCell(dest->pos) && checkForwardMoveIsFree(dest->b_sx, c)
					&& !checkEnemyPiecesOnLeftDiagonal(dest, c) && !checkEnemyKingOnDiagonal(cel, dest, c))
				effective_move = true;
		}
	}
	
	if (effective_move)
		updateAttackingPlayer(attacking, orig, dest->pos);
	
	return effective_move;
}

/*Move king in a safe cell*/
boolean moveKing(player attacking, cella orig) {
	
	boolean effective_move = false;
	char c = attacking->color;
	cella cel = NULL;

	/*If the king in the right diagonal is safe*/
	if (!checkRiskUpperRightDiagonal(orig, c)) {
	
		/*Check if moving in the direction of the upper right diagonal does not risk being eaten
		  from a piece or from a king in the left diagonal*/
		for (cel = orig->a_dx; (cel && isEmptyCell(cel->pos) && !checkFreeMoveOnLeftDiagonal(cel, c)); cel = cel->a_dx)
			;
	
		if (cel && isEmptyCell(cel->pos) && checkFreeMoveOnLeftDiagonal(cel, c) && checkForwardMoveIsFree(cel->a_dx, c))
			effective_move = true;
	
		/*Move in the direction of the lower right diagonal*/
		if (!effective_move) {
			for (cel = orig->b_sx; (cel && isEmptyCell(cel->pos) && !checkFreeMoveOnLeftDiagonal(cel, c)); cel = cel->b_sx)
				;
			if (cel && isEmptyCell(cel->pos) && checkFreeMoveOnLeftDiagonal(cel, c) && checkForwardMoveIsFree(cel->b_sx, c))
				effective_move = true;
		}
	}
	
	/*If the king can't move in the right diagonal check if it can in the direction of the upper left diagonal*/
	if (!effective_move && !checkRiskUpperLeftDiagonal(orig, c)) {
	
		/*Move in the direction of the upper left diagonal*/
		for (cel = orig->a_sx; (cel && isEmptyCell(cel->pos) && !checkFreeMoveOnRighDiagonal(cel, c)); cel = cel->a_sx)
			;
	
		if (cel && isEmptyCell(cel->pos) && checkFreeMoveOnRighDiagonal(cel, c) && checkForwardMoveIsFree(cel->a_sx, c))
			effective_move = true;
	
		/*Move in the direction of the lower left diagonal*/
		if (!effective_move) {
			for (cel = orig->b_dx; (cel && isEmptyCell(cel->pos) && !checkFreeMoveOnRighDiagonal(cel, c)); cel = cel->b_dx)
				;
			if (cel && isEmptyCell(cel->pos) && checkFreeMoveOnRighDiagonal(cel, c) && checkForwardMoveIsFree(cel->b_dx, c))
				effective_move = true;
		}
	}
	
	if (effective_move)
		updateAttackingPlayer(attacking, orig->pos, cel->pos);
	
	return effective_move;
}

/*Check if moving in the direction of the upper right diagonal does not risk being eaten
  from a piece or from a king in the left diagonal*/
boolean checkRiskUpperRightDiagonal(cella cell, char c) {
	cella c_tmp = NULL;
	boolean attention_king = false;

	/* I check if there is an attack by a king in the upper right diagonal after a move.*/
	if (!attention_king && cell->b_sx && isEmptyCell(cell->b_sx->pos)) {
		c_tmp = cell->a_dx;
		/*If going through the upper diagonal the cell is no longer empty ...*/
		whileEmptyRightAbove(c_tmp);
		/*.... then if it occurs we check if this is an opposing king.*/
		if (c_tmp && enemyPieces(c_tmp->pos, c) && dama(scac[c_tmp->pos].simb))
			attention_king = true;
	}
	
	/* Check if there is an attack by a king in the lower left diagonal after a move.*/
	if (!attention_king && cell->a_dx && isEmptyCell(cell->a_dx->pos)) {
		c_tmp = cell->b_sx;
		whileEmptyLeftBelow(c_tmp);
		if (c_tmp && enemyPieces(c_tmp->pos, c) && dama(scac[c_tmp->pos].simb))
			attention_king = true;
	}
	
	return attention_king;
}

/*Check if moving in the direction of the left diagonal does not risk being eaten
  from a piece or from a king in the left diagonal*/
boolean checkRiskUpperLeftDiagonal(cella cell, char c) {
	cella c_tmp = NULL;
	boolean attention_king = false;
	
	/* I check if there is an attack by a king in the upper left diagonal after a move.*/
	if (!attention_king && cell->b_dx && isEmptyCell(cell->b_dx->pos)) {
		c_tmp = cell->a_sx;
		whileEmptyLeftAbove(c_tmp);
		if (c_tmp && enemyPieces(c_tmp->pos, c) && dama(scac[c_tmp->pos].simb))
			attention_king = true;
	}
	
	/* Check if there is an attack by a king in the lower right diagonal after a move.*/
	if (!attention_king && cell->a_sx && isEmptyCell(cell->a_sx->pos)) {
		c_tmp = cell->b_dx;
		whileEmptyRightBelow(c_tmp);
		if (c_tmp && enemyPieces(c_tmp->pos, c) && dama(scac[c_tmp->pos].simb))
			attention_king = true;
	}
	
	return attention_king;
}

/*Moves without checking any risk.*/
boolean moveAnyway(player attacking) {
	
	lista list = attacking->lista_p;
	cella cel_dest = NULL;
	boolean effective_move = false;
	int origine;
	
	/*Light player move*/
	if (attacking->color == LIGHT) {
		for (; (!effective_move && list); origine = list->pos_p, list = list->next) {
			
			cel_dest = &scac[list->pos_p];
			
			if (cel_dest->a_dx && isEmptyCell(cel_dest->a_dx->pos)) {
				cel_dest = cel_dest->a_dx;
				effective_move = true;
			} else if (cel_dest->a_sx && isEmptyCell(cel_dest->a_sx->pos)) {
				cel_dest = cel_dest->a_sx;
				effective_move = true;
			}
		}
	}/*Dark player move*/ 
	else {
		for (; (!effective_move && list);	origine = list->pos_p, list = list->next) {
			
			cel_dest = &scac[list->pos_p];
			
			if (cel_dest->b_dx && isEmptyCell(cel_dest->b_dx->pos)) {
				cel_dest = cel_dest->b_dx;
				effective_move = true;
			} else if (cel_dest->b_sx && isEmptyCell(cel_dest->b_sx->pos)) {
				cel_dest = cel_dest->b_sx;
				effective_move = true;
			}
		}
	}
	
	/*Considero la dama se non posso muovere pedine, basta che muove è inutile in questo contesto andare più avanti.*/
	if (!effective_move) {
		for (list = attacking->lista_d; (!effective_move && list); origine =
				list->pos_p, list = list->next) {
			cel_dest = &scac[list->pos_p];
			if (cel_dest->a_dx && isEmptyCell(cel_dest->a_dx->pos)) {
				cel_dest = cel_dest->a_dx;
				effective_move = true;
			} else if (cel_dest->a_sx && isEmptyCell(cel_dest->a_sx->pos)) {
				cel_dest = cel_dest->a_sx;
				effective_move = true;
			} else if (cel_dest->b_dx && isEmptyCell(cel_dest->b_dx->pos)) {
				cel_dest = cel_dest->b_dx;
				effective_move = true;
			} else if (cel_dest->b_sx && isEmptyCell(cel_dest->b_sx->pos)) {
				cel_dest = cel_dest->b_sx;
				effective_move = true;
			}
		}
	}
	
	if (effective_move)
		updateAttackingPlayer(attacking, origine, cel_dest->pos);
	
	return effective_move;
}
