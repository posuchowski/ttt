#pragma once
#include <vector>

namespace ttt {

    class Board {

        private:
            int X, O;
            char winner;
            std::vector<int> winConditions;

        public:
            Board();
            void set_X( int );
            void set_O( int );
            void dump( void );
            void clearScreen( void );
            void cprint( void );
            void move( char, int, int );
            bool isOccupied( int, int );
            bool hasWin( void );
            char getWinner( void );

    };

}

