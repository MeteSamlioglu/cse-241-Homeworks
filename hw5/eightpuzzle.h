#ifndef EIGHTPUZZLE_H
#define EIGHTPUZZLE_H
#include"BoardGame2D.h"
#include<string>
using namespace std;

namespace SavitcGames{

    
    class EightPuzzle : public BoardGame2D
    {
        public:
            EightPuzzle( );
            EightPuzzle(string GameType);
            EightPuzzle(const EightPuzzle& Obj); //Copy Constructor
            ~EightPuzzle( );
            EightPuzzle& operator = (const EightPuzzle& Obj);
            void playUser(string move) override;
            void playAuto( ) override;
            void setMove(Direction direction, int row, int column);
            void initialize( ) override; /* Initializes 3x3 game board */
            void createBoard( ); //Creates random board
            void printHorizantonal( ) const;
            void print( )const override; 
            bool endGame( ) const override;
            bool isValidInput(string input) const override;
            bool isSolvable( ) const;
           
       

        private:
            int**Board;

    };

}
#endif