#pragma once

#include <vector>
#include "Board.h"
#include "Memory.h"

namespace ttt {

	struct AiMove {
		int move;
		int score;
	};

	class AiPlayer {

		private:
			Memory * memory;
			std::vector<AiMove *> possibleMoves;
			int highestScore;

			void clearPossibleMoves(void);
			void dumpMoveScores(std::string);
			int returnRandomMove(void);
			void scoreMovesFromMemory(void);
			void findHighestScore(void);
			void dropLowerThanHighest(void);
			void scoreObviousWinsAndBlocks(Board *);

		public:
			AiPlayer();
			void collectEmptySquares(Board *);
			void dumpPossibleMoves(void);
			const std::vector<AiMove *>& getPossibleMoves(void);
			int makeMove(Board *);
			void onNewGame(void);
			void onLoss(void);
			void onWin(void);
			void onTie(void);

	}; // class AiPlayer

} // namespace ttt

