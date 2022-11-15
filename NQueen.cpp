// * g++ -std=c++17 NQueen.cpp -o NQueen -I/Users/roiqk/SFML/include -L/Users/roiqk/SFML/build/lib  -lsfml-graphics -lsfml-window -lsfml-system


//  this program visualizes backtracking algorithm solving N Queens problem

#include <array>        
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

//  map related -> base N = 16; TILE_SIZE = 50 
//  if you want to decrease N from 16 to 8 you have to increase TILE_SIZE from 50 to 100 and increase QUEEN_SCALE from 0.065 to 0.13
#define N 16                   //  size of one side of the square map
#define TILE_SIZE 50           //  size of one tile on the map

//  window related
#define WIDTH N*TILE_SIZE    //  window width
#define HEIGHT N*TILE_SIZE   //  window height
#define QUEEN_SCALE 0.065    //  scale used for queen iumages to fit into one tile


// return values
#define SUCCESS 0
#define ERROR -1

// create the window     
sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WIDTH, HEIGHT)), "Backtracking algorithm visualizer");

//  constant values describing board values
const int QUEEN_NUM = 1;
const int EMPTY_NUM = 0;


/*
     ######  ##          ###     ######   ######  
    ##    ## ##         ## ##   ##    ## ##    ## 
    ##       ##        ##   ##  ##       ##       
    ##       ##       ##     ##  ######   ######  
    ##       ##       #########       ##       ## 
    ##    ## ##       ##     ## ##    ## ##    ## 
     ######  ######## ##     ##  ######   ######  
*/


//  Board stores all important data and renders the actual board seen by the user and also draws queens
class Board {
    public:
        std::array<sf::RectangleShape, N> boardTiles;
        std::array<std::array<int, N>, N> map;
        sf::Texture whiteQueenTexture;
        sf::Texture blackQueenTexture;
        sf::Sprite queenSprite;
        int black;        

        Board() {
            map = {{EMPTY_NUM}};
            if (!whiteQueenTexture.loadFromFile("path to /whiteQueen.png")) std::exit(0);
            if (!blackQueenTexture.loadFromFile("path to /blackQueen.png")) std::exit(0);
        }

        //  draws the bard
        void render(void)
        {
            black = 0;
            window.clear();
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    boardTiles[i].setPosition (sf::Vector2f(j*TILE_SIZE, i*TILE_SIZE));
                    boardTiles[i].setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                    queenSprite.setScale(sf::Vector2f(QUEEN_SCALE, QUEEN_SCALE));
                    if (black % 2 == true) {
                        boardTiles[i].setFillColor(sf::Color::Black);
                        queenSprite.setTexture(whiteQueenTexture);
                    } 
                    else {
                        boardTiles[i].setFillColor(sf::Color::White);
                        queenSprite.setTexture(blackQueenTexture);
                    }
                    window.draw(boardTiles[i]);
                    if (map[i][j] == QUEEN_NUM) {
                        queenSprite.setPosition (sf::Vector2f(j*TILE_SIZE, i*TILE_SIZE));
                        window.draw(queenSprite);
                    }
                    black++; 
                }
                black++;
            }
            window.display();
        }
};


void addRandomQueen(Board &board);              //  adds random queen for uniqueness
void sfml(Board &board);                        //  draws the screen
bool NQsolve(Board &board, int row);            //  backtracking algorithm solving N Queen
void printOut(Board &board);                    //  prints board to the console


/*
    ##     ##    ###    #### ##    ## 
    ###   ###   ## ##    ##  ###   ## 
    #### ####  ##   ##   ##  ####  ## 
    ## ### ## ##     ##  ##  ## ## ## 
    ##     ## #########  ##  ##  #### 
    ##     ## ##     ##  ##  ##   ### 
    ##     ## ##     ## #### ##    ## 
*/


//  starts the program
int main()
{
    Board board = Board();

    addRandomQueen(board);

    sfml(board);
     
    return SUCCESS;
}


//  makes the program more unique and interesting
void addRandomQueen(Board &board)
{
    srand(time(NULL));
    int row = rand()%N;
    int col = rand()%N;
    board.map[row][col] = QUEEN_NUM;
}


/*
     ######  ######## ##     ## ##       
    ##    ## ##       ###   ### ##       
    ##       ##       #### #### ##       
     ######  ######   ## ### ## ##       
          ## ##       ##     ## ##       
    ##    ## ##       ##     ## ##       
     ######  ##       ##     ## ######## 
*/


//  opens the window and calls solving function
void sfml(Board &board)
{
    window.setFramerateLimit (60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        NQsolve(board, 0);
    }
    return;
}


/*
       ###    ##        ######    #######  ########  #### ######## ##     ## ##     ## 
      ## ##   ##       ##    ##  ##     ## ##     ##  ##     ##    ##     ## ###   ###
     ##   ##  ##       ##        ##     ## ##     ##  ##     ##    ##     ## #### #### 
    ##     ## ##       ##   #### ##     ## ########   ##     ##    ######### ## ### ## 
    ######### ##       ##    ##  ##     ## ##   ##    ##     ##    ##     ## ##     ##     
    ##     ## ##       ##    ##  ##     ## ##    ##   ##     ##    ##     ## ##     ##
    ##     ## ########  ######    #######  ##     ## ####    ##    ##     ## ##     ##  
*/


//  checks if queen can be placed on specific position on the board
bool isValid(Board &board, int &row, int &col)
{
    for (int i = 0; i < N; i++) if (board.map[i][col] == QUEEN_NUM) return false;
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < N; j++) {
            if (i + j == row + col || i - j == row - col) {
                if (board.map[i][j] == QUEEN_NUM) return false;
            }
        }
    }
    return true;
}


/*
* Implementation of backtracking algorithm, O(n!)
The idea is to place queens one by one in different columns, 
starting from the leftmost column. When we place a queen in a column, 
we check for clashes with already placed queens. In the current column, 
if we find a row for which there is no clash, we mark this row and column as part of the solution. 
If we do not find such a row due to clashes, then we backtrack and return false.
*/
bool NQsolve(Board &board, int row) 
{
    if (row == N) return true;
    for (int i = 0; i < N; i++) if (board.map[row][i] == QUEEN_NUM) return NQsolve(board, row+1);
    for (int i = 0; i < N; i++) {
        if (isValid(board, row, i)) {
            board.map[row][i] = QUEEN_NUM;
            board.render();   
            printOut(board);
            if (NQsolve(board, row+1)) return true;
        }
        board.map[row][i] = EMPTY_NUM;
    }
    return false;
}


//  print the board in user-friendly form and returns Queen positions (not designed for N > 27)
void printOut(Board &board)
{
    std::cout << std::endl;
    std::string formattedReturn;
    for (int i = 0; i < N; i++) std::cout << ' ' << (char) (97 + i);
    std::cout << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board.map[i][j] == QUEEN_NUM) {
                std::cout << ' ' << 'Q';
                formattedReturn += 'a' + i%26;
                formattedReturn += std::to_string(N - j);
                if (i != N - 1 && j != N - 1) formattedReturn += ", ";
            }
            else std::cout << ' ' << '.';
        }
        std::cout << '|' << N - i << '\n';
    }
    std::cout << '\n' << formattedReturn << '\n';
}
