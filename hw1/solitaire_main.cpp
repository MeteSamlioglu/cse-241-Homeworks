#include"solitaire.h"

int main(){
                /* All game boards */ 
                /* I've created them manually which was way easier when compared to create them by using nested loops */
                /* I didn't understand game board 6's moves(there were 8 different moves) so that I didn't add this board */
  int choose_game_board=0, game_choice=0;    
    vector<vector<board_element>>game_type_1{
       {board_element::WALL, board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL},
       {board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL},
       {board_element::PEG,board_element::PEG,board_element::PEG,board_element::EMPTY,board_element::PEG,board_element::PEG,board_element::PEG},
       {board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
       {board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
       {board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL},
       {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL}
   };   
   vector<vector<board_element>>game_type_2{
      {board_element::WALL,board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
      {board_element::WALL,board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
      {board_element::WALL,board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
      {board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
      {board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::EMPTY,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
      {board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
      {board_element::WALL,board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
      {board_element::WALL,board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
      {board_element::WALL,board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL}
   };
    vector<vector<board_element>>game_type_3{
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
        {board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
        {board_element::PEG,board_element::PEG,board_element::PEG,board_element::EMPTY,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
        {board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL}
    };

    vector<vector<board_element>>game_type_4{
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL},
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL},
        {board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
        {board_element::PEG,board_element::PEG,board_element::PEG,board_element::EMPTY,board_element::PEG,board_element::PEG,board_element::PEG},
        {board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL},
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL}
    };
    vector<vector<board_element>>game_type_5{
        {board_element::WALL,board_element::WALL,board_element::WALL,board_element::WALL,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL,board_element::WALL},
        {board_element::WALL,board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL},
        {board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL},
        {board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::EMPTY,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG},
        {board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL},
        {board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL},
        {board_element::WALL,board_element::WALL,board_element::WALL,board_element::PEG,board_element::PEG,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL},
        {board_element::WALL,board_element::WALL,board_element::WALL,board_element::WALL,board_element::PEG,board_element::WALL,board_element::WALL,board_element::WALL,board_element::WALL}
    };
    
    cout<<"Choose your Board  from 1 to 5."<<endl;  /* Choose your game board */
    cout<<"1-)"<<endl; 
    print_board(game_type_1);
    cout<<endl<<"2-)"<<endl;
    print_board(game_type_2);
    cout<<"3-)"<<endl;
    print_board(game_type_3);
    cout<<"4-)"<<endl;
    print_board(game_type_4);
    cout<<"5-)"<<endl;
    print_board(game_type_5);
    cout<<endl<<"Game board: ";
    cin>>choose_game_board;
    while(1){
        if(choose_game_board>5 || choose_game_board<1){                /* Check user's input */
            cout<<"Your input is not valid, please enter a valid input!"<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"Game board: ";
            cin>>choose_game_board;
        }
        else
            break;
    }                       /* The player chose the game board, it is time to  pass choosen game board vector to game_screen function */
    switch(choose_game_board){              /* Pass chosen 2D vector to game_type_choice function and let user choose game type */
        case 1:
            game_type_choice(game_type_1);
            break;
        case 2:
            game_type_choice(game_type_2);
            break;
        case 3: 
            game_type_choice(game_type_3);
            break;
        case 4:
            game_type_choice(game_type_4);
            break;
        case 5:
            game_type_choice(game_type_5);
            break;
        default:
            break;
    }
}