#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

// Display the board
void showBoard(char board[][SIDE]) {
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

// Show instructions for the user
void showInstructions() {
    printf("\nChoose a cell numbered from 1 to 9 as below and play\n\n");
    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 7 | 8 | 9 \n\n");
}

// Initialize the board
void initialise(char board[][SIDE]) {
    for (int i = 0; i < SIDE; ++i) {
        for (int j = 0; j < SIDE; ++j) {
            board[i][j] = '*';
        }
    }
}

// Declare the winner
void declareWinner(int whoseTurn) {
    if (whoseTurn == COMPUTER)
        printf("COMPUTER has won\n");
    else
        printf("HUMAN has won\n");
}

// Check if a row is crossed
bool rowCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; ++i) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != '*')
            return true;
    }
    return false;
}

// Check if a column is crossed
bool columnCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; ++i) {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != '*')
            return true;
    }
    return false;
}

// Check if a diagonal is crossed
bool diagonalCrossed(char board[][SIDE]) {
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != '*')
        return true;
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != '*')
        return true;
    return false;
}

// Check if the game is over
bool gameOver(char board[][SIDE]) {
    return rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board);
}

// Minimax algorithm to find the best move
int minimax(char board[][SIDE], int depth, bool isAI) {
    int score = 0;
    if (gameOver(board)) {
        if (isAI) return -10;
        else return 10;
    }
    if (depth == SIDE * SIDE) return 0; // Board is full

    int bestScore = isAI ? -999 : 999;
    for (int i = 0; i < SIDE; ++i) {
        for (int j = 0; j < SIDE; ++j) {
            if (board[i][j] == '*') {
                board[i][j] = isAI ? COMPUTERMOVE : HUMANMOVE;
                score = minimax(board, depth + 1, !isAI);
                board[i][j] = '*';
                if (isAI) {
                    bestScore = max(score, bestScore);
                } else {
                    bestScore = min(score, bestScore);
                }
            }
        }
    }
    return bestScore;
}

// Find the best move for the computer
int bestMove(char board[][SIDE], int moveIndex) {
    int x = -1, y = -1;
    int bestScore = -999;
    for (int i = 0; i < SIDE; ++i) {
        for (int j = 0; j < SIDE; ++j) {
            if (board[i][j] == '*') {
                board[i][j] = COMPUTERMOVE;
                int score = minimax(board, moveIndex + 1, false);
                board[i][j] = '*';
                if (score > bestScore) {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * SIDE + y;
}

// Play the Tic-Tac-Toe game
void playTicTacToe(int whoseTurn) {
    char board[SIDE][SIDE];
    int moveIndex = 0;
    initialise(board);
    showInstructions();
    
    while (!gameOver(board) && moveIndex != SIDE * SIDE) {
        int n;
        if (whoseTurn == COMPUTER) {
            n = bestMove(board, moveIndex);
            int x = n / SIDE;
            int y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            printf("COMPUTER has put a %c in cell %d\n\n", COMPUTERMOVE, n + 1);
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        } else if (whoseTurn == HUMAN) {
            printf("You can insert in the following positions: ");
            for (int i = 0; i < SIDE; ++i) {
                for (int j = 0; j < SIDE; ++j) {
                    if (board[i][j] == '*') {
                        printf("%d ", i * SIDE + j + 1);
                    }
                }
            }
            printf("\n\nEnter the position: ");
            scanf("%d", &n);
            n--;
            int x = n / SIDE;
            int y = n % SIDE;
            if (board[x][y] == '*' && n < SIDE * SIDE && n >= 0) {
                board[x][y] = HUMANMOVE;
                printf("\nHUMAN has put a %c in cell %d\n\n", HUMANMOVE, n + 1);
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            } else if (board[x][y] != '*' && n < SIDE * SIDE && n >= 0) {
                printf("\nPosition is occupied, select another position.\n\n");
            } else {
                printf("Invalid position\n");
            }
        }
    }
    
    if (!gameOver(board) && moveIndex == SIDE * SIDE) {
        printf("It's a draw\n");
    } else {
        declareWinner(whoseTurn == COMPUTER ? HUMAN : COMPUTER);
    }
}

// Main function
int main() {
    printf("\n-------------------------------------------------------------------\n\n");
    printf("\t\t\t Tic-Tac-Toe\n");
    printf("\n-------------------------------------------------------------------\n\n");
    
    char cont = 'y';
    do {
        char choice;
        printf("Do you want to start first? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'n') {
            playTicTacToe(COMPUTER);
        } else if (choice == 'y') {
            playTicTacToe(HUMAN);
        } else {
            printf("Invalid choice\n");
        }
        printf("\nDo you want to quit (y/n): ");
        scanf(" %c", &cont);
    } while (cont == 'n');
    
    return 0;
}

