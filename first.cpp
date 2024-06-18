#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 4;
int board[SIZE][SIZE];

void initializeBoard() {
    // Initialize the board with zeros
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = 0;
        }
    }
}

void generateNewTile() {
    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                emptyCells.push_back(make_pair(i, j));
            }
        }
    }
    
    if (!emptyCells.empty()) {
        srand(time(0));
        int index = rand() % emptyCells.size();
        int row = emptyCells[index].first;
        int col = emptyCells[index].second;
        board[row][col] = (rand() % 2 + 1) * 2; // Generate 2 or 4
    }
}

void drawBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

bool canMove() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) return true;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return true;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return true;
        }
    }
    return false;
}

void compress(int row[]) {
    int temp[SIZE] = {0};
    int index = 0;
    for (int i = 0; i < SIZE; ++i) {
        if (row[i] != 0) {
            temp[index++] = row[i];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        row[i] = temp[i];
    }
}

void merge(int row[]) {
    for (int i = 0; i < SIZE - 1; ++i) {
        if (row[i] == row[i + 1] && row[i] != 0) {
            row[i] *= 2;
            row[i + 1] = 0;
            i++;
        }
    }
}

void moveLeft() {
    for (int i = 0; i < SIZE; ++i) {
        compress(board[i]);
        merge(board[i]);
        compress(board[i]);
    }
}

void rotateBoard() {
    int temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = board[j][SIZE - i - 1];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = temp[i][j];
        }
    }
}

void moveRight() {
    rotateBoard();
    rotateBoard();
    moveLeft();
    rotateBoard();
    rotateBoard();
}

void moveUp() {
    rotateBoard();
    rotateBoard();
    rotateBoard();
    moveLeft();
    rotateBoard();
}

void moveDown() {
    rotateBoard();
    moveLeft();
    rotateBoard();
    rotateBoard();
    rotateBoard();
}

void handleInput(char input) {
    switch (input) {
        case 'w':
            moveUp();
            break;
        case 's':
            moveDown();
            break;
        case 'a':
            moveLeft();
            break;
        case 'd':
            moveRight();
            break;
    }
}

int main() {
    initializeBoard();
    generateNewTile();
    generateNewTile();
    drawBoard();

    while (canMove()) {
        char input;
        cin >> input;
        handleInput(input);
        generateNewTile();
        drawBoard();
    }

    cout << "Game Over!" << endl;

    return 0;
}

