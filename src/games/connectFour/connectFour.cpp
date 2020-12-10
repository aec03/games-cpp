#include <iostream>
#include "connectFourBoard.hpp"

#include <mcts.hpp>

#define LOG(x) std::cout << x << std::endl

int main() {
    ConnectFourBoard board(8, 9);
    MCTS::ComputeOptions options;

    board.makeMove(5);
    LOG(board);
    board.undoMove();
    LOG(board);
    return 0;
}