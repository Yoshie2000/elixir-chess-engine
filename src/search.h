#pragma once

#include <array>
#include <span>
#include <chrono>

#include "board/board.h"
#include "move.h"

namespace elixir::search {
    class SearchInfo {
    public:
        SearchInfo() = default;
        SearchInfo(int depth) : depth(depth), nodes(0), ply(0), stopped(false), timed(false), x(0), start_time(0), time_left(0) {};
        SearchInfo(int depth, F64 start_time, F64 time_left) : depth(depth), nodes(0), ply(0), stopped(false), timed(true), x(0), start_time(start_time), time_left(time_left) {};
        ~SearchInfo() = default;
        unsigned long long nodes;
        int depth;
        int ply;
        bool stopped;
        bool timed;
        int x;
        F64 start_time;
        F64 time_left;
    };
    
    struct PVariation {
        std::size_t length;
        int score;
        std::array<move::Move, MAX_PLY> line;

        PVariation() : length(0), score(0) {
            for (auto& move : line) {
                move = move::Move();
            }
        }

        std::span<move::Move> moves() {
            return std::span<move::Move>(line.data(), length);
        }

        int score_value() const {
            return score;
        }

        void print_pv() const {
            for (int i = 0; i < length; i++) {
                line[i].print_uci();
                std::cout << " ";
            }
        }

        void load_from(move::Move m, const PVariation& rest) {
            line[0] = m;
            std::copy(rest.line.begin(), rest.line.begin() + rest.length, line.begin() + 1);
            length = rest.length + 1;
        }
    };
    
    int negamax(Board& board, int alpha, int beta, int depth, SearchInfo& info, PVariation& pv);
    void search(Board& board, SearchInfo& info);
}
