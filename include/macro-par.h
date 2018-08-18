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

#ifndef MACRO_PAR_H_
#define MACRO_PAR_H_

#include "dama.h"

#define playerLost(g) (g->num_d == 0 && g->num_p == 0)
#define dama(c) (c == DARK_KING || c == LIGHT_KING)
#define max(x, y) ((x>y)? x : y)
#define max4(a, b, c, d) max(max(a, b), max(c, d))
#define isEmptyCell(i) (scac[i].simb == EMPTY)
#define empty(cel) (cel == NULL || isEmptyCell(cel->pos))
#define myPieces(i, c) (scac[i].simb == c || scac[i].simb == (c-32))
#define enemyPieces(i, c) (!isEmptyCell(i) && !myPieces(i,c))

/*Ordinary pieces move one square diagonally forward to an unoccupied square and after that check if is not occupied by enemy*/
#define checkForwardMoveIsFree(cell, c) (empty(cell) || myPieces(cell->pos, c))

/*Delete lists*/
#define e_liste(a, b, c, d) a = deleteList(a); b = deleteList(b); c = deleteList(c); d = deleteList(d)

/*When the pieces became king, "1-2-3-4-5" for the light, "46-47-48-49-50" for the dark*/
#define base_dama_b(dest) ((dest == 1) || (dest == 2) || (dest == 3) || (dest == 4) || (dest == 5))
#define base_dama_n(dest) ((dest == 46) || (dest == 47) || (dest == 48) || (dest == 49) || (dest == 50))

/*Checks if the movement put on risk the pieces*/
#define found(cel, i) (cel && (cel->pos == i))

/*King is looking a way to eat.*/
#define checkEatableEnemyPiecesForKing(cel, dest, c) (dest && enemyPieces(cel->pos, c) && isEmptyCell(dest->pos))

/***************************************************************************************************************/
/*Check the consistency of the piece, rispectively left diagonal and right diagonal*/
#define ris(cel_x, cel_y, c) (cel_x && cel_y && enemyPieces(cel_x->pos, c) && isEmptyCell(cel_y->pos))
#define checkEnemyPiecesOnLeftDiagonal(cel, c) (ris(cel->b_dx, cel->a_sx, c) || ris(cel->a_sx, cel->b_dx, c))
#define checkEnemyPiecesOnRightDiagonal(cel, c) (ris(cel->a_dx, cel->b_sx, c) || ris(cel->b_sx, cel->a_dx, c))

/*Checks if there is any risk of been eaten by a king*/
#define checkEnemyKingOnDiagonal(cel_x, cel_y, c) (checkRiskUpperRightDiagonal(cel_x, c) || checkRiskUpperLeftDiagonal(cel_y, c))

/*Checks if there is any risk of been eaten by a pieces*/
#define checkEnemyPiecesOnDiagonal(cel, c) (checkEnemyPiecesOnRightDiagonal(cel, c) || checkEnemyPiecesOnLeftDiagonal(cel, c))

/*Checks if there is any risk of been eaten in the right diagonal by a pieces or a king*/
#define checkFreeMoveOnRighDiagonal(cel, c) (!checkRiskUpperRightDiagonal(cel, c) && !checkEnemyPiecesOnRightDiagonal(cel, c))

/*Checks if there is any risk of been eaten in the left diagonal by a pieces or a king*/
#define checkFreeMoveOnLeftDiagonal(cel, c) (!checkRiskUpperLeftDiagonal(cel, c) && !checkEnemyPiecesOnLeftDiagonal(cel, c))
/***************************************************************************************************************/

/***************************************************************************************************************/
/*The piece check if  a piece is in the side directions from the diagonal 
respectively right above, left above, right below, left below*/
#define m_p_a_d(cell, c) (cell && enemyPieces(cell->pos, c) && cell->a_dx && isEmptyCell(cell->a_dx->pos))
#define m_p_a_s(cell, c) (cell && enemyPieces(cell->pos, c) && cell->a_sx && isEmptyCell(cell->a_sx->pos))
#define m_p_b_d(cell, c) (cell && enemyPieces(cell->pos, c) && cell->b_dx && isEmptyCell(cell->b_dx->pos))
#define m_p_b_s(cell, c) (cell && enemyPieces(cell->pos, c) && cell->b_sx && isEmptyCell(cell->b_sx->pos))
/***************************************************************************************************************/

/***************************************************************************************************************/
/*The king try to avoid empty cells and find a pices to take*/
#define whileEmptyRightAbove(cel) while(cel && isEmptyCell(cel->pos)) cel = cel->a_dx
#define whileEmptyLeftAbove(cel) while(cel && isEmptyCell(cel->pos)) cel = cel->a_sx
#define whileEmptyRightBelow(cel) while(cel && isEmptyCell(cel->pos)) cel = cel->b_dx
#define whileEmptyLeftBelow(cel) while(cel && isEmptyCell(cel->pos)) cel = cel->b_sx
/***************************************************************************************************************/

/***************************************************************************************************************/
/*Try to find the destination cell.*/
#define findDestinationRightAbove(cel, dest) for(; cel && !found(cel, dest) && isEmptyCell(cel->pos); cel = cel->a_dx)
#define findDestinationLeftAbove(cel, dest) for(; cel && !found(cel, dest) && isEmptyCell(cel->pos); cel = cel->a_sx)
#define findDestinationRightBelow(cel, dest) for(; cel && !found(cel, dest) && isEmptyCell(cel->pos); cel = cel->b_dx)
#define findDestinationLeftBelow(cel, dest) for(; cel && !found(cel, dest) && isEmptyCell(cel->pos); cel = cel->b_sx)
/***************************************************************************************************************/

/***************************************************************************************************************/
/*The king try to capture a piece in the side directions from the diagonal 
respectively right above, left above, right below, left below*/
#define tillFindEatablePieceRightAbove(captured, dest, orig, simb)\
while(!captured && orig){captured = checkRightBelowByKing(orig->b_dx, dest->pos, simb);\
if(!captured) captured = checkLeftAboveByKing(orig->a_sx, dest->pos, simb); else direction = 3; orig = orig->a_dx;}

#define tillFindEatablePieceLeftAbove(captured, dest, orig, simb)\
while(!captured && orig){captured = checkLeftBelowByKing(orig->b_sx, dest->pos, simb);\
if(!captured) captured = checkRightAboveByKing(orig->a_dx, dest->pos, simb); else direction = 4; orig = orig->a_sx;}

#define tillFindEatablePieceRightBelow(captured, dest, orig, simb)\
while(!captured && orig){captured = checkLeftBelowByKing(orig->b_sx, dest->pos, simb);\
if(!captured) captured = checkRightAboveByKing(orig->a_dx, dest->pos, simb); else direction = 4; orig = orig->b_dx;}

#define tillFindEatablePieceLeftBelow(captured, dest, orig, simb)\
while(!captured && orig){captured = checkRightBelowByKing(orig->b_dx, dest->pos, simb);\
if(!captured) captured = checkLeftAboveByKing(orig->a_sx, dest->pos, simb); else direction = 3; orig = orig->b_sx;}
/***************************************************************************************************************/

#endif /* MACRO_PAR_H_ */
