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
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
 
#include "chess.h"
 
char*
AIMove(void)
{
    FILE* ai = fopen("ai", "r");
 
    bestMoves();
 
    srand(time(NULL));
    int r = rand() % (aiMovesCount);
 
    fseek(ai, r * 7 * sizeof(char), SEEK_SET);
 
    int temp[5];
    fscanf(ai, "%1d%1d%1d%1d%d", &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]);
 
    char* s = malloc(sizeof(char) * 7);
    s[0] = temp[1] + 'A';
    s[1] = '8' - temp[0];
    s[2] = temp[3] + 'A';
    s[3] = '8' - temp[2];
    s[4] = temp[4];
    s[5] = 0;
 
    return s;
}
 
int
bestMoves(void){
 
    FILE* moves;
    if (turn == -1)
    {
        moves = fopen("ai", "w");
        aiMovesCount = 0;
    }
    int max_value = INT_MIN;
 
    int i, j, k, l;
    int possibleMoves[5];
    for ( i = 0 ; i < 8 ; i++ )
    {
        for ( j = 0 ; j < 8 ; j++ )
        {
            if (turn == -1 ? isupper(board[i][j]) : islower(board[i][j]))
            {
                for ( k = 0 ; k < 8 ; k++ )
                {
                    for ( l = 0 ; l < 8 ; l++)
                    {
                        possibleMoves[0] = i;
                        possibleMoves[1] = j;
                        possibleMoves[2] = k;
                        possibleMoves[3] = l;
                        possibleMoves[4] = (tolower(board[i][j]) == 'p' && (k == 0 || k == 7)) ? 'q' : 0;
                        if (isValid(possibleMoves))
                        {
                            char killed = tempMove(possibleMoves);
                            int val = pieceValue(killed);
 
                            if (turn == -1)
                            {
                                turn *= -1;
                                if (isCheck())
                                {
                                    val += 1;
                                }
 
                                val -= bestMoves();
                                turn *= -1;
 
                                if (val >= max_value)
                                {
                                    if (val > max_value)
                                    {
                                        aiMovesCount = 1;
                                        fclose(moves);
                                        moves = fopen("ai", "w");
                                        max_value = val;
 
                                    }
                                    else
                                        aiMovesCount++;
 
                                    fprintf(moves, "%d%d%d%d%d\n", possibleMoves[0], possibleMoves[1], possibleMoves[2], possibleMoves[3], possibleMoves[4]);
                                }
 
                            }
                            else
                            {
                                if (val > max_value)
                                {
                                    max_value = val;
                                }
                                turn *= -1;
                                if (isCheckMate(turn))
                                {
                                    turn *= -1;
                                    tempUndo(possibleMoves, killed);
                                    return INT_MAX;
                                }
                                turn *= -1;
 
                            }
                            tempUndo(possibleMoves, killed);
                        }
 
                    }
                }
            }
 
        }
 
    }
    if (turn == -1)
        fclose(moves);
    return max_value;
}
 
int
pieceValue(char p)
{
    switch (tolower(p))
    {
        case 'p':
            return 1;
        case 'n':
            return 3;
        case 'b':
            return 3;
        case'r':
            return 5;
        case 'q':
            return 9;
        case 'k':
            return INT_MAX;
        default:
            break;
    }
    return 0;
}