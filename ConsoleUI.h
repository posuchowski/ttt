#pragma once
#include "Board.h"
#include "BigBoard.h"

namespace ttt {

	class ConsoleUI {

		private:
			int moveBoard;

		public:
			ConsoleUI();
			void startGame();
			char getHumanSymbol();
			int getMoveBoard();
			int getHumanMove();
			void updateDisplay( BigBoard * );
			void updateStats( int, int, int );
			void printOneBoard( Board * );

			void onGameWon(int);
			void onGameLost(int);
			void onGameTied(int);

			void goodBye();

	};

} // namespace ttt

