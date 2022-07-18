#include<iostream>
#include<vector>
#include"pegsolitaire.h"
using namespace std;


namespace SavitcGames{

    PegSolitaire::PegSolitaire( )
        :BoardGame2D( )
    {
        initialize( );
    
    }
    PegSolitaire::PegSolitaire(string typeofGame)
        :BoardGame2D(typeofGame)
    {
        initialize( );
        
    }
    void PegSolitaire::findScore( ) {
        int score_point = 0;

        for(int i = 0; i <Board.size(); i++)
        {
            for(int j = 0; j < Board[i].size( ) ; j++)
                if(Board[i][j].checkElement(GameElements::PEG))
                    score_point++;
        
        }
        BoardGame2D::setScore(score_point);

    }

    
    void PegSolitaire::print( ) const
    {
        char ch='a';
        auto x=0;
        decltype(x) counter=x+1;
        
       
        cout<<"  ";
        
        for(int i=0; i<Board[0].size(); ++i){ /* Column letters */
            cout<<ch<<" ";
            ch++;
        }
        cout<<endl;
        for(int i=0; i<Board.size(); ++i){
            cout<<counter<<" ";
            for(int j=0; j<Board[i].size(); ++j){
                if(Board[i][j].checkElement(GameElements::WALL)==true)
                    cout<<" "<<" ";            
                else if(Board[i][j].checkElement(GameElements::PEG)==true)
                    cout<<"P"<<" ";
                else if(Board[i][j].checkElement(GameElements::EMPTY)==true)
                    cout<<"."<<" ";
            }
            counter++;
            cout<<endl;
        }
    }
    
    /* This function is written to draw a game board without column letters and row numbers */
    
  
    void PegSolitaire::CreateBoard(vector<vector<GameElements>>v){
        int row = 0, column = 0;
        row = v.size();
        column = v[0].size();
        Board.resize(row, vector<Cell>(column)); 
        for(int i=0; i<v.size(); ++i){
            
            for(int j=0; j<v[i].size(); ++j)
            {
                if(v[i][j]==GameElements::EMPTY)
                    Board[i][j].setElement(i,j,GameElements::EMPTY);
                
                
                else if(v[i][j]==GameElements::PEG)
                    Board[i][j].setElement(i,j,GameElements::PEG);
                
                
                else if(v[i][j]==GameElements::WALL)
                    Board[i][j].setElement(i,j,GameElements::WALL);
                
            }
        }
      
    }
   
    void PegSolitaire::playUser(string input){

        int row_index = 0, column_letter = 0, command_check = 0;
        Direction move; 
        column_letter = input[0];
        row_index = input[1]-'0';
        cout<<input[3];
        switch(input[3]){
            case 'L':
                move=Direction::LEFT;
                setMove(row_index, column_letter, move);
                break;
            case 'R':
                move=Direction::RIGHT;
                setMove(row_index, column_letter, move);
                break;
            case 'U':
                move=Direction::UP; 
                setMove(row_index, column_letter, move);
                break;
            case 'D':
                move=Direction::DOWN;
                setMove(row_index, column_letter, move);
                break;
            default:   
                break;
                    
            findScore( );
        }
    }
    void PegSolitaire::playAuto( ){
        
        int column_count=0, row_count=0, random_row_number=0, random_column_number=0;
        bool valid_move=false;
        char ch='a';
        unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
        mt19937 number_generator(seed);
        for(int i=0; i<Board.size(); ++i)  /* First we need to find total row and column count to generate valid random move */
            row_count++;
        
        for(int j=0; j<Board[0].size(); ++j)
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
                        valid_move=true;
                        break;                                                                /* Break the loop and make another random move till game is over */
                    }
                    random_column_number+=1;
                    ch+=1;
                }        
                if( valid_move==true ){
                    findScore( );
                    print( );
                    break;
                }   
        }    
    }
    
    void PegSolitaire::setMove(int row_index, char column_index, Direction move){
    
        int row = row_index-1, column = 0;
        
        if(column_index<='Z' && column_index>='A')    /* Find the correct row and column index for vector */
            column=column_index-'A';
        else if(column_index<='z' && column_index>='a')
            column=column_index-'a';

        switch(move){                    /* According to choosen movement direction and row and column index, modify the current game board */
            case Direction::LEFT:
                if(isValidMove(row,column,Direction::LEFT)==true){
                    Board[row][column].setElement(row, column, GameElements::EMPTY);
                    Board[row][column-1].setElement(row, column-1, GameElements::EMPTY);
                    Board[row][column-2].setElement(row, column-2, GameElements::PEG);
                    print( );
                }
                else
                    cerr<<"Your move is not legal, please make another move "<<endl; /* Warning */
                
                break;
            case Direction::RIGHT:
                if(isValidMove(row,column,Direction::RIGHT)==true){
                
                    Board[row][column].setElement(row, column, GameElements::EMPTY);
                    Board[row][column+1].setElement(row, column+1, GameElements::EMPTY);
                    Board[row][column+2].setElement(row, column+2, GameElements::PEG);
                    print( );
                }
                else
                    cerr<<"Your move is not legal, please make another move "<<endl;
                
                break;
            case Direction::UP:
                if(isValidMove(row,column,Direction::UP)==true){
                
                    Board[row][column].setElement(row, column, GameElements::EMPTY);
                    Board[row-1][column].setElement(row-1, column, GameElements::EMPTY);
                    Board[row-2][column].setElement(row-2, column, GameElements::PEG);
                    print( );
                }
                else
                    cerr<<"Your move is not legal, please make another move "<<endl;
                
                break;

            case Direction::DOWN:
                if(isValidMove(row,column,Direction::DOWN)==true){
                    Board[row][column].setElement(row, column, GameElements::EMPTY);
                    Board[row+1][column].setElement(row+1, column, GameElements::EMPTY);
                    Board[row+2][column].setElement(row+2, column, GameElements::PEG);
                    print( );
                }
                else
                    cerr<<"Your move is not legal, please make another move "<<endl;
                
                break;
        }

    }
    bool PegSolitaire::isRandomMoveValid(int row, int column, char column_letter){
        int random_direction = 0;
        bool value = false;
        unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
        mt19937 number_generator(seed);
        uniform_int_distribution<int>direction_interval(0,3);
        random_direction = direction_interval(number_generator);
        for(int i=0; i<4; ++i){       /* At first, check if random movement direction which is generated by number generator is legal or not*/
                                    /* If its not valid try other movement directions for random index */
            if(random_direction==4)
                random_direction=0;
            
            if(random_direction==0){  /* LEFT */         /* Increment row because setElement function will decrement it */
                if(isValidMove(row,column,Direction::LEFT)==true){ /* Check if computer's move is legal toward LEFT direction */
                    
                    cout << "\x1b[2J"; 
                    cout << "\033[0;0H"; 
                    cout << endl ;
                    cout<<endl<<"Move : "<<column_letter<<row+1<<"-L\n"<<endl; /* Print move */
                    cout<<"---------------------------------"<<endl;
                    Board[row][column].setElement(row,column_letter, GameElements::EMPTY); /* Modify the game board */
                    Board[row][column-1].setElement(row, column-1, GameElements::EMPTY);
                    Board[row][column-2].setElement(row, column-2, GameElements::PEG);
                 
                    
                    value=true;
                    break;
                }
            }
            else if(random_direction==1){/* RIGHT */
        
                if(isValidMove(row, column, Direction::RIGHT)==true){
                    cout << "\x1b[2J"; 
                    cout << "\033[0;0H"; 
                    cout << endl ;
                    cout<<endl<<"Move : "<<column_letter<<row+1<<"-R\n"<<endl;
                    cout<<"---------------------------------"<<endl;
                    Board[row][column].setElement(row, column, GameElements::EMPTY);
                    Board[row][column+1].setElement(row, column+1, GameElements::EMPTY);
                    Board[row][column+2].setElement(row, column+2, GameElements::PEG);
                    value=true;
                    break;
                }
                
            }
            else if(random_direction==2){ /* UP */
        
                if(isValidMove(row, column, Direction::UP)==true){
                    cout << "\x1b[2J"; 
                    cout << "\033[0;0H"; 
                    cout << endl; 
                    cout<<endl<<"Move : "<<column_letter<<row+1<<"-U\n"<<endl;
                    cout<<"---------------------------------"<<endl;
                    Board[row][column].setElement(row, column, GameElements::EMPTY);
                    Board[row-1][column].setElement(row-1, column, GameElements::EMPTY);
                    Board[row-2][column].setElement(row-2, column, GameElements::PEG);
                    value=true;
                    break;
                }
                
            }
            else if(random_direction==3){ /* DOWN */

                if(isValidMove(row, column, Direction::DOWN)==true){
                    cout << "\x1b[2J"; 
                    cout << "\033[0;0H"; 
                    cout << endl ;
                    cout<<endl<<"Move : "<<column_letter<<row+1<<"-D\n"<<endl;
                    cout<<"---------------------------------"<<endl;
                    Board[row][column].setElement(row, column, GameElements::EMPTY);
                    Board[row+1][column].setElement(row+1, column, GameElements::EMPTY);
                    Board[row+2][column].setElement(row+2, column, GameElements::PEG);
                    value=true;
                    break;
                }
            }
            
                random_direction++;  
        }
        return value;
    }

    bool PegSolitaire::endGame( ) const{
        bool game_end_control=false;

        for(int row=0; row<Board.size(); ++row){
            for(int column=0; column<Board[row].size(); ++column){
                if(((row-2)>=0) && (isValidMove(row,column,Direction::UP)==true)){   /* UP */
                    game_end_control=true;
                    break;
                }
                if(((row+2)<Board.size( )) && (isValidMove(row,column,Direction::DOWN)==true)){ /* DOWN */
                    game_end_control=true;
                    break;
                }
                if(((column-2)>=0) && (isValidMove(row,column, Direction::LEFT)==true)){ /* LEFT */
                    game_end_control=true;
                    break;
                }
                if(((column+2)<Board[row].size()) && (isValidMove(row,column, Direction::RIGHT)==true)){ /* RIGHT */
                    game_end_control=true;
                    break;
                }
            }
        }
        
        if(game_end_control==true)
            return false; /* The game is not finished */
        else {
            
            return true; /* The game is finished */
        }
    }
    
    bool PegSolitaire::isValidMove(int row, int column, Direction Move) const{ /* This function checks whether given move is valid or not */

        switch(Move){          
            
            case Direction::UP:
                if((row-2)>=0 && Board[row-1][column].checkElement(GameElements::PEG) && Board[row][column].checkElement(GameElements::PEG))
                    if(Board[row-2][column].checkElement(GameElements::EMPTY))
                        return true;
                    else
                        return false;
                else
                    return false;
                
                break;
            
            case Direction::DOWN:
                if(((row+2)<Board.size()) && Board[row+1][column].checkElement(GameElements::PEG) && Board[row][column].checkElement(GameElements::PEG))
                    if(Board[row+2][column].checkElement(GameElements::EMPTY))
                        return true;
                    else
                        return false;
                else
                    return false;
                break;
            
            case Direction::LEFT:
                if( ((column-2)>=0) && Board[row][column-1].checkElement(GameElements::PEG) && Board[row][column].checkElement(GameElements::PEG))
                    if(Board[row][column-2].checkElement(GameElements::EMPTY))
                        return true;
                    else
                        return false;
                else
                    return false;
                break;
            case Direction::RIGHT:
                if( ((column+2)<Board[row].size()) && Board[row][column+1].checkElement(GameElements::PEG) && Board[row][column].checkElement(GameElements::PEG))
                    if(Board[row][column+2].checkElement(GameElements::EMPTY))
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
    bool PegSolitaire::isValidInput(string input) const
    {

        int row=Board.size(); /* which represents last number */                         /* Valid input examples A5-L, g5-R */
        int column=Board[0].size(); /* which represents last letter */                                                      
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

    void PegSolitaire::initialize( ){ /* All the game boards */
        
        vector<vector<GameElements>>game_type_2{
            {GameElements::WALL,GameElements::WALL,GameElements::WALL,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::WALL,GameElements::WALL,GameElements::WALL},
            {GameElements::WALL,GameElements::WALL,GameElements::WALL,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::WALL,GameElements::WALL,GameElements::WALL},
            {GameElements::WALL,GameElements::WALL,GameElements::WALL,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::WALL,GameElements::WALL,GameElements::WALL},
            {GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG},
            {GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::EMPTY,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG},
            {GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::PEG},
            {GameElements::WALL,GameElements::WALL,GameElements::WALL,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::WALL,GameElements::WALL,GameElements::WALL},
            {GameElements::WALL,GameElements::WALL,GameElements::WALL,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::WALL,GameElements::WALL,GameElements::WALL},
            {GameElements::WALL,GameElements::WALL,GameElements::WALL,GameElements::PEG,GameElements::PEG,GameElements::PEG,GameElements::WALL,GameElements::WALL,GameElements::WALL}
        };
    
        CreateBoard(game_type_2);        

    }
    
    PegSolitaire::Cell::Cell() : row(0), column(0), element(GameElements::WALL)
    { /* Intentionally Empty */ }


    void PegSolitaire::Cell::setElement(int row_index,char column_index, GameElements element_type)
    {
        row = row_index;
        column = column_index; 
        element = element_type;
    }
    bool PegSolitaire::Cell::checkElement(GameElements elm) const
    {
        if(elm==element)
            
            return true;
        
        else
            return false;
    }

}