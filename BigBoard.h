#pragma once
#include "Board.h"

namespace ttt {

	class BigBoard {

		private:

			bool hasWin, hasTie;
			char winner;

			Board boards[9];
			getSubBoardResult(int);

		public:
			BigBoard();

	} // class BigBoard

} // namespace ttt

