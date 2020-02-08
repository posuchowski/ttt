#pragma once

#include "Board.h"
#include "Memory.h"

namespace ttt {

    private:
			Memory * memory;

    public:
        int makeMove( Board & );
