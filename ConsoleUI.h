#pragma once
#include "BigBoard.h"

namespace ttt {

	class ConsoleUI {

		private:
			int moveBoard;

		public:
			ConsoleUI();
			char getHumanSymbol();
			int getMoveBoard();
			int getHumanMove();
			int updateDisplay( BigBoard * );

	}

} // namespace ttt

