//  time complexity: O(n!)
//  solution to n queen problem using backtracking algorithm


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


const char QUEEN_CHAR = 'Q';
const char EMPTY_CHAR = '.';
const int QUEEN_NUM = 1;
const int EMPTY_NUM = 0;


int assignPos(char *pos, int n, int board[n][n]);
void getAnalysis(int n);
int NQmain(int n, int board[n][n]);
bool solveNQueen(int row, int n, int board[n][n]);
bool isValid(int row, int col, int n, int board[n][n]);
void printOut(int n, int board[n][n]);


double timeSum;
int timeLen;


int main(void)
{
    while (true) {
        int n;
        timeSum = timeLen = 0.0;
        char *pos = malloc(5);  
        if (pos == NULL) return 1;
        printf("\nEnter N: ");  
        scanf("%d", &n);
        int board[n][n];
        memset(board, EMPTY_NUM, sizeof(board));
        printOut(n, board);
        while (true) {
            printf("([x] reassign N value | [w] edit queen positions | [a] analysis)\nEnter starting position of the Queen: ");  
            scanf("%s", pos);
            if (strcmp(pos, "x") == 0) break;
            if (strcmp(pos, "a") == 0) getAnalysis(n);
            if (strcmp(pos, "w") == 0) {
                memset(board, EMPTY_NUM, sizeof(board));
                printOut(n, board);
                while (strcmp(pos, "x") != 0) {
                    printf("(press [x] to finish | press [z] to clear board)\nEnter position of the Queen: ");  
                    scanf("%s", pos);
                    if (strcmp(pos, "z") == 0) memset(board, EMPTY_NUM, sizeof(board));
                    printf("\n\n");
                    assignPos(pos, n, board);
                    printOut(n, board);
                }
            }
            else {
                memset(board, EMPTY_NUM, sizeof(board));
                assignPos(pos, n, board);
            }
            NQmain(n, board);
        }
    }
}


void getAnalysis(int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int board[n][n];
            memset(board, EMPTY_NUM, sizeof(board));
            board[i][j] = QUEEN_NUM;
            NQmain(n, board);
            printf("Valid solutions found: %i", timeLen);
        }
    }
}


int assignPos(char *pos, int n, int board[n][n])
{
    int col = pos[0] - 97; 
    pos++;
    int pos_num = atoi(pos);
    if (pos_num == 0) return 1;
    int row = n - pos_num;
    if (isValid(row, col, n, board)) {
        board[row][col] = QUEEN_NUM;
        return 0;
    }
    return 1;
}


int NQmain(int n, int board[n][n]) 
{
    clock_t t = clock();
    if (solveNQueen(0, n, board)) {
        t = clock() - t;
        double run_time = (double) t/CLOCKS_PER_SEC;
        timeSum += run_time;
        timeLen += 1;
        printf("\n\n\nFinished in %.3fs\n", run_time);
        printf("Average runtime is %.6fs\n", timeSum/timeLen);
        printOut(n, board);
        return 0;
    }
    printf("\nNo solutions found.\n");
    return 0;
}


bool isValid(int row, int col, int n, int board[n][n])
{
    for (int i = 0; i < n; i++) if (board[i][col] == QUEEN_NUM) return false;
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            if (i + j == row + col || i - j == row - col) {
                if (board[i][j] == QUEEN_NUM) return false;
            }
        }
    }
    return true;
}


bool solveNQueen(int row, int n, int board[n][n])
{
    if (row == n) return true;
    for (int i = 0; i < n; i++) if (board[row][i] == QUEEN_NUM) return solveNQueen(row+1, n, board);
    for (int i = 0; i < n; i++) {
        if (isValid(row, i, n, board)) {
            board[row][i] = QUEEN_NUM;
            if (solveNQueen(row+1, n, board)) return true;
        }
        board[row][i] = EMPTY_NUM;
    }
    return false;
}


void returnf(int n, int board[n][n])
{   
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {   
            if (board[j][i] == QUEEN_NUM) {
                printf("%c%i", 'a' + i%26, n - j);
                count++;
                if (count != n) printf(", ");
            }
        }
        if (count % (n/2) == 0 && count > 0) printf("\n");
    }
    printf("\n\n");
}


void printOut(int n, int board[n][n])
{
    for (int i = 0; i < n; i++) printf("%c ", 'a' + i%26);
    printf("\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == QUEEN_NUM) printf("%c ", QUEEN_CHAR);
            else printf("%c ", EMPTY_CHAR);
        }
        printf("|%i\n", n - i);
    }
    returnf(n, board);
}
