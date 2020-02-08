#pragma once

#include <vector>
#include "Board.h"
#include "Memory.h"

namespace ttt {

	struct Move {
		int move;
		int score;
	}

	class AI {

		private:
			Memory * memory;
			std::vector<Move> possibleMoves;

		public:
			AI(void);
			void collectBoardPossibleMoves(Board & board);
			int makeMove(Board &);
