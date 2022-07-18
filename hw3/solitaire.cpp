#include"solitaire.h"

/* Constructors */


PegSolitaire::PegSolitaire(int choosen_board, int type_of_game) :game_type(type_of_game), board_type(choosen_board), isBoardInitialized(true)
{SetGameBoard(board_type);}



PegSolitaire::PegSolitaire(int choosen_board) :board_type(choosen_board), game_type(0), isBoardInitialized(true)
{SetGameBoard(board_type);}

PegSolitaire::PegSolitaire() :board_type(0), game_type(0), isBoardInitialized(false)
{/*Intentionally Empty */}


int PegSolitaire::TotalNumberOfPegs=0; /* Static value initalazation */


int PegSolitaire::sumAllPegs(int empty_cells, int total_pegs){
    bool isActiveGame = false ;
    
    if(empty_cells > 1)
        isActiveGame = true;
    
    if(isActiveGame == true)
        TotalNumberOfPegs += total_pegs;
    else
        TotalNumberOfPegs += 0;
    
    return TotalNumberOfPegs;
}
void PegSolitaire::setToZero(){ 
    TotalNumberOfPegs = 0;
}
int PegSolitaire::getTotalPegs(){
    
    return TotalNumberOfPegs;
}

void PegSolitaire::SetGameType(int type_of_game){ 


    if(game_type<1 || game_type>2){
        cout<<"1-)Human game: ";
        cout<<endl<<"2-)Computer game: ";
        cout<<endl<<"Choose the type of your game : ";
        cin>>game_type;        
        cin.ignore();
        cin.clear();    
    }
    else
        game_type = type_of_game;

}

void PegSolitaire::Start(){ 
    
    if(isBoardInitialized==false) /* Check whether this is the first game for this Class */
        SetGameBoard(board_type);
    
    if(game_type<1 || game_type>2) /* Check if game type is valid before game is started */
        SetGameType(game_type);
    
    
    cout<<"Number of pegs: "<<number_of_pegs()<<endl;
    cout<<"Number of empty cells: "<<number_of_empty_cells()<<endl;
    cout<<"Number of taken pegs out from the board: "<<number_of_taken_pegs()<<endl<<endl;

    if(game_type==1)
        HumanGame();
    
    else if(game_type==2)
        playGame();    

}


void PegSolitaire::CreateBoard(vector<vector<board_element>>v){ /* Create a new board */
    int row, column;
   
    row = v.size();
    column = v[0].size();
    
    game.clear(); /* Just in case ERASE the old board */
    game.resize(row, vector<Cell>(column)); 
    
    
    for(int i=0; i<v.size(); ++i){
        for(int j=0; j<v[i].size(); ++j)
        {
            if(v[i][j]==board_element::EMPTY)
                game[i][j].setElement(i,j,board_element::EMPTY);
            
            
            else if(v[i][j]==board_element::PEG)
                game[i][j].setElement(i,j,board_element::PEG);
            
            
            else if(v[i][j]==board_element::WALL)
                game[i][j].setElement(i,j,board_element::WALL);
            
        }
    }
    
   

}


bool PegSolitaire::isValidMove(int row, int column, Direction Move) const{ /* This function checks whether given move is valid or not */

    switch(Move){          
        
        case Direction::UP:
            if((row-2)>=0 && game[row-1][column].checkElement(board_element::PEG) && game[row][column].checkElement(board_element::PEG))
                if(game[row-2][column].checkElement(board_element::EMPTY))
                    return true;
                else
                    return false;
            else
                return false;
            
             break;
        
        case Direction::DOWN:
            if(((row+2)<game.size()) && game[row+1][column].checkElement(board_element::PEG) && game[row][column].checkElement(board_element::PEG))
                if(game[row+2][column].checkElement(board_element::EMPTY))
                    return true;
                else
                    return false;
            else
                return false;
            break;
        
        case Direction::LEFT:
            if( ((column-2)>=0) && game[row][column-1].checkElement(board_element::PEG) && game[row][column].checkElement(board_element::PEG))
                if(game[row][column-2].checkElement(board_element::EMPTY))
                    return true;
                else
                    return false;
            else
                return false;
            break;
        case Direction::RIGHT:
            if( ((column+2)<game[row].size()) && game[row][column+1].checkElement(board_element::PEG) && game[row][column].checkElement(board_element::PEG))
                if(game[row][column + 2].checkElement(board_element::EMPTY))
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

bool PegSolitaire::isGameOver() const{ // Checks if game is ended
 bool game_end_control=false;

    for(int row=0; row<game.size(); ++row){
        for(int column=0; column<game[row].size(); ++column){
            if(((row-2)>=0) && (isValidMove(row,column,Direction::UP)==true)){   /* UP */
                game_end_control=true;
                break;
            }
            if(((row+2)<game.size()) && (isValidMove(row,column,Direction::DOWN)==true)){ /* DOWN */
                game_end_control=true;
                break;
            }
            if(((column-2)>=0) && (isValidMove(row,column, Direction::LEFT)==true)){ /* LEFT */
                game_end_control=true;
                break;
            }
            if(((column+2)<game[row].size()) && (isValidMove(row,column, Direction::RIGHT)==true)){ /* RIGHT */
                game_end_control=true;
                break;
            }
        }
    }
    
     if(game_end_control==true)
        return false; /* The game is not finished */
    else 
        return true; /* The game is finished */
        
        
}

bool PegSolitaire::isRandomMoveValid(int row, int column, char column_letter){
    
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
        
        if(random_direction==0){  /* LEFT */         /* Increment row because setElement function will decrement it */
            if(isValidMove(row,column,Direction::LEFT)==true){ /* Check if computer's move is legal toward LEFT direction */
                cout<<endl<<"Move : "<<column_letter<<row+1<<"-L\n"<<endl; /* Print move */
                cout<<"---------------------------------"<<endl;
                game[row][column].setElement(row,column_letter, board_element::EMPTY); /* Modify the game board */
                game[row][column-1].setElement(row, column-1, board_element::EMPTY);
                game[row][column-2].setElement(row, column-2, board_element::PEG);
                value=true;
                break;
            }
        }
        else if(random_direction==1){/* RIGHT */
       
            if(isValidMove(row, column, Direction::RIGHT)==true){
                cout<<endl<<"Move : "<<column_letter<<row+1<<"-R\n"<<endl;
                cout<<"---------------------------------"<<endl;
                game[row][column].setElement(row, column, board_element::EMPTY);
                game[row][column+1].setElement(row, column+1, board_element::EMPTY);
                game[row][column+2].setElement(row, column+2, board_element::PEG);
                value=true;
                break;
            }
            
        }
        else if(random_direction==2){ /* UP */
     
            if(isValidMove(row, column, Direction::UP)==true){
                cout<<endl<<"Move : "<<column_letter<<row+1<<"-U\n"<<endl;
                cout<<"---------------------------------"<<endl;
                game[row][column].setElement(row, column, board_element::EMPTY);
                game[row-1][column].setElement(row-1, column, board_element::EMPTY);
                game[row-2][column].setElement(row-2, column, board_element::PEG);
                value=true;
                break;
            }
            
        }
        else if(random_direction==3){ /* DOWN */

            if(isValidMove(row, column, Direction::DOWN)==true){
                cout<<endl<<"Move : "<<column_letter<<row+1<<"-D\n"<<endl;
                cout<<"---------------------------------"<<endl;
                game[row][column].setElement(row, column, board_element::EMPTY);
                game[row+1][column].setElement(row+1, column, board_element::EMPTY);
                game[row+2][column].setElement(row+2, column, board_element::PEG);
                value=true;
                break;
            }
        }
        
             random_direction++;  
    }
    return value;
}

bool PegSolitaire::isValidInput(string input) const
{

    int row=game.size(); /* which represents last number */                         /* Valid input examples A5-L, g5-R */
    int column=game[0].size(); /* which represents last letter */                                                      
    char ch='a', ch2='A', max_row_num='0';                     
    bool return_value=false;
    
    for(int i=1; i<column; ++i){
        ch+=1;
        ch2+=1;
    }
    for(int i=0; i<row; ++i)
        max_row_num+=1;

    if((input[0]<=ch2 && input[0]>='A') || (input[0]>='a' && input[0]<=ch)){ 
        if(input[1]>='1' && input[1]<=max_row_num){
            if(input[2]=='-'){
                if(input[3]=='R' || input[3]=='L' || input[3]=='U' || input[3]=='D')
                    return_value = true;
                else
                    return_value = false;
            }
            else
                return_value = false;
        }
        else
            return_value = false; 
    }
        else 
            return_value = false;

    if(return_value==true)
        return true;
    else{
        cerr<<"Your input is not valid !"<<endl;
        return false;
    }
}
 bool PegSolitaire::CompareGames(const PegSolitaire& game2) const{ /* If parameter class has more pegs return false, otherwise return true */ 

    return (number_of_pegs()> game2.number_of_pegs());

 }

inline int PegSolitaire::getGameType() const{

    return game_type;
}

inline int PegSolitaire::CheckCommand(string command) const{ /* Returns 0 for invalid, 1 for LOAD , 2 for SAVE, 3 for EXIT commands */
    
    string first_part, second_part;
    int command_type=0;  

  
    for(int i=0; i<4; ++i) /* For all commands (LOAD/SAVE/EXIT) we should check first 4 letter  */
        first_part.push_back(command.at(i)); 

    for(int i=5; i <command.size(); ++i) /* Valid move input is LOAD FILE.TXT so that we removed first five element from size */
        second_part.push_back(command.at(i));

    if( first_part.compare("LOAD")==0 || first_part.compare("load")==0 ){
        
        ifstream load_file(second_part);
        if(load_file.is_open())
            command_type = 1;
        
        else{
            cerr<<"File does not exist !"<<endl;
            command_type = 0;    
        }
        load_file.close();
    }
    else if( first_part.compare("SAVE")==0 || first_part.compare("save")==0 )
        command_type = 2; 

    else if( first_part.compare("EXIT")==0 || first_part.compare("exit")==0 )
        command_type = 3;
    

    return command_type;
}


void PegSolitaire::read_from_file(string input){ /* Read Data from file and create a new board */
    string file_name, str;
    int row = 0, row_counter=0, column = 0, column_counter =0, counter = 0;
    char game_type;
    vector<vector<board_element>>vect;
    
    for(int i=5; i <input.size(); ++i) 
        file_name.push_back(input.at(i));

    ifstream load_file(file_name);        
    
    if(load_file.is_open()){
        
        while(getline(load_file,str)){          + 

            counter = 0;
            if(str[0]=='C' || str[0]=='H'){
                game_type = str[0];
                break;
            }

            for(int i=0; i<str.size(); ++i){
                
                if(static_cast<int>(str[i])==13) /* Remove carriage return character */
                    counter=counter-1;
                
                counter++;
            }

            if(counter>=column)
                column=counter;

            row++;
            str.clear();
        }    
        
        load_file.close();
    }
    
    ifstream read_file(file_name);

    if(read_file.is_open()){
        
        vect.resize(row, vector<board_element>(column));
        row_counter=0;
    
        while(getline(read_file,str)){
            
            column_counter = 0;
            if(row_counter==row)
                break;
            
            for(int j = 0; str[j]!='\0' ; j++, column_counter+=1){
                
                if(static_cast<int>(str[j])==13) /* REMOVE Carriage return character */
                    break;
                
                if(str[j]=='P')
                    vect[row_counter][j]=board_element::PEG;
                
                else if(str[j]==' ')
                    vect[row_counter][j]=board_element::WALL;
                
                else if(str[j]=='.')
                    vect[row_counter][j]=board_element::EMPTY;
                
            }
            
            for(int j = column_counter; j < column ; ++j)
                vect[row_counter][j]=board_element::WALL; 
            
            row_counter++;
            str.clear();
        }
        
        cout<<"Game has loaded ! "<<endl;
        read_file.close();
        
        if(game_type=='H')
            SetGameType(1);
        else if(game_type=='C')
            SetGameType(2);

        CreateBoard(vect);
        
    }
    
}


void PegSolitaire::write_to_file(string input_file) const{ /* SAVE Game's data to file */

    string file_name;
    for(int i = 5; i<input_file.size(); ++i)
        file_name.push_back(input_file.at(i));

    ofstream save_file(file_name);
    if(save_file.is_open()){
        for(int i=0; i <game.size(); ++i){
            for(int j=0; j < game[i].size(); ++j){
                if(game[i][j].checkElement(board_element::PEG)==true)
                    save_file<<"P";
                else if(game[i][j].checkElement(board_element::WALL)==true)
                    save_file<<" ";
                else if(game[i][j].checkElement(board_element::EMPTY)==true)
                    save_file<<".";
            }
            save_file<<"\n";
        }
        if(getGameType()==1)
            save_file<<"H";   /* Write game type */
        else if(getGameType()==2)
            save_file<<"C";


        cout<<"Curren game is saved to "<<file_name<<" file !"<<endl;
        save_file.close();
    }
    else
        cerr<<"File could not be created !"<<endl;
}

void PegSolitaire::HumanGame(){ /* User Game function */
    string input;
    int row_index = 0, column_letter = 0, command_check = 0;
    Direction move;
    cout<<"Human Game"<<endl;
    cout<<endl<<"To Load from file type LOAD FILE.TXT"<<"\n"<<"To Write/Save to any file type: SAVE FILE.TXT"<<endl;
    cout<<"To go back to main screen type :EXIT or exit "<<endl<<endl;
    display_game();  
    while(1){
          
        printf("Please make a move(or type command):");
        getline(cin,input);
        
        if(input!="" && input.size()>=4) /* Remove enter input, control string to avoid segment error*/
            command_check = CheckCommand(input);
        
        if(command_check==1){ /* LOAD command */
            
            read_from_file(input);
            Start(); /* Start again */
            break;
        }
        else if(command_check==2) /* SAVE command */
            write_to_file(input);
        else if(command_check==3) /* Exit command */
            break;
      
        else if(isValidInput(input)==true){
            column_letter = input[0];
            row_index = input[1]-'0';
            switch(input[3]){
                case 'L':
                    move=Direction::LEFT;
                    break;
                case 'R':
                    move=Direction::RIGHT;
                    break;
                case 'U':
                    move=Direction::UP; 
                    break;
                case 'D':
                    move=Direction::DOWN;
                    break;
                default:   
                    break;
            }
            
            play(row_index, column_letter, move);
        }
        
       if(isGameOver()==true){
            cout<<"Game is over !"<<endl;
            break;
       }
        command_check = 0;

    }

}

void PegSolitaire::playGame(){ /* Computer Play function */

    string input;
    int command_check=0;
    cout<<"Computer Game:"<<endl<<endl;
    
    cout<<endl<<"To Load from file type LOAD FILE.TXT"<<"\n"<<"To Write/Save to any file type: SAVE FILE.TXT"<<endl;
    cout<<"To go back to main screen type :EXIT or exit "<<endl<<endl;
    display_game();
    

    while(1){
        cout<<"Please press ENTER to make random move or use LOAD FILE.TXT/SAVE FILE.TXT/EXIT commands: ";
        getline(cin,input);
        
        if(input!="" && input.size()>=4) /* Remove enter input, control string to avoid segment error */
            command_check = CheckCommand(input);
        
        if(command_check==1){ /* LOAD command */
            read_from_file(input);
            Start();
            break;
        }
        else if(command_check==2) /* SAVE command */
            write_to_file(input);
        
        else if(command_check==3) /* Exit command */
            break;
        
        else if(input==""){
            play();
            display_game();
        }
        
        if(isGameOver()==true){
            cout<<"Game is over !";        
            break;
        }
        command_check = 0;
    }

}

void PegSolitaire::play(int row_index, char column_index, Direction Move){ /* User play function */
    
    int row = row_index-1, column = 0;
    

    if(column_index<='Z' && column_index>='A')    /* Find the correct row and column index for vector */
        column=column_index-'A';
    else if(column_index<='z' && column_index>='a')
        column=column_index-'a';


    switch(Move){                    /* According to choosen movement direction and row and column index, modify the current game board */
        case Direction::LEFT:
            if(isValidMove(row,column,Direction::LEFT)==true){
                game[row][column].setElement(row, column, board_element::EMPTY);
                game[row][column-1].setElement(row, column-1, board_element::EMPTY);
                game[row][column-2].setElement(row, column-2, board_element::PEG);
                display_game();
            }
            else
                cerr<<"Your move is not legal, please make another move "<<endl; /* Warning */
            
            break;
        case Direction::RIGHT:
            if(isValidMove(row,column,Direction::RIGHT)==true){
               
                game[row][column].setElement(row, column, board_element::EMPTY);
                game[row][column+1].setElement(row, column+1, board_element::EMPTY);
                game[row][column+2].setElement(row, column+2, board_element::PEG);
                display_game();
            }
            else
                cerr<<"Your move is not legal, please make another move "<<endl;
            
            break;
        case Direction::UP:
            if(isValidMove(row,column,Direction::UP)==true){
               
                game[row][column].setElement(row, column, board_element::EMPTY);
                game[row-1][column].setElement(row-1, column, board_element::EMPTY);
                game[row-2][column].setElement(row-2, column, board_element::PEG);
                display_game();
            }
            else
                cerr<<"Your move is not legal, please make another move "<<endl;
            
            break;

        case Direction::DOWN:
            if(isValidMove(row,column,Direction::DOWN)==true){
                game[row][column].setElement(row, column, board_element::EMPTY);
                game[row+1][column].setElement(row+1, column, board_element::EMPTY);
                game[row+2][column].setElement(row+2, column, board_element::PEG);
                display_game();
            }
            else
                cerr<<"Your move is not legal, please make another move "<<endl;
            
            break;
    }
}

void PegSolitaire::play(){ /* play function for single step computer move */
    
    int column_count=0, row_count=0, random_row_number=0, random_column_number=0;
    bool valid_move=false;
    char ch='a';
    unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
    mt19937 number_generator(seed);
    for(int i=0; i<game.size(); ++i)  /* First we need to find total row and column count to generate valid random move */
        row_count++;
    
    for(int j=0; j<game[0].size(); ++j)
        column_count++;
    
    uniform_int_distribution<int>row_interval(0, row_count-1);   /*   Determination of valid random number intervals for both cases */
    uniform_int_distribution<int>column_interval(0, column_count-1);
    
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
                    
                if(isRandomMoveValid(random_row_number,random_column_number,ch)==true){ /* If return value is true, it means the move was legal and played */
                    valid_move = true;
                    break;                                                                /* Break the loop and make another random move till game is over */
                }
                random_column_number+=1;
                ch+=1;
            }        
            if(valid_move==true || isGameOver()==true)
                break;
                
    }
}


inline int PegSolitaire::number_of_pegs() const{ /* Returns current pegs count on game board */
    int current_peg_count = 0;
    
    for(int i=0; i<game.size(); ++i){
        for(int j=0; j<game[i].size(); ++j)
            if(game[i][j].checkElement(board_element::PEG)==true)
                current_peg_count++;
    }  

    return current_peg_count;
}

inline int PegSolitaire::number_of_empty_cells() const{ /* Returns current number of empty cells  on game board */
    int empty_cell_count = 0;    

    for(int i=0; i<game.size(); ++i){
        for(int j=0; j<game[i].size(); ++j)
            if(game[i][j].checkElement(board_element::EMPTY)==true)
                empty_cell_count++;
    }  
    return empty_cell_count;
}

inline int PegSolitaire::number_of_taken_pegs() const{ /* Returns current number of taken pegs  from game board */
    
    int number_of_taken = number_of_empty_cells() - 1;
    return number_of_taken;

}

void PegSolitaire::display_object_info() const{ /* Show object's informations */
int emptyCount = number_of_empty_cells();
int pegsCount = number_of_pegs();
    
    if(game_type==1)
        cout<<"   Game Type: Human game"<<endl;
    else if(game_type==2)
        cout<<"   Game Type: Computer game"<<endl;
    else
        cout<<"   Game type is not choosen "<<endl;

    
    if(board_type>0 && board_type<6){
        cout<<"   Current Game Board: "<<endl;
        display_game();
        sumAllPegs(emptyCount , pegsCount);
    }
    else
        cout<<"   Game Board is not choosen "<<endl;

    if(isGameOver()==true && isBoardInitialized==true)
        cout<<"   Game is Over ";
    cout<<endl<<"-----------------------"<<endl;

}

void PegSolitaire::display_game () const{ /* Draw Board */
    char ch='a';
    auto x=0;
    decltype(x) counter=x+1;
    
    cout<<"  ";
    
    for(int i=0; i<game[0].size(); ++i){ /* Column letters */
        cout<<ch<<" ";
        ch++;
    }
    cout<<endl;
    for(int i=0; i<game.size(); ++i){
        cout<<counter<<" ";
        for(int j=0; j<game[i].size(); ++j){
            if(game[i][j].checkElement(board_element::WALL)==true)
                cout<<" "<<" ";            
            else if(game[i][j].checkElement(board_element::PEG)==true)
                cout<<"P"<<" ";
            else if(game[i][j].checkElement(board_element::EMPTY)==true)
                cout<<"."<<" ";
        }
        counter++;
        cout<<endl;
    }

}

void PegSolitaire::print_board(const vector<vector<board_element>>v) const{ /* This function is written to draw a game board without column letters and row numbers */

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




PegSolitaire::Cell::Cell() : row(0), column(0), element(board_element::WALL)
{ /* Intentionally Empty */ }


void PegSolitaire::Cell::setElement(int row_index,char column_index,board_element element_type)
{
    row=row_index;
    column=column_index; 
    element=element_type;
}
bool PegSolitaire::Cell::checkElement(board_element elm) const
{
    if(elm==element)
        
        return true;
    
    else
        return false;
}


void PegSolitaire::SetGameBoard(int board_index){
    string str;
    int choose_board = 0;
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
    
    
    if(board_index<1 || board_index>5){
        cout<<"1-)"<<endl;
        print_board(game_type_1);
        cout<<"2-)"<<endl;
        print_board(game_type_2);
        cout<<"3-)"<<endl;
        print_board(game_type_3);
        cout<<"4-)"<<endl;
        print_board(game_type_4);
        cout<<"5-)"<<endl;
        print_board(game_type_5);
        cout<<endl;
        
        cout<<"Please choose a game board:";
        cin>>choose_board;
        while(1){
            if(choose_board>5 || choose_board<1){                /* Check user's input */
                cerr<<"This operation does not exist !"<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                cout<<"Please choose a game board:";
                cin>>choose_board;
            }
            else
                break;
        }     
        isBoardInitialized = true;
        board_type = choose_board;
    }



    switch(board_type){ /* Create Board */
        case 1:
            CreateBoard(game_type_1);
            break;
        case 2:
            CreateBoard(game_type_2);
            break;
        case 3:
            CreateBoard(game_type_3);
            break;
        case 4:
            CreateBoard(game_type_4);
            break;
        case 5:
            CreateBoard(game_type_5);
            break;
        
        default:
            break;

    }
}




