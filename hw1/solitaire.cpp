#include"solitaire.h"


void game_type_choice(vector<vector<board_element>>&v){ /*Ask the user if game is human player game or a computer game */
    int game_choice=0;
    cout<<"1-)Human player game"<<endl;
    cout<<"2-)Computer game"<<endl;
    cout<<"Human player game or computer game ? 1|2: ";
    cin>>game_choice;
     while(1){
        if(game_choice<1 || game_choice>2){ /* Check user's input */ 
            cout<<"Your input is not valid, please enter a valid input!"<<endl;
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"Human player game or computer game ? 1|2:";
            cin>>game_choice;
        }
        else
            break;
    }       
    switch(game_choice){  /* The game is starting */
        case 1:
            human_game(v);
            break;
        case 2:
            computer_game(v);
            break;
        
        default:
            break;

    }
}

int find_peg_count(const vector<vector<board_element>>v){ /* This function returns current peg count on the game board */
    int peg_count=0;
    for(int i=0; i<v.size(); ++i){
        for(int j=0; j<v[i].size(); ++j){
            if(v[i][j]==board_element::PEG)
                peg_count++;
        }
    }
    return peg_count;
}

void human_game(vector<vector<board_element>>&v){  /* User game and its regarding functions */
    vector<char>movement;
    movement_direction direction;
    string str;
    int row=0, initial_pegs=0, final_score=0;
    char column, direct;
    
    initial_pegs=find_peg_count(v);
    
    cout<<"The game has started !"<<endl;
    while(1){
        print_game_board(v);
        cout<<"Please make a move : ";
        cin>>str;    
        for(int i=0; i<str.size(); ++i)
            movement.push_back(str.at(i));
        
        while(1){
            if(movement_input_check(v,movement)==true)     /* Make sure that given input is valid */
                break;                               /* Call movement_input_check function to check given input */
            else{
                cout<<"Error, Your movement is not valid,please enter a valid movement. "<<endl;
                cout<<"Please make a move : ";
                movement.clear(); /* Eleminate possible input mistakes */
                cin>>str;
                cin.clear();
                cin.ignore(256,'\n');
                for(int i=0; i<str.size(); ++i)
                    movement.push_back(str.at(i));
            }
        }    
        column=str[0];  /* Column letter */
        row=str[1]-'0'; /* To turn  char number into integer */
        direct=str[3];
        switch(direct){
            case 'L':
                direction=movement_direction::LEFT;
                set_movement(row, column, direction,v);
                break;
            case 'l':
                direction=movement_direction::LEFT;
                set_movement(row, column, direction,v);
                break;
            case 'R':
                direction=movement_direction::RIGHT;
                set_movement(row, column, direction,v);
                break;
            case 'r':
                direction=movement_direction::RIGHT;
                set_movement(row, column, direction, v);
                break;
            case 'U':
                direction=movement_direction::UP;
                set_movement( row, column, direction,v);
                break;
            case 'u':
                direction=movement_direction::UP;
                set_movement( row, column, direction, v);
                break;
            case 'D':
                direction=movement_direction::DOWN;
                set_movement( row, column, direction, v);
                break;
            case 'd':
                direction=movement_direction::DOWN;
                set_movement( row, column, direction, v);
                break;
            default:
                break;
        }
        if(check_game_end(v)==true){   /* Game end condition */
            final_score=find_peg_count(v); 
            print_game_board(v);
            cout<<"The game is over"<<endl;
            cout<<"Your score is : "<<final_score<<" out of "<<initial_pegs; 
            break;
        }
    }

}

void computer_game(vector<vector<board_element>>&v){ /* Computer's game and its functions */
    int column_count=0, row_count=0, random_row_number=0, random_column_number=0;
    int initial_peg=0, final_score=0;
    bool break_condition=false;
    char ch='a';
    unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
    mt19937 number_generator(seed);
    for(int i=0; i<v.size(); ++i)  /* First we need to find total row and column count to generate valid random move */
        row_count++;
    
    for(int j=0; j<v[0].size(); ++j)
        column_count++;
    
    uniform_int_distribution<int>row_interval(0, row_count-1);   /*   Determination of valid random number intervals for both cases */
    uniform_int_distribution<int>column_interval(0, column_count-1);
    initial_peg=find_peg_count(v);
    cout<<"Computer game has started, good luck computer ! "<<endl;
    cout<<"Initial board"<<endl;
    print_game_board(v);
    
    while(1){
        ch='a';
        random_row_number=row_interval(number_generator); /* generate random row number in valid interval */
        random_column_number=column_interval(number_generator); /* generate random column number in valid interval */
        for(int i=0; i<random_column_number; ++i)  /* To turn random column number into regarding letter */
            ch++;

        for(int i=0; i<column_count; ++i){
            if(random_column_number==column_count){
                random_column_number=0;
                ch='a';
            }
            
            if(random_computer_move(v,random_row_number,random_column_number,ch)==true) /* If return value is true, it means the move was legal and played */
                break;                                                                  /* Break the loop and make another random move till game is over */
            
            random_column_number+=1;
            ch+=1;
        }        
        
        if(check_game_end(v)==true){ /* End condition */
            cout<<"There is no more legal move, the game is over..."<<endl;
            final_score=find_peg_count(v);
            cout<<"Computer's score is "<<final_score<<" out of "<<initial_peg<<endl;
            break;
        }
    }


}
/* Computer makes random move towards random direction, if there are any legal move, function makes the change on the board and returns true */
/* It tries all possible directions till make a legal move if there are no valid move in choosen random row index, it returns false */
/* This random move algorithm is the fastest among other random computer move algorithms that I've written */
bool random_computer_move(vector<vector<board_element>>&v, int row, int column, char column_letter){
    int random_direction=0;
    bool value=false;
    unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
    mt19937 number_generator(seed);
    uniform_int_distribution<int>direction_interval(0,3);
    random_direction=direction_interval(number_generator);
    for(int i=0; i<4; ++i){       /* At first, check if random movement direction which is generated by number generator is legal or not*/
                                  /* If its not valid try other movement directions for random index */
        if(random_direction==4)
            random_direction=0;
        
        if(random_direction==0){  /* LEFT */
            if(check_valid_move(v,row,column,movement_direction::LEFT)==true){ /* Check if computer's move is legal toward LEFT direction */
                cout<<endl<<"Move : "<<column_letter<<row+1<<"-L\n"<<endl; /* Print move */
                cout<<"---------------------------------"<<endl;
                set_movement(row+1,column_letter,movement_direction::LEFT,v); /* Modify the game board */
                print_game_board(v);                                          /* Print modified game board */
                value=true;
                break;
            
            }
        }
        else if(random_direction==1){/* RIGHT */
       
            if(check_valid_move(v,row,column,movement_direction::RIGHT)==true){
                cout<<endl<<"Move : "<<column_letter<<row+1<<"-R\n"<<endl;
                cout<<"---------------------------------"<<endl;
                set_movement(row+1,column_letter,movement_direction::RIGHT,v);
                print_game_board(v);
                value=true;
                break;
            }
            
        }
        else if(random_direction==2){ /* UP */
     
            
            if(check_valid_move(v,row,column,movement_direction::UP)==true){
                cout<<endl<<"Move : "<<column_letter<<row+1<<"-U\n"<<endl;
                cout<<"---------------------------------"<<endl;
                set_movement(row+1,column_letter,movement_direction::UP,v);
                print_game_board(v);
                value=true;
                break;
            }
            
        }
        else if(random_direction==3){ /* DOWN */

            if(check_valid_move(v,row,column,movement_direction::DOWN)==true){
                cout<<endl<<"Move : "<<column_letter<<row+1<<"-D\n"<<endl;
                cout<<"---------------------------------"<<endl;
                set_movement(row+1,column_letter,movement_direction::DOWN,v);
                print_game_board(v);
                value=true;
                break;
            }
        }
        
             random_direction++;  
    }
    return value;
}


/* This function checks if there are any legal move can be playable on the current game board */
/* If there are no more legal moves, it returns "true" which means the game is over */

bool check_game_end(const vector<vector<board_element>>v){
   int game_end_control=0;

    for(int row=0; row<v.size(); ++row){
        for(int column=0; column<v[row].size(); ++column){
            if(((row-2)>=0) && (check_valid_move(v,row,column,movement_direction::UP)==true)){   /* UP */
                game_end_control=1;
                break;
            }
            if(((row+2)<v.size()) && (check_valid_move(v,row,column,movement_direction::DOWN)==true)){ /* DOWN */
                game_end_control=1;
                break;
            }
            if(((column-2)>=0) && (check_valid_move(v,row,column,movement_direction::LEFT)==true)){ /* LEFT */
                game_end_control=1;
                break;
            }
            if(((column+2)<v[row].size()) && (check_valid_move(v,row,column,movement_direction::RIGHT)==true)){ /* RIGHT */
                game_end_control=1;
                break;
            }
        }
    }
    if(game_end_control==1)
            return false; /* The game is not finished */
        else 
            return true; /* The game is finished */

}
        

/*According to game rules and the move which is played,this function replaces current game board elements with new elements */

void set_movement(int row_index, char column_index, movement_direction direction, vector<vector<board_element>>&v){

    int row=row_index-1;
    int column=0;

    if(column_index<='Z' && column_index>='A')    /* Find the correct row and column index for vector */
        column=column_index-'A';
    else if(column_index<='z' && column_index>='a')
        column=column_index-'a';

    switch(direction){                    /* According to choosen movement direction and row and column index, modify the current game board */
        case movement_direction::LEFT:
            if(check_valid_move(v,row,column,direction)==true){
                v[row][column]=board_element::EMPTY;
                v[row][column-1]=board_element::EMPTY;
                v[row][column-2]=board_element::PEG;
            }
            else
                cout<<" Your move is not legal, please make another move "<<endl; /* Warning */
            
            break;
        case movement_direction::RIGHT:
            if(check_valid_move(v,row,column,direction)==true){
                v[row][column]=board_element::EMPTY;
                v[row][column+1]=board_element::EMPTY;
                v[row][column+2]=board_element::PEG;
            }
            else
                cout<<" Your move is not legal, please make another move "<<endl;
            
            break;
        case movement_direction::UP:
            if(check_valid_move(v,row,column,direction)==true){
                v[row][column]=board_element::EMPTY;
                v[row-1][column]=board_element::EMPTY;
                v[row-2][column]=board_element::PEG;
            }
            else
                cout<<" Your move is not legal, please make another move "<<endl;
            
            break;

        case movement_direction::DOWN:
            if(check_valid_move(v,row,column,direction)==true){
                v[row][column]=board_element::EMPTY;
                v[row+1][column]=board_element::EMPTY;
                v[row+2][column]=board_element::PEG;

            }
            else
                cout<<" Your move is not legal, please make another move "<<endl;
            
            break;
    }

}


/* This function checks if user's move valid can be playable or not */
/* If the move is playable, function returns true */

bool check_valid_move(const vector<vector<board_element>>v, int row, int column, movement_direction direction){

    switch(direction){          
        case movement_direction::UP:    
            if((row-2)>=0 && v[row-1][column]==board_element::PEG && v[row][column]==board_element::PEG)
                if(v[row-2][column]==board_element::EMPTY)
                    return true;
                else
                    return false;
            else
                return false;
            
             break;
        case movement_direction::DOWN:
            if(((row+2)<v.size()) && v[row+1][column]==board_element::PEG && v[row][column]==board_element::PEG)
                if(v[row+2][column]==board_element::EMPTY)
                    return true;
                else
                    return false;
            else
                return false;
            break;
        case movement_direction::LEFT:
            if( ((column-2)>=0) && v[row][column-1]==board_element::PEG && v[row][column]==board_element::PEG)
                if(v[row][column-2]==board_element::EMPTY)
                    return true;
                else
                    return false;
            else
                return false;
            break;
        case movement_direction::RIGHT:
            if( ((column+2)<v[row].size()) && v[row][column+1]==board_element::PEG && v[row][column]==board_element::PEG)
                if(v[row][column+2]==board_element::EMPTY)
                    return true;
                else
                    return false;
            else
                return false;        
        
        default:
            return false;
            break;
                
    }

}

/* This function checks if user's input is valid or not */
/* Column letters and row numbers may change from one game board to another */                                                         
/* In those cases this function is still able to eleminate not exist column letter and row number */
bool movement_input_check(const vector<vector<board_element>>v,vector<char>str){ 
    int row=v.size(); /* which represents last number */                         /* Valid input examples A5-L, g5-R */
    int column=v[0].size(); /* which represents last letter */                                                      
    char ch='a', ch2='A', max_row_num='0';                     
    for(int i=1; i<column; ++i){
        ch+=1;
        ch2+=1;
    }
    for(int i=0; i<row; ++i)
        max_row_num+=1;

    if((str[0]<=ch2 && str[0]>='A') || (str[0]>='a' && str[0]<=ch)){ 
        if(str[1]>='1' && str[1]<=max_row_num){
            if(str[2]=='-'){
                if(str[3]=='R' || str[3]=='L' || str[3]=='U' || str[3]=='D')
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false; 
    }
        else 
            return false;
}

void print_game_board(const vector<vector<board_element>>v){ /* This function draws game board with column letters and row numbers */
    char ch='a';
    int counter=1;
    cout<<"  ";
    for(int i=0; i<v.size(); ++i){
        cout<<ch<<" ";
        ch++;
    }
    cout<<endl;
    for(int i=0; i<v.size(); ++i){
        cout<<counter<<" ";
        for(int j=0; j<v[i].size(); ++j){
            if(v[i][j]==board_element::WALL)
                cout<<" "<<" ";            
            else if(v[i][j]==board_element::PEG)
                cout<<"P"<<" ";
            else if(v[i][j]==board_element::EMPTY)
                cout<<"."<<" ";
        }
        counter++;
        cout<<endl;
    }


}

void print_board(const vector<vector<board_element>>v){ /* This function is written to draw a game board without column letters and row numbers */

    for(int i=0; i<v.size(); ++i){
        for(int j=0; j<v[i].size(); ++j){
            if(v[i][j]==board_element::WALL)
                cout<<" "<<" ";            
            else if(v[i][j]==board_element::PEG)
                cout<<"P"<<" ";
            else if(v[i][j]==board_element::EMPTY)
                cout<<"."<<" ";
        }
        cout<<endl;
    }
}