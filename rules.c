/****************************************************************************
 * Chess Library
 *
 * Alexandria University, Faculty of Engineering
 * First year, Fall 2015
 * Computer and Systems Engineering Department
 *
 * Programming I Final Project
 *
 * Marwan Tammam <darknight-x@hotmail.com>
 * Ahmed Yakout <iyakout@hotmail.com>
 *
 ***************************************************************************/
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "chess.h"

bool
isValid(int move2[]){

    if (move2[1] == 8 || move2[1] == 9)
    {
        return castling(move2);
    }
    if (islower(board[move2[0]][move2[1]]) && islower(board[move2[2]][move2[3]]))
        return false;

    if (isupper(board[move2[0]][move2[1]]) && isupper(board[move2[2]][move2[3]]))
        return false;

    if ((islower(board[move2[0]][move2[1]]) && turn != 1) || (isupper(board[move2[0]][move2[1]]) && turn != -1))
        return false;

        switch (board[move2[0]][move2[1]]){
            case 'P': case 'p':
                if (isValidPawn(move2))
                {
                    if (move2[4] != 0 || move2[2] == 0 || move2[2] == 7)
                    {
                        if (move2[4] != 0 && (move2[2] == 0 || move2[2] == 7))
                        {
                            board[move2[0]][move2[1]] = turn == 1 ? move2[4] : toupper(move2[4]);
                            return true;
                        }
                    }
                    return true;
                }
                else
                    return false;
            case 'K': case 'k':
                return isValidKing(move2);
            case 'N': case 'n':
                return (isValidKnight(move2));
            case 'B': case 'b':
                return (isValidBishop(move2));
            case 'R': case 'r':
                return (isValidRook(move2));
            case 'Q': case 'q':
                return (isValidQueen(move2));
            default:
                return false;
        }
}

bool
isValidRook(int move[])
{
    int i;
        if ( move[1] == move[3]){
        //***************** vertical move ****************
                    if( move[0] > move[2]){
                            // *********** forward **************
                            for ( i = move[0]-1 ; i > move[2] ; i-- ){
                                        if ( board[i][move[1]] != WHT && board[i][move[1]] != BLK ) {
                                           // if true that means there is a piece in the way.
                                            return false;
                                        }

                            }
                            return true;
                      }
                    else if ( move[0] < move[2] ){
                            // *********** backward ****************

                            for ( i = move[0]+1 ; i < move[2] ; i++ ){
                                        if ( board[i][move[1]] != WHT && board[i][move[1]] != BLK) {
                                            // if true that means there is a piece in the way.
                                            return false;
                                        }
                            }
                            return true;
                      }
                    else return false;
                    // *********** invalid move ****************
                  }
        else if ( move[0] == move[2]){
        //***************** Horizontal move ****************

                    if( move[1] > move[3]){
                           // ************** left  ***************

                             for ( i = move[1]-1 ; i > move[3] ; i-- ){
                                        if ( board[move[0]][i] != WHT && board[move[0]][i] != BLK){
                                            // if true that means there is a piece in the way.
                                            return false;
                                        }

                            }
                            return true;
                      }

                    else if ( move[1] < move[3] ){
                            // ************** right ***************

                            for ( i = move[1]+1 ; i < move[3] ; i++ ){

                                        if ( board[move[0]][i] != WHT && board[move[0]][i] != BLK){
                                            // if true that means there is a piece in the way.
                                            return false;
                                        }

                            }
                            return true;
                      }
                    else return false;

                  }
        else return false;
        // ******************** invalid move ********************
    }

bool
isValidBishop(int move[]){
    int i;
    if ( abs(move[0]-move[2]) == abs(move[1]-move[3]) ){
    //***************** Valid Diagonal move ************
                if( move[0] < move[2] && move[1] < move[3]){
                // *********** backward - right **************
                        for ( i = 1 ; i < move[2]-move[0] ; i++ ){
                                    if ( board[move[0]+i][move[1]+i] != WHT && board[move[0]+i][move[1]+i] != BLK ) {
                                        // if true that means there is a piece in the way.
                                        return false;
                                    }

                        }
                        return true;
                  }
                else if( move[0] < move[2] && move[1] > move[3]){
                // *********** backward - left ************
                        for ( i = 1 ; i < move[2]-move[0] ; i++ ){
                                    if ( board[move[0]+i][move[1]-i] != WHT && board[move[0]+i][move[1]-i] != BLK ) {
                                        // if true that means there is a piece in the way.
                                        return false;
                                    }
                        }
                        return true;
                  }
                else if( move[0] > move[2] && move[1] < move[3]){
                // *********** forward - right **************
                        for ( i = 1 ; i < move[0]-move[2] ; i++ ){
                                    if ( board[move[0]-i][move[1]+i] != WHT && board[move[0]-i][move[1]+i] != BLK ) {
                                        // if true that means there is a piece in the way.
                                        return false;
                                    }
                            }
                        return true;
                }
                else if( move[0] > move[2] && move[1] > move[3]){
                // *********** Forward - left **************
                        for ( i = 1 ; i < move[0]-move[2] ; i++ ){
                                    if ( board[move[0]-i][move[1]-i] != WHT && board[move[0]-i][move[1]-i] != BLK ) {
                                        // if true that means there is a piece in the way.
                                        return false;
                                    }
                            }
                        return true;
                }

                else return false;
                // *********** invalid move ****************
              }
    else return false;
    // ******************** invalid diagonal move ********************
    }

bool
isValidQueen(int move[]){
    if ( isValidBishop(move) || isValidRook(move) ) return true;
    else return false;
}

bool
isValidKnight(int move[]){

    if     ( move[2] == move[0]-2 && move[3] == move[1]+1 ) return true;
    else if( move[2] == move[0]+2 && move[3] == move[1]+1 ) return true;
    else if( move[2] == move[0]-2 && move[3] == move[1]-1 ) return true;
    else if( move[2] == move[0]+2 && move[3] == move[1]-1 ) return true;

    else if( move[2] == move[0]-1 && move[3] == move[1]+2 ) return true;
    else if( move[2] == move[0]+1 && move[3] == move[1]+2 ) return true;
    else if( move[2] == move[0]-1 && move[3] == move[1]-2 ) return true;
    else if( move[2] == move[0]+1 && move[3] == move[1]-2 ) return true;

    else return false;

}

bool
isValidKing(int move[]){
    if      ( abs(move[2] - move[0]) == 1 && abs(move[3] - move[1]) == 1 ) return true; // diagonal move
    else if ( abs(move[2] - move[0]) == 1 &&     move[3] - move[1]  == 0 ) return true; // vertical move
    else if (     move[2] - move[0]  == 0 && abs(move[3] - move[1]) == 1 ) return true; // horizontal move

    else return false;

}

bool
isValidPawn(int move[]){
    if ( turn == 1 ){
        // player1 turn
        if ( move[0]-move[2] == 1 && abs(move[1]-move[3]) == 1 ){
         // Valid Diagonal move (forward) ( must check for a piece to be taken out
                if (board[move[2]][move[3]] != WHT &&  board[move[2]][move[3]] != BLK) return true;
                // a piece will be taken out, therefore move is valid.

                else return false;
                // there is no piece to be taken out, therefore move is invalid!
        }

        else if ( move[1] == move [3] && move[0] > move[2]){
           // vertical (forward) move is valid (can't take out a piece)
            if (move[0] == 6){
           // can move 2 steps or 1 step
                if ( move[0]-move[2] == 2){
                        // two step
                        if ((board[move[2]+1][move[3]] != WHT &&  board[move[2]+1][move[3]] != BLK) || (board[move[2]][move[3]] != WHT &&  board[move[2]][move[3]] != BLK)) return false;
                        else return true;
                    }
                else if (move[0]-move[2] == 1){
                        // one step
                        if (board[move[2]][move[3]] != WHT &&  board[move[2]][move[3]] != BLK) return false;
                        else return true;
                    }
                else return false;

                }
            else{
           // can move 1 step (forward) only
                    if ( move[0] - move[2] == 1 ){
                        if ( board[move[2]][move[3]] != WHT &&  board[move[2]][move[3]] != BLK ) return false;
                        else return true;
                    }
                    else return false;
                 }
            }
        else return false;
    }
    else if ( turn == -1){
    // player2 turn
        if ( move[2]-move[0] == 1 && abs(move[1]-move[3]) == 1 ){
         // Valid Diagonal move (backward) ( must check for a piece to be taken out
                if (board[move[2]][move[3]] != WHT &&  board[move[2]][move[3]] != BLK) return true;
                // a piece will be taken out, therefore move is valid.

                else return false;
                // there is no piece to be taken out, therefore move is invalid!

        }
        else if ( move[1] == move [3] && move[0] < move[2]){
        // vertical (Backward) move is valid (can't take out a piece)
            if (move[0] == 1){
            // can move 2 steps or 1 step
                    if ( move[2]-move[0] == 2){
                        // two step
                        if ((board[move[2]-1][move[3]] != WHT &&  board[move[2]-1][move[3]] != BLK) || (board[move[2]][move[3]] != WHT &&  board[move[2]][move[3]] != BLK)) return false;
                        else return true;
                    }
                    else if (move[2]-move[0] == 1){
                        // one step
                        if (board[move[2]][move[3]] != WHT &&  board[move[2]][move[3]] != BLK) return false;
                        return true;
                    }
                    else return false;
            }
            else{
            // can move 1 step (backward) only
                if ( move[2]-move[0] == 1 ){
                    if (board[move[2]][move[3]] != WHT &&  board[move[2]][move[3]] != BLK) return false;
                    else return true;
                }
                else return false;
                }
             }
        else return false;
    }

    else return false;
// invalid move or Promotion!
}


/* *********************************************************************************************
 * ******************************** "Check" Functions ******************************************
 * *********************************************************************************************
 */

bool
isCheck(void) {
    if (knightAttack() || bishopAttack() || pawnAttack() || rookAttack() || kingAttack()) {
        return true;
    } else return false;
}

bool
rookAttack(void) {
    int i;
    char attacker1 = turn == -1 ? 'r' : 'R';
    char attacker2 = turn == -1 ? 'q' : 'Q';
    int kingPos[2];
    kingPos[0] = turn == -1 ? blackKingPos[0] : whiteKingPos[0];
    kingPos[1] = turn == -1 ? blackKingPos[1] : whiteKingPos[1];
    // vertical
    // forward
    for (i = kingPos[0] - 1; i >= 0; i--) {
        if (board[i][kingPos[1]] == attacker1) return true;
        else if (board[i][kingPos[1]] == attacker2) return true;
        else if (board[i][kingPos[1]] == WHT || board[i][kingPos[1]] == BLK) continue;
        else break;
    }
    // backward
    for (i = (kingPos[0] + 1); i <= 7; i++) {
        if (board[i][kingPos[1]] == attacker1) return true;
        else if (board[i][kingPos[1]] == attacker2) return true;
        else if (board[i][kingPos[1]] == WHT || board[i][kingPos[1]] == BLK) continue;
        else break;
    }

    // horizontal
    // left
    for (i = kingPos[1] - 1; i >= 0; i--) {
        if (board[kingPos[0]][i] == attacker1) return true;
        else if (board[kingPos[0]][i] == attacker2) return true;
        else if (board[kingPos[0]][i] == WHT || board[kingPos[0]][i] == BLK) continue;
        else break;
    }
    // right
    for (i = kingPos[1] + 1; i <= 7; i++) {
        if (board[kingPos[0]][i] == attacker1) return true;
        else if (board[kingPos[0]][i] == attacker2) return true;
        else if (board[kingPos[0]][i] == WHT || board[kingPos[0]][i] == BLK) continue;
        else break;
    }
    return false; // no threats
}

bool
bishopAttack(void) {
    int i;
    char attacker1 = turn == -1 ? 'b' : 'B';
    char attacker2 = turn == -1 ? 'q' : 'Q';
    int kingPos[2];
    kingPos[0] = turn == -1 ? blackKingPos[0] : whiteKingPos[0];
    kingPos[1] = turn == -1 ? blackKingPos[1] : whiteKingPos[1];
    // diagonal moves
    // diagonal (forward - right) // pawn may check!
    for (i = 1; i <= 7; i++) {
        if (kingPos[0] - i < 0 || kingPos[1] + i > 7) break; // board's edge reached
        if (board[kingPos[0] - i][kingPos[1] + i] == attacker1) return true;
        else if (board[kingPos[0] - i][kingPos[1] + i] == attacker2) return true;
        else if (board[kingPos[0] - i][kingPos[1] + i] == WHT || board[kingPos[0] - i][kingPos[1] + i] == BLK) continue;
        else break;
    }
    // diagonal (backward - left)
    for (i = 1; i <= 7; i++) {
        if (kingPos[0] + i > 7 || kingPos[1] - i < 0) break; // board's edge reached
        if (board[kingPos[0] + i][kingPos[1] - i] == attacker1) return true;
        else if (board[kingPos[0] + i][kingPos[1] - i] == attacker2) return true;
        else if (board[kingPos[0] + i][kingPos[1] - i] == WHT || board[kingPos[0] + i][kingPos[1] - i] == BLK) continue;
        else break;
    }
    // diagonal (forward - left) // pawn may check!
    for (i = 1; i <= 7; i++) {
        if (kingPos[0] - i < 0 || kingPos[1] - i < 0) break; // board's edge reached
        if (board[kingPos[0] - i][kingPos[1] - i] == attacker1) return true;
        else if (board[kingPos[0] - i][kingPos[1] - i] == attacker2) return true;
        else if (board[kingPos[0] - i][kingPos[1] - i] == WHT || board[kingPos[0] - i][kingPos[1] - i] == BLK) continue;
        else break;
    }
    // diagonal (backward - right)
    for (i = 1; i <= 7; i++) {
        if (kingPos[0] + i > 7 || kingPos[1] + i > 7) break; // board's edge reached
        if (board[kingPos[0] + i][kingPos[1] + i] == attacker1) return true;
        else if (board[kingPos[0] + i][kingPos[1] + i] == attacker2) return true;
        else if (board[kingPos[0] + i][kingPos[1] + i] == WHT || board[kingPos[0] + i][kingPos[1] + i] == BLK) continue;
        else break;
    }
    return false; // no threats
}

bool
pawnAttack(void) {
    char attacker = turn == -1 ? 'p' : 'P';
    int kingPos[2];
    kingPos[0] = turn == -1 ? blackKingPos[0] : whiteKingPos[0];
    kingPos[1] = turn == -1 ? blackKingPos[1] : whiteKingPos[1];
    if (islower(attacker))
    {
         if (board[kingPos[0] + 1][kingPos[1] - 1] == attacker || board[kingPos[0] + 1][kingPos[1] + 1] == attacker) return true; // check
         else return false; // no threats
    }
    else
    {
         if (board[kingPos[0] - 1][kingPos[1] - 1] == attacker || board[kingPos[0] - 1][kingPos[1] + 1] == attacker) return true; // check
         else return false; // no threats
    }
}

bool
knightAttack(void) {
    char attacker = turn == -1 ? 'n' : 'N';
    int kingPos[2];
    kingPos[0] = turn == -1 ? blackKingPos[0] : whiteKingPos[0];
    kingPos[1] = turn == -1 ? blackKingPos[1] : whiteKingPos[1];

    if (board[kingPos[0] - 2][kingPos[1] + 1] == attacker) return true; //check
    else if (board[kingPos[0] + 2][kingPos[1] + 1] == attacker) return true;
    else if (board[kingPos[0] - 2][kingPos[1] - 1] == attacker) return true;
    else if (board[kingPos[0] + 2][kingPos[1] - 1] == attacker) return true;

    else if (board[kingPos[0] - 1][kingPos[1] + 2] == attacker) return true; //check
    else if (board[kingPos[0] + 1][kingPos[1] + 2] == attacker) return true;
    else if (board[kingPos[0] - 1][kingPos[1] - 2] == attacker) return true;
    else if (board[kingPos[0] + 1][kingPos[1] - 2] == attacker) return true;

    else return false; // no threats

}

bool
kingAttack(void) {
    char attacker = turn == -1 ? 'k' : 'K';
    int kingPos[2];
    kingPos[0] = turn == -1 ? blackKingPos[0] : whiteKingPos[0];
    kingPos[1] = turn == -1 ? blackKingPos[1] : whiteKingPos[1];

    // diagonal moves
    if (board[kingPos[0] - 1][kingPos[1] - 1] == attacker || board[kingPos[0] - 1][kingPos[1] + 1] == attacker) return true; // check
    if (board[kingPos[0] + 1][kingPos[1] - 1] == attacker || board[kingPos[0] + 1][kingPos[1] + 1] == attacker) return true; // check
    // vertical
    if (board[kingPos[0]][kingPos[1] - 1] == attacker || board[kingPos[0]][kingPos[1] + 1] == attacker) return true; // check
    if (board[kingPos[0] - 1][kingPos[1]] == attacker || board[kingPos[0] + 1][kingPos[1]] == attacker) return true; // check

    else return false;
}


/*******************************************************************************
*/

bool
isCheckMate(int n){
    //n => turn
    int i, j, k, l;
    int possibleMoves[5];
    for ( i = 0 ; i < 8 ; i++ ){
        for ( j = 0 ; j < 8 ; j++ ){
            if ( n == 1 ? islower(board[i][j]) : isupper(board[i][j]) ){
                for ( k = 0 ; k < 8 ; k++ ){
                    for ( l = 0 ; l < 8 ; l++){
                        possibleMoves[0] = i;
                        possibleMoves[1] = j;
                        possibleMoves[2] = k;
                        possibleMoves[3] = l;
                        possibleMoves[4] = (tolower(board[i][j]) == 'p' && (k == 0 || k == 7)) ? 'q' : 0;
                        if (isValid(possibleMoves)) {

                            char killed = tempMove(possibleMoves);

                            int x = 0;
                            if (isCheck())
                            {
                                x = 1;
                            }


                            tempUndo(possibleMoves, killed);

                            if (x == 0)
                                return false;

                        }

                    }
                }
            }

        }

    }
    return true;
}


bool
castling(int move[]){
    // (0-0) kingSide , (0-0-0) queenSide
    int i;
    int move2[5] = {0};
    move2[0] = turn == 1 ? whiteKingPos[0] : blackKingPos[0];
    move2[1] = turn == 1 ? whiteKingPos[1] : blackKingPos[1];
    move2[2] = turn == 1 ? whiteKingPos[0] : blackKingPos[0];
    if (isCheck()) return false;
    if(move[1] == 8)
    {
        if((turn == 1 ? r77Moved : R07Moved) == 1 || (turn == 1 ? whiteKingMoved : blackKingMoved) == 1) return false;
        for ( i = 1 ; i <= 2 ; i++) {
            move2[3] = move2[1] + i;
            if (board[turn == 1 ? 7 : 0][4+i] != WHT && board[turn == 1 ? 7 : 0][4+i] != BLK) return false;
            tempMove(move2);
            if(isCheck()) {
                tempUndo(move2, WHT);
                return false;
            }
            else tempUndo(move2, WHT);
        }
    }
    else if (move[1] == 9)
    {
        if((turn == 1 ? r70Moved : R00Moved) == 1 || (turn == 1 ? whiteKingMoved : blackKingMoved) == 1) return false;
        for ( i = 1 ; i <= 3 ; i++) {
            move2[3] = move2[1] - i;
            if (board[turn == 1 ? 7 : 0][4-i] != WHT && board[turn == 1 ? 7 : 0][4-i] != BLK) return false;
            tempMove(move2);
            if(isCheck()) {
                tempUndo(move2, WHT);
                return false;
            }
            else tempUndo(move2, WHT);
        }
    }
    return true;
}
