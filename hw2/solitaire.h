#ifndef _SOLITAIRE_H
#define _SOLITAIRE_H
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <random>
#include <chrono>
using namespace std;

enum class board_element{PEG, EMPTY, WALL};    /* Game board elements */
enum class movement_direction{LEFT, RIGHT, UP, DOWN}; /* Directions */
void game_type_choice(vector<vector<board_element>>&v); /* Choosing if game is human  or computer game */
void human_game(vector<vector<board_element>>&v, int number_of_moves=0);      /* Human game choice */
void computer_game(vector<vector<board_element>>&v, int number_of_moves=0);   /* Computer game choice */
bool load_command_check(string str); /* Checks LOAD command  */
bool save_command_check(string str); /* Checks SAVE command */
void save_to_file(const vector<vector<board_element>>&v,string command,int number_of_moves,char game_type);/* To save current game's informations */
void load_from_file(vector<vector<board_element>>&v,string command); /* To load a game from file */
bool random_computer_move(vector<vector<board_element>>&v, int row, int column, char column_letter,int &number_of_moves); /* Computer makes a random move toward random direction*/
bool movement_input_check(const vector<vector<board_element>>,vector<char>str);/* This function checks if user's input is valid or not */
bool check_valid_move(const vector<vector<board_element>>v, int row, int column, movement_direction direction);/* This function checks input movement is valid or not */
bool check_game_end(const vector<vector<board_element>>v); /* This function checks current game board and determines if game is over */
void set_movement(int row_index, char column_index, movement_direction direction, vector<vector<board_element>>&v, int &number_of_moves);/*This function replaces the old board element with current element */
void print_board(const vector<vector<board_element>>v); /* This function prints game board without row numbers and column letters */
void print_game_board(const vector<vector<board_element>>v); /* This function prints game board with row numbers and column letters */
int find_peg_count(const vector<vector<board_element>>v); /* This function returns current peg count on the game board */

#endif