#pragma once

namespace ttt {

  class Memory {

    private:

			class MemCell {
				public:
					int score;
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

      Memory( void );
			void * getRootCellAddr(void);
			void * getMovePtr(void);
			void resetMovePtr(void);
      void advance(int);
      bool doesRemember(int);
      int scoreMove(int);

	}; // class Memory

} // namespace ttt
