#ifndef AI_H
#define AI_H

#include <algorithm>
#include "global.h"

struct Move
{
    char move;
    int score;
    Move(int score) { this->score = score; }
};

class AI
{
    int maxDepth;

public:
    Move minimax(
        Board &board,
        bool isMaximizing,
        int depth,
        int player,
        int alpha,
        int beta);
};

#endif //AI_H