#include "mcts.hpp"

namespace MCTS {

    template<typename BoardState>
    Node<BoardState>::Node(const BoardState& state) :
        move(BoardState::noMove),
        parent(nullptr),
        playerTurn(state.playerTurn),
        wins(0),
        visits(0),
        moves(state.getMoves()),
        score(0) {
    }

    template<typename BoardState>
    Node<BoardState>::Node(const BoardState& state, const int& move_, Node* parent_) :
        move(move_),
        parent(parent_),
        playerTurn(state.playerTurn),
        wins(0),
        visits(0),
        moves(state.getMoves()),
        score(0) {
    }

    template<typename BoardState>
    Node<BoardState>::~Node() {
        for (auto child : children) {
            delete child;
        }
    }

    template<typename BoardState>
    bool Node<BoardState>::hasMovesLeft() const {
        return !moves.empty();
    }

    template<typename BoardState>
    template<typename RandomEngine>
    typename BoardState::Move Node<BoardState>::getMovesLeft(RandomEngine* engine) const {
        std::uniform_int_distribution<std::size_t> movesDistribution(0, moves.size() - 1);
        return moves[movesDistribution(*engine)];
    }

    template<typename BoardState>
    bool Node<BoardState>::hasChildren() const {
        return !children.empty();
    }

    template<typename BoardState>
    Node<BoardState>* Node<BoardState>::bestChild() {
        return *std::max_element(children.begin(), children.end(), [](Node* a, Node* b) { return a->visits < b->visits; });
    }

    template<typename BoardState>
    Node<BoardState>* Node<BoardState>::selectChild() {
        for (auto child : children) {
            child->score = double(child->wins) / double(child->visits) + std::sqrt(2.0 * std::log(double(this->visits)) / child->visits);
        }

        return *std::max_element(children.begin(), children.end(), [](Node* a, Node* b) { return a->score < b->score; });
    }

    template<typename BoardState>
    Node<BoardState>* Node<BoardState>::addChild(const Move& move, const BoardState& state) {
        auto node = new Node(state, move, this);
        children.push_back(node);

        auto itr = moves.begin();
        for (; itr != moves.end() && *itr != move; ++itr);
        std::iter_swap(itr, moves.end() - 1);
        moves.resize(moves.size() - 1);
        return node;
    }

    template<typename BoardState>
    void Node<BoardState>::update(double result) {
        visits++;
        wins += result;
    }
}