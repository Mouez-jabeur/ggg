#include <iostream>

using namespace std;

char board[3][3];
char currentMarker;
int currentPlayer;

void drawBoard() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

bool placeMarker(int row, int col) {
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
        board[row][col] = currentMarker;
        return true;
    }
    return false;
}

int checkWin() {
    // Rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return currentPlayer;
    }
    // Columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return currentPlayer;
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return currentPlayer;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return currentPlayer;

    return 0;
}

void swapPlayerAndMarker() {
    if (currentMarker == 'X') currentMarker = 'O';
    else currentMarker = 'X';

    if (currentPlayer == 1) currentPlayer = 2;
    else currentPlayer = 1;
}

void initializeBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void game() {
    initializeBoard();
    currentMarker = 'X';
    currentPlayer = 1;
    int playerWon = 0;
    int row, col;

    for (int i = 0; i < 9; i++) {
        drawBoard();
        cout << "It's player " << currentPlayer << "'s turn. Enter row and column: ";
        cin >> row >> col;
        row--; col--; // Adjust for 0-based indexing

        if (placeMarker(row, col)) {
            playerWon = checkWin();
            if (playerWon == 1) {
                cout << "Player 1 wins!" << endl;
                break;
            }
            if (playerWon == 2) {
                cout << "Player 2 wins!" << endl;
                break;
            }
            swapPlayerAndMarker();
        } else {
            cout << "That spot is taken! Try again." << endl;
            i--; // Do not count this iteration as a valid move
        }
    }
    if (playerWon == 0)
        cout << "It's a tie!" << endl;

    drawBoard();
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    game();
    return 0;
}

