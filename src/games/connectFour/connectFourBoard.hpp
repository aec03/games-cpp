#pragma once

#include <iostream>
#include <vector>
#include <random>

// COLORS FOR TERMINAL
#define RESET "\033[0m"
#define RED "\033[31m"    /* Red */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m"   /* Blue */

class ConnectFourBoard
{
private:
    std::vector<std::vector<char> > _board;

    int _numCols;
    int _numRows;

    int _lastCol;
    int _lastRow;

public:
    typedef int Move;
    static const Move noMove = -1;

    const char playerMarkers[3] = { '-', 'X', 'O' };
    int playerTurn;

    ConnectFourBoard(int numRows, int numCols);

    void print(std::ostream& out);
    friend std::ostream& operator << (std::ostream& out, ConnectFourBoard& board) {
        board.print(out);
        return out;
    }

    int makeMove(int column);
    void undoMove();

    template<typename RandomEngine>
    void randomMove(RandomEngine* engine);

    bool boardFull();
    bool columnFull(int column);

    char getWinner();
    double getResult(int currentPlayer);


    std::vector<int> getMoves() const;
};