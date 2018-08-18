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

#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_

#include "dama.h"

/*Function prototypes*/
void makeMove(player, player);
lista listMaxNumberOfPiecesTaken(player); 
lista captureAllElementOnList(lista, player, player); 

/*Player movement prototypes.*/
void chooseMove(player, player, int);
boolean checkHaveChosenToCaptureTheMax(player, player, char*, int);
boolean checkMoveValidity(player, player, char*, int);
boolean checkSemanticMove(player, player, int, int, int); 
lista listPiecesCapturedByPiece(lista,char, int);
lista listPiecesCapturedByKing(lista, char, int);
int checkRightAboveByKing(cella, int, char);
int checkLeftAboveByKing(cella, int, char);
int checkRightBelowByKing(cella, int, char);
int checkLeftBelowByKing(cella, int, char);

/*Program movement prototypes.*/
void programMakeMove(player, player);
boolean moveToSafePosition(player, player); 
boolean moveAnyway(player);
boolean moveKing(player, cella);
boolean movePiece(player, cella);
boolean checkRiskUpperRightDiagonal(cella, char);
boolean checkRiskUpperLeftDiagonal(cella, char);

/*Search prototypes*/
cella m_d_a_d(cella, char); /*Check if the king can eat righ above*/
cella m_d_a_s(cella, char); /*Check if the king can eat left above*/
cella m_d_b_d(cella, char); /*Check if the king can eat righ below*/
cella m_d_b_s(cella, char); /*Check if the king can eat left below*/
lista l_max_d(cella, lista, char); /*List with max number of pieces eatable from a king.*/
lista l_max_p(cella, cella, cella, cella, cella, lista, char); /*List with max number of pieces eatable from a normal piece.*/

/*List*/
lista createList(lista, int);
lista deleteElement(lista, int);
lista deleteList(lista);
boolean checkDuplicates(lista, int);
int numElementsPerList(lista);
lista modifyListOfPieces(lista, int, int);
void modifyListOfKings(lista, int, int);
lista createNewElementOnList(int);
lista cloneList(lista);

/*MISC*/
void initBoard();
char chooseColor();
player initPlayer(char);
lista initPlayerList(char);
void printGameBoard(player, player);
void updateAttackingPlayer(player, int, int);
void updateAttackedPlayer(player, int);
void deletePlayer(player);

/*Test prototypes*/
void initTest(player, player);
lista initTestList(int *, int);

#endif /* PROTOTYPE_H_ */
