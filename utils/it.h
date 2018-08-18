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

#define ERR_ORIGIN_PIECE_IS_NOT_YOUR_COLOR "\nMossa non valida - La pedina di origine non e' del tuo colore.\n\n"
#define ERR_ORIGIN_CELL_INVALID "\nMossa non valida - Cella inesistente (deve essere compresa tra 1-50).\n\n"
#define ERR_DESTINATION_CELL_INVALID "\nMossa non valida - Non e possibile giungere nella cella di destinazione.\n\n"
#define ERR_DESTINATION_CELL_OCCUPIED "\nMossa non valida - Gia' presente una pedina nella cella destinazione.\n\n"
#define ERR_SINTASSI_MOSSA  "\nFormato mossa non valida, deve essere una stringa di due numeri compresi da 1 a 50, \
separati da un trattino, es. \"32-27\". Inoltre puoi uscire solo dopo aver fatto almeno 40 mosse digitando esci.\n\n"

#define ERR_SURRENDER "\nE' necessario fare almeno 40 mosse prima di abbandonare il gioco.\n\n"

#define ERR_MUST_CAPTURED "\nE' necessario mangiare la pedina avversaria.\n\n"

#define ERR_MOVE	"\nRicontrolla la sequenza dei passaggi (xy-xy-xy..), la prima cella deve essere una mia pedina i \
successivi devono essere celle vuote poste dietro \nla pedina mangiata e tutti separati da un trattino e compresi fra 1 e 50. \
Per uscire digitare esci, \novviamente se abbaimo fatto un numero minimo di mosse.\n\n"
#define ERR_MALLOC  "La malloc() ha restituito null!\n"
#define ERR_MUST_CAPTURE_MAX_NUMBER "\nAvete fatto una mossa sintatticamente o semanticamente non corretta. Ricordati \nche e' necessario \
mangiare il maggior numero possibile di pedine.\n\n"

#define MSG_CHOSE_COLOR "\nScegli il tuo colore: \"b\" per il bianco, \"n\" per il nero.\n"
#define MSG_MAKE_MOVE  "Fai la tua mossa, ricordati che la sintassi della mossa semplice deve essere di due numeri compresi\
da 1 a 50 separati da un trattino(es.\"32-27\"). \nMentre se la mossa è complessa la forma deve essere \"xy-xy-xy-xy\" dove le xy \
hanno la stessa sintassi della mossa semplice \ne devono essere poste dietro la pedina mangiata, per ulteriori informazioni \
guardare le regole della dama internaz. Per uscire dal gioco, \ndopo aver fatto un numero minimo di mosse, digitare esci.\n"
#define MSG_SURRENDER "\nHa vinto il \"programma\" per abbandono del giocatore avversario.\n\n"
#define MSG_NO_VALID_MOVE_REMAINING "\nIl programma ha perso, nessuna mossa valida possibile."


#define MSG_BOARD_PLAYER_D "\\___________________________GIOCATORE NERO_________________________________/"
#define MSG_BOARD_PIECES_D "	Numero Pedine Nere in possesso del giocatore: "
#define MSG_BOARD_KING_D "	Numero Dame Nere in possesso del giocatore: "

#define MSG_BOARD_PLAYER_L "/____________________________GIOCATORE BIANCO______________________________\\"
#define MSG_BOARD_PIECES_L "	Numero Pedine Bianche in possesso del giocatore: "
#define MSG_BOARD_KING_L "	Numero Dame Bianche in possesso del giocatore: "
#define MSG_WINNER "Ha vinto la partita il giocatore "
#define MSG_COLOR "Hai scelto il colore: "
#define MSG_EXIT "exit"

#define PLAYER_LIGHT "Bianco"
#define PLAYER_DARK "Nero"
