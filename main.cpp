#include <iostream>
#include <vector>
#include <limits>

using namespace std;

char PLAYER;
char AI;
const char EMPTY = '_';

void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool isMovesLeft(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

int evaluate(const vector<vector<char>>& board) {
    for (int row = 0; row < 3; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI) return +10;
            if (board[row][0] == PLAYER) return -10;
        }
    }

    for (int col = 0; col < 3; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI) return +10;
            if (board[0][col] == PLAYER) return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI) return +10;
        if (board[0][0] == PLAYER) return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI) return +10;
        if (board[0][2] == PLAYER) return -10;
    }

    return 0;
}

int minimax(vector<vector<char>>& board, int depth, bool isMaximizing) {
    int score = evaluate(board);

    if (score == 10 || score == -10) return score;

    if (!isMovesLeft(board)) return 0;

    if (isMaximizing) {
        int best = numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    best = max(best, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    best = min(best, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int moveVal = minimax(board, 0, false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

void playGame() {
    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    cout << "To make a move, enter a number between 1 and 9 corresponding to the board positions:\n";
    cout << "1 | 2 | 3\n4 | 5 | 6\n7 | 8 | 9\n";
    printBoard(board);

    while (true) {
        int move;
        cout << "Enter your move (1-9): ";
        cin >> move;

        if (move < 1 || move > 9 || board[(move - 1) / 3][(move - 1) % 3] != EMPTY) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        board[(move - 1) / 3][(move - 1) % 3] = PLAYER;

        if (evaluate(board) == -10) {
            printBoard(board);
            cout << "You win!\n";
            break;
        }

        if (!isMovesLeft(board)) {
            printBoard(board);
            cout << "It's a draw!\n";
            break;
        }

        pair<int, int> aiMove = findBestMove(board);
        board[aiMove.first][aiMove.second] = AI;

        printBoard(board);

        if (evaluate(board) == 10) {
            cout << "AI wins!\n";
            break;
        }

        if (!isMovesLeft(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }
}

int main() {
    while (true) {
        cout << "Welcome to Tic-Tac-Toe!\n";
        cout << "Choose your sign (X or O): ";
        cin >> PLAYER;

        if (PLAYER == 'X' || PLAYER == 'O') {
            AI = (PLAYER == 'X') ? 'O' : 'X';
        } else {
            cout << "Invalid choice. Please choose X or O.\n";
            continue;
        }

        playGame();

        char rematch;
        cout << "Do you want a rematch? (y/n): ";
        cin >> rematch;

        if (rematch != 'y' && rematch != 'Y') {
            cout << "Thanks for playing!\n";
            break;
        }
    }

    return 0;
}
