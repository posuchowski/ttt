#pragma once

namespace ttt {

	class MemCell {

		private:
			int boardX, boardO, move, score;
			MemCell * nextMove[9];

		public:
			void setScore( int );
			int getScore( void );

			void setMove( int );
			int getMove( void );

			bool addMove( MemCell * );
			int getBestMove( void );
			
	};

}

