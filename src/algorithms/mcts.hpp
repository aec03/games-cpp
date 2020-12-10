#pragma once

#include <vector>
#include <math.h>
#include <algorithm>
#include <memory>
#include <map>
#include <future>
#include <iostream>
#include <random>
#include <cstdlib>
#include <iomanip>
#include <set>
#include <thread>

namespace MCTS {

    struct ComputeOptions
    {
        int numThreads;
        int maxSims;
        double maxTime;
        bool verbose;

        ComputeOptions() :
            numThreads(8),
            maxSims(10000),
            maxTime(-1.0), // default is no time limit.
            verbose(false) {
        }
    };

    template<typename BoardState>
    class Node {
        Node(const BoardState& state, const int& move, Node* parent);
        Node(const Node&);
        Node& operator = (const Node&);

    public:
        typedef typename BoardState::Move Move;

        Node(const BoardState& state);
        ~Node();

        bool hasMovesLeft() const;

        template<typename RandomEngine>
        Move getMovesLeft(RandomEngine* engine) const;

        void update(double result);

        bool hasChildren() const;
        Node* bestChild();
        Node* selectChild();
        Node* addChild(const Move& move, const BoardState& board);

        const Move move;
        const int playerTurn;
        Node* const parent;

        double score;
        double wins;
        int visits;
        int utility;

        std::vector<Node*> children;
        std::vector<int> moves;
    };
}