//  time complexity: O(n!)
//  solution to n queen problem using backtracking algorithm

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


const char QUEEN_CHAR = 'Q';
const char EMPTY_CHAR = '.';
const int QUEEN_NUM = 1;
const int EMPTY_NUM = 0;


int NQmain(char *pos, int n);
bool solve_N_queen(int row, int n, int board[n][n]);
void returnf(int n, int board[n][n]);
void print_out(int n, int board[n][n]);


int main(void)
{
    while (true) {
        int n;
        char *pos = malloc(5);  
        if (pos == NULL) return 1;
        printf("\nEnter N: ");  
        scanf("%d", &n);
        while (strcmp(pos, "x") != 0) {
            printf("(press x to assign new N value)\nEnter starting position of the Queen: ");  
            scanf("%s", pos);
            NQmain(pos, n);
        }
    }
}


int NQmain(char *pos, int n) 
{
    clock_t t = clock();
    int board[n][n];
    memset(board, EMPTY_NUM, sizeof(board));
    int col = pos[0] - 97; 
    pos++;
    int pos_num = atoi(pos);
    if (pos_num == 0) return 0;
    int row = n - pos_num;
    board[row][col] = QUEEN_NUM;
    if (solve_N_queen(0, n, board)) {
        t = clock() - t;
        double run_time = (double)t/CLOCKS_PER_SEC;
        printf("\nFinished in %.3fs\n", run_time);
        print_out(n, board);
        returnf(n, board);
        return 0;
    }
    printf("No solutions found.\n");
    return 0;
}


bool is_valid(int row, int col, int n, int board[n][n])
{
    for (int i = 0; i < n; i++) if (board[row][i] == QUEEN_NUM) return false; 
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


bool solve_N_queen(int row, int n, int board[n][n])
{
    if (row == n) return true;
    for (int i = 0; i < n; i++) if (board[row][i] == QUEEN_NUM) return solve_N_queen(row+1, n, board);
    for (int i = 0; i < n; i++) {
        if (is_valid(row, i, n, board)) {
            board[row][i] = QUEEN_NUM;
            if (solve_N_queen(row+1, n, board)) return true;
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
            if (board[j][i] == QUEEN_NUM) printf("%c%i, ", i + 97, n - j), count++;
        }
        if (count % (n/2) == 0) printf("\n");
    }
    printf("\n\n");
}


void print_out(int n, int board[n][n])
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
}
