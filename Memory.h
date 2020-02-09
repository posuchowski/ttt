#pragma once

namespace ttt {

  class Memory {

    private:

			class MemCell {
				public:
					int score;
					int moveNum;
					MemCell * nextMove[9];
					MemCell * previous;
					MemCell();
					void setScore(int);
					int getScore(int);
		  };

			int lastMove;
      MemCell * rootCell;  // so ops are the same
      MemCell * movePtr;

    public:

			int winVal, lossVal, tieVal;

      Memory( void );
			void * getRootCellAddr(void);
			void * getMovePtr(void);
			void resetMovePtr(void);
			void retreat(void);
      void advance(int);
      bool doesRemember(int);
			int getMovePtrMove(void);
      int scoreMove(int);
			void backPropagate(int, int);
			void rememberWin(void);
			void rememberLoss(void);
			void rememberTie(void);

	}; // class Memory

} // namespace ttt
