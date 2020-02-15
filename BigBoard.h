#pragma once
#include "Board.h"

namespace ttt {

	class BigBoard {

		private:

			bool hasWin, hasTie;
			char starter, mover, winner;

			Board * boards[9];
			void allocateBoards(void);

		public:
			BigBoard();
			bool subBoardHasWin(int);
			bool subBoardHasTie(int);
			char subBoardWinner(int);

			void move(int, char, int, int );
			char intSymbolAt(int, int);
			void subBoardCharRepr(int, char* );

	}; // class BigBoard

} // namespace ttt

