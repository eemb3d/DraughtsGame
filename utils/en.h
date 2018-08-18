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

#define PLAYER_LIGHT "Light"
#define PLAYER_DARK "Dark"

#define ERR_MALLOC  "Malloc() returned null!\n"
#define ERR_ORIGIN_PIECE_IS_NOT_YOUR_COLOR "\nInvalid move - The origin piece is not of your color.\n\n"
#define ERR_ORIGIN_CELL_INVALID "\nInvalid move - Non-existent cell (must be between 1-50).\n\n"
#define ERR_DESTINATION_CELL_INVALID "\nInvalid move - It is not possible to reach the destination cell.\n\n"
#define ERR_DESTINATION_CELL_OCCUPIED "\nInvalid move - The destination cell is already occupied.\n\n"
#define ERR_SINTASSI_MOSSA  "\nInvalid move format, must be a string of two numbers from 1 to 50, separated by a dash, es. \"31-26\".\n \
To surrender type exit, after you have done a minimum number of moves, about 40.\n\n"

#define ERR_MUST_CAPTURED "\nEnemy pieces can and must be captured by jumping over the enemy piece.\n\n"
#define ERR_SURRENDER "\nBefore a proposal for a draw can be made, at least 40 moves must have been made by each player.\n\n"

#define ERR_MOVE "\nRecheck the sequence of the steps (xy-xy-xy ...), the first cell must be my piece\n \
the successive one must be an empty cells placed behind \n \
the eaten piece and all separated by a dash and included between 1 and 50.\n \
To surrender type exit, after you have done a minimum number of moves.\n\n"

#define ERR_MUST_CAPTURE_MAX_NUMBER "\nYou have made a syntactically or semantically incorrect move. \nRemember \
that it is necessary to eat as many pieces as possible.\n\n"

#define MSG_CHOSE_COLOR "\nChose the color: \"b\" for Light, \"n\" for Black.\n"

#define MSG_MAKE_MOVE  "Make your move, remember that the syntax of the simple move must be two numbers from 1 to 50 separated \
by a hyphen (es.\"31-26\"). \nIf the move is complex the form must be \"xy-xy-xy-xy ...\" where the xy \
has the same syntax as the simple move \n and must be placed behind the eaten piece, for more information \
check International draughts rules. \nTo surrender type exit, after you have done a minimum number of moves.\n"

#define MSG_SURRENDER "\nThe \"program\" has won due to the surrender of the opposing player.\n\n"
#define MSG_WINNER "The following player has won: "

#define MSG_BOARD_PLAYER_D "\\_____________________________DARK PLAYER__________________________________/"
#define MSG_BOARD_PIECES_D "	Number of Pieces in possession of the Black player: "
#define MSG_BOARD_KING_D "	Number of Kings in possession of the Black player: "

#define MSG_BOARD_PLAYER_L "/______________________________LIGHT PLAYER________________________________\\"
#define MSG_BOARD_PIECES_L "	Number of Pieces in possession of the Light player: "
#define MSG_BOARD_KING_L "	Number of Kings in possession of the Light player: "
#define MSG_COLOR "You have chosen the color: "
#define MSG_NO_VALID_MOVE_REMAINING "\nNo valid move remaining, program has lost."
#define MSG_EXIT "exit"


