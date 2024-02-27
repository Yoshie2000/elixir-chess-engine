#pragma once

#include <vector>

#include "defs.h"
#include "types.h"
#include "move.h"
#include "hashing/hash.h"

namespace elixir
{
    constexpr int default_tt_size = 64;
    enum TTFlag : U8
    {
        TT_NONE,
        TT_EXACT,
        TT_ALPHA,
        TT_BETA
    };

    struct TTEntry
    {
        U64 key = 0ULL;
        I16 score = 0;
        move::Move move = move::Move();
        U8 depth = 0;
        TTFlag flag = TT_NONE;

        bool operator==(const TTEntry &other) const
        {
            return key == other.key && score == other.score && depth == other.depth && flag == other.flag;
        }
        bool operator==(const U64 &other) const
        {
            return key == other;
        }
    };

    struct ProbedEntry
    {
        int score;
        move::Move best_move;
        U8 depth;
        TTFlag flag;

        ProbedEntry() : score(0), best_move(move::Move()), depth(0), flag(TT_NONE) {}

        inline ProbedEntry operator=(const TTEntry &entry)
        {
            score = entry.score;
            best_move = entry.move;
            depth = entry.depth;
            flag = entry.flag;
            return *this;
        }
    };

    class TranspositionTable
    {
    public:
        TranspositionTable(U16 size = default_tt_size);
        ~TranspositionTable() = default;
        void clear_tt();
        void store_tt(U64 key, int score, move::Move move, U8 depth, TTFlag flag);
        bool probe_tt(ProbedEntry &result, U64 key, U8 depth, int alpha, int beta);
        // assign probed entry to tt entry, oeprator overload

    private:
        inline U32 get_index(U64 key) const { return key % table.size(); }
        std::vector<TTEntry> table;
    };
}