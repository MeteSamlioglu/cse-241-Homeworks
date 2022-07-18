#ifndef _SOLITAIRE_H
#define _SOLITAIRE_H
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstring>
#include <random>
#include <chrono>
using namespace std;

enum class board_element{PEG, EMPTY, WALL};
enum class Direction{LEFT, RIGHT, UP, DOWN};

int input_check(int input,int lower_interval, int upper_interval);

class PegSolitaire
{

public:
    PegSolitaire();
    PegSolitaire(int choosen_board);
    PegSolitaire(int choosen_board, int type_of_game);

    void read_from_file(string input_file);      
    void write_to_file(string input_file) const;
    void display_game() const; /* Displays current game on screen */
    void display_object_info() const; /* Displays current game/object's informations on the screen */
    void print_board(vector<vector<board_element>>v ) const; /* This function prints board without column letters and row numbers */
    
    void SetGameBoard(int board_index);
    void SetGameType(int type_of_game); /* Ask user that if the game is human game or computer game */
    
    void Start();
    void HumanGame(); /* User plays the game */
    void playGame(); //This function plays the game by asking the user the board type first then automatically plays the game until it ends.
    
 
 
    void play(int row_index, char column_index, Direction move); //It plays the user.   
    void play(); //It plays automatically
    
    bool isValidMove(int row, int column, Direction move) const; /* Checks the validity of move */
    bool isRandomMoveValid(int row, int column, char column_letter); /* Check whether computer's random move is valid, if it is a valid move upgrade game board */
    bool isValidInput(string input) const;
    bool isGameOver() const; // Checks if game is ended
    bool CompareGames(const PegSolitaire& game2) const; //If class has more pegs it returns true, otherwise return false 
    

    static int sumAllPegs(int empty_cells, int total_pegs); // Pegs Summation of all active games 
    static int getTotalPegs(); /* Return static int TotalNumberOfPegs */
    static void setToZero(); // Every step, set static private TotalNumberOfPegs variable to zero 

    inline int getGameType() const; // Returns game type 
    inline int CheckCommand(string command) const; /* Checks command input LOAD/SAVE/EXIT */
    inline int number_of_pegs() const; /* Returns number of pegs on the current game board */
    inline int number_of_taken_pegs() const; /* Returns number of taken pegs on the game board */
    inline int number_of_empty_cells() const; /* Returns empty cells on the game board */


    class Cell{
        public:
        Cell();
        bool checkElement(board_element elm) const;
        void setElement(int row,char column,board_element element);

        private:
            int row;
            char column;
            board_element element;

    };

    
    private:
        static int TotalNumberOfPegs;
        vector<vector<Cell>> game;
        void CreateBoard(vector<vector<board_element>>v);
        int game_type;
        int board_type;
        bool isBoardInitialized;
};



#endif