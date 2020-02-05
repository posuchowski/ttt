#pragma once

#include <vector>
#include "Board.h"

namespace ttt {

    struct Move {
        int gameID;
        int X;
        int O;
        int move;
        int score;
    }

    private:
        vector<Move> memory;
        vector<Move> book;

    public:
        int makeMove( Board & );
