#ifndef PEGSOLITAIRE_H
#define PEGSOLITAIRE_H
#include"BoardGame2D.h"

using namespace std;

namespace SavitcGames
{
   
    class PegSolitaire : public BoardGame2D
    {
        public:
            PegSolitaire( );
            PegSolitaire(string typeofGame);
            void playUser(string move) override;
            void playAuto( ) override;
            void setMove(int row_index, char column_index, Direction move); //Sets user's move
            bool isValidMove(int row, int column, Direction move) const; /* Checks the validity of move */
            bool isRandomMoveValid(int row, int column, char column_letter);
            bool isValidInput(string input) const override;
            void findScore( );
            bool endGame( ) const override; //Checks if game end or not
            void print( ) const override; /* Prints the game on the screen */
            void initialize( ) override;
        

            class Cell{
                public:
                    Cell();
                    bool checkElement(GameElements elm) const;
                    void setElement(int row_index,char column_index,GameElements element);

                private:
                    int row;
                    char column;
                    GameElements element;
        };

        private:
            vector<vector<Cell>>Board;
            void CreateBoard(vector<vector<GameElements>>v);
    };


}
#endif