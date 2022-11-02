//  solves N queen using backtracking algorithm
//  places Queen on every tile are returns average per position and total time

#include <iostream>
#include <string.h>


#define N 18        //  size of the board

//  _NUM are shown only to program and _CHAR is shown to the user
const int QUEEN_NUM = 1;
const int EMPTY_NUM = 0;
const char QUEEN_CHAR = 'Q';
const char EMPTY_CHAR = '.';


int NQmain();                                       //  directs the program
bool isValid(int row, int col, int board[N][N]);    //  helper function for NQsolve 
bool NQsolve(int row, int board[N][N]);             //  solves NQ using backtracking algorithm
void printOut(int board[N][N]);                     //  prints board


int main(void) 
{
    NQmain();
}


int NQmain() 
{
    int board[N][N];
    long double timeSum;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            memset(board, EMPTY_NUM, sizeof(board));
            board[i][j] = QUEEN_NUM;
            NQsolve(0, board);
            printOut(board);
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    timeSum += duration.count();
    std::cout << std::endl << "Average time per position is " << timeSum/(N*N) << "s and total is " << timeSum << 's';
    return 0;
}


//  checks if queen can be placed on specific position on the board
bool isValid(int row, int col, int board[N][N])
{
    for (int i = 0; i < N; i++) if (board[i][col] == QUEEN_NUM) return false;
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) {
            if (i + j == row + col || i - j == row - col) {
                if (board[i][j] == QUEEN_NUM) return false;
            }
        }
    }
    return true;
}


//  time complexity O(n!)
bool NQsolve(int row, int board[N][N]) 
{
    if (row == N) return true;
    for (int i = 0; i < N; i++) if (board[row][i] == QUEEN_NUM) return NQsolve(row+1, board);
    for (int i = 0; i < N; i++) {
        if (isValid(row, i, board)) {
            board[row][i] = QUEEN_NUM;
            if (NQsolve(row+1, board)) return true;
        }
        board[row][i] = EMPTY_NUM;
    }
    return false;
}


//  print the board in user-readable form and returns Queen positions
void printOut(int board[N][N])
{
    std::cout << std::endl;
    std::string formattedReturn;
    for (int i = 0; i < N; i++) std::cout << ' ' << (char) (97 + i);
    std::cout << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == QUEEN_NUM) {
                std::cout << ' ' << QUEEN_CHAR;
                formattedReturn += 'a' + i%26;
                formattedReturn += std::to_string(N - j);
                if (i != N - 1 && j != N - 1) formattedReturn += ", ";
            }
            else std::cout << ' ' << EMPTY_CHAR;
        }
        std::cout << '|' << N - i << std::endl;
    }
    std::cout << formattedReturn << std::endl;
}