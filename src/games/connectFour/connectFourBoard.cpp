#include "connectFourBoard.hpp"

ConnectFourBoard::ConnectFourBoard(int numRows, int numCols)
    : playerTurn(1), _numRows(numRows), _numCols(numCols) {
    _board.resize(_numRows, std::vector<char>(_numCols, playerMarkers[0]));
}

void ConnectFourBoard::print(std::ostream& out) {
    out << "\n";
    for (int row = 0; row < _numRows; row++) {
        for (int col = 0; col < _numCols; col++) {
            auto peice = _board[row][col];
            if (peice == playerMarkers[1]) {
                out << " " << RED << _board[row][col] << RESET;
            } else if (peice == playerMarkers[2]) {
                out << " " << YELLOW << _board[row][col] << RESET;
            } else {
                out << " " << _board[row][col] << RESET;
            }
        }
        out << "\n";
    }

    for (int col = 0; col < _numCols; col++) {
        out << " " << col;
    }
    out << "\n\n";
}

int ConnectFourBoard::makeMove(Move move) {
    int row = _numRows - 1;
    while (_board[row][move] != playerMarkers[0]) row--;
    _board[row][move] = playerMarkers[playerTurn];

    _lastCol = move;
    _lastRow = row;

    playerTurn = 3 - playerTurn;

    return row;
}

void ConnectFourBoard::undoMove() {
    _board[_lastRow][_lastCol] = playerMarkers[0];
}

bool ConnectFourBoard::boardFull() {
    if (getWinner() != playerMarkers[0]) {
        return true;
    }

    for (int col = 0; col < _numCols; col++) {
        if (_board[0][col] == playerMarkers[0]) {
            return false;
        }
    }
    return true;
}

bool ConnectFourBoard::columnFull(int column) {
    return _board[0][column] != playerMarkers[0];
}

// int ConnectFourBoard::scoreBoard() {
//     int counters[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//     typedef int grid[_numRows][_numCols];
//     const grid& scores = _board;

//     // Horizontal spans
//     for (int y = 0; y < _numRows; y++) {
//         int score = scores[y][0] + scores[y][1] + scores[y][2];
//         for (int x = 3; x < _numCols; x++) {
//             score += scores[y][x];
//             counters[score + 4]++;
//             score -= scores[y][x - 3];
//         }
//     }
//     // Vertical spans
//     for (int x = 0; x < _numCols; x++) {
//         int score = scores[0][x] + scores[1][x] + scores[2][x];
//         for (int y = 3; y < _numRows; y++) {
//             score += scores[y][x];
//             counters[score + 4]++;
//             score -= scores[y - 3][x];
//         }
//     }
//     // Down-right (and up-left) diagonals
//     for (int y = 0; y < _numRows - 3; y++) {
//         for (int x = 0; x < _numCols - 3; x++) {
//             int score = 0;
//             for (int idx = 0; idx < 4; idx++) {
//                 int yy = y + idx;
//                 int xx = x + idx;
//                 score += scores[yy][xx];
//             }
//             counters[score + 4]++;
//         }
//     }
//     // up-right (and down-left) diagonals
//     for (int y = 3; y < _numRows; y++) {
//         for (int x = 0; x < _numCols - 3; x++) {
//             int score = 0;
//             for (int idx = 0; idx < 4; idx++) {
//                 int yy = y - idx;
//                 int xx = x + idx;
//                 score += scores[yy][xx];
//             }
//             counters[score + 4]++;
//         }
//     }
//     if (counters[0] != 0)
//         return playerMarkers[playerTurn];
//     else if (counters[8] != 0)
//         return COMP_WIN;
//     else // heuristic function
//         return counters[5] + 5 * counters[6] + 10 * counters[7] -
//         counters[3] - 2 * counters[2] - 5 * counters[1];
// }

char ConnectFourBoard::getWinner() {
    if (_lastCol < 0) return playerMarkers[0];

    char piece = _board[_lastRow][_lastCol];

    // horizonal win
    int left = 0, right = 0;
    for (int col = _lastCol - 1; col >= 0 && _board[_lastRow][col] == piece; --col) left++;
    for (int col = _lastCol + 1; col < 7 && _board[_lastRow][col] == piece; ++col) right++;
    if (left + 1 + right >= 4) {
        return piece;
    }

    // vertical win
    int up = 0, down = 0;
    for (int row = _lastRow - 1; row >= 0 && _board[row][_lastCol] == piece; --row) up++;
    for (int row = _lastRow + 1; row < 6 && _board[row][_lastCol] == piece; ++row) down++;
    if (up + 1 + down >= 4) {
        return piece;
    }

    // left-high -> right-low
    up = 0;
    down = 0;
    for (int row = _lastRow - 1, col = _lastCol - 1; row >= 0 && col >= 0 && _board[row][col] == piece; --row, --col) up++;
    for (int row = _lastRow + 1, col = _lastCol + 1; row < 6 && col < 7 && _board[row][col] == piece; ++row, ++col) down++;
    if (up + 1 + down >= 4) {
        return piece;
    }

    // right-high -> left-low
    up = 0;
    down = 0;
    for (int row = _lastRow + 1, col = _lastCol - 1; row < 6 && col >= 0 && _board[row][col] == piece; ++row, --col) up++;
    for (int row = _lastRow - 1, col = _lastCol + 1; row >= 0 && col < 7 && _board[row][col] == piece; --row, ++col) down++;
    if (up + 1 + down >= 4) {
        return piece;
    }

    return playerMarkers[0];
}

double ConnectFourBoard::getResult(int currentPlayer) {
    auto winner = getWinner();
    if (winner == playerMarkers[0]) {
        return 0.5;
    }

    if (winner == playerMarkers[currentPlayer]) {
        return 0.0;
    } else {
        return 1.0;
    }
}

std::vector<int> ConnectFourBoard::getMoves() const {
    std::vector<int> moves;

    moves.reserve(_numCols);

    for (int col = 0; col < _numCols; col++) {
        if (_board[0][col] == playerMarkers[0]) {
            moves.push_back(col);
        }
    }
    return moves;
}