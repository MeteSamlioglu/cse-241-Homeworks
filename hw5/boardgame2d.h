#ifndef BOARDGAME2D_H
#define BOARDGAME2D_H

#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<random>
#include<thread>
#include<chrono>
using namespace std;

namespace SavitcGames{
    enum class GameElements{PEG, EMPTY, WALL};
    enum class Direction{LEFT, RIGHT, UP, DOWN};
    
    
    class BoardGame2D
    {
        public:
        BoardGame2D( );
        BoardGame2D(string GameType);

    
        virtual void playUser(string move) = 0;
        virtual void playUser( ) final; //it takes a string from the user for the next move in a loop and plays the game until it is over.
        virtual void playAuto( ) = 0;  //Plays the game by the computer for one move.
        virtual void playAutoAll( ) final ; //It plays the game by calling playAuto( ) function until it is over.
        virtual bool endGame( ) const = 0; // returns true if the game is ended.
        virtual bool isValidInput(string input) const = 0; // Checks the validity of given input
        virtual int boardScore( ) const ;  //It returns a positive integer that indicates the goodness of the current board, if game is finished return 0.
        virtual void initialize( ) = 0; //initializes the board. For some games the initial board is the same, for other games its random.
        virtual void print( ) const = 0; //prints the game on the screen
        string getGameType( )const; //Returns the type of the game(Human or Computer)
        void setScore(int _score);
        void setGameType(string type);
        void start( ); // Starts the game according to its gametype 
        static void playVector(vector<BoardGame2D*>v);
        friend ostream& operator<<(ostream& outputStream, const BoardGame2D& Obj);



        private:
            string GameType; //Human or Computer
            int score;


    };
    

}//ENDSAVITCH

#endif