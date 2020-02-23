#pragma once

namespace ttt {

	class AnyUI {

		public:
			virtual char getHumanSymbol();
			virtual int getMoveBoard();
			virtual int getHumanMove();
			virtual void updateDispay( BigBoard * );
			virtual void updateStats( int, int, int );

		protected:
			virtual int moveBoard;

		};

} // namespace ttt

