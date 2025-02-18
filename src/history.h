#pragma once

#include "defs.h"
#include "move.h"
#include "types.h"

namespace elixir {
    extern int HISTORY_GRAVITY;
    class History {
      public:
        History()  = default;
        ~History() = default;

        void clear();
        void update_history(Square from, Square to, int depth, MoveList &bad_quiets);
        int get_history(Square from, Square to) const;

      private:
        int scale_bonus(int score, int bonus);
        int history[64][64] = {0};
    };
}