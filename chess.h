/*****************************************************************************
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
 
#include <stdio.h>
#include <stdbool.h>
 
#define WHT ' '
#define BLK '*'

char  board[8][8];
char  killed[2][16];
int   whiteKingPos[2];
int   blackKingPos[2];
int   kw, kb;
int   turn;
int   redos;
int   moves;
 
//
int   R00Moved;
int   R07Moved;
int   r70Moved;
int   r77Moved;
int   whiteKingMoved;
int   blackKingMoved;
//
 
FILE* f;
 
int  whiteTime;
int  blackTime;
int  aiMovesCount;
char lastMove[6];
int  mode;
char t;
 
//
void
printBoard(void);//M
 
void
printSymbols(char a);
 
void
newBoard();
 
void
makeMoveHelper(char move[]);
 
void
makeMove(int move2[]);
 
void
tempUndo(int move2[], char i);
 
char
tempMove(int move2[]);
 
 
//
void
saveMoves(int move[], char i);
 
void
undo(void);
 
void
redo(void);
 
void
save(void);
 
bool
load(void);
 
 
/**
 Checks validity of the move
*/
 
bool
isValid(int move2[]);
 
bool
isValidPawn(int move[]);
 
bool
isValidKnight(int move[]);
 
bool
isValidKing(int move[]);
 
bool
isValidBishop(int move[]);
 
bool
isValidQueen(int move[]);
 
bool
isValidRook(int move[]);
 
bool
castling(int move[]);
 
void
uncastle(int i);
 
 
// CHECK.
bool
isCheck(void);
 
bool
pawnAttack(void);
 
bool
knightAttack(void);
 
bool
bishopAttack(void);
 
bool
rookAttack(void);
 
bool
kingAttack(void);
 
 
// CHECKMATE.
bool
isCheckMate(int n);
 
char*
GetTimedString(int* t);
 
int
pieceValue(char p);
 
char*
AIMove(void);
 
int
bestMoves(void);