#include"EightPuzzle.h"

using namespace std;


namespace SavitcGames{

    EightPuzzle::EightPuzzle( )
        :BoardGame2D( )
    {
        Board = new int*[3];
        for( int i = 0 ; i < 3 ; i++)
            Board[i] = new int[3];      
        
        initialize( ); 
 
        
    
    }
    EightPuzzle::EightPuzzle(string GameType)
        :BoardGame2D(GameType)

    {
        
        Board = new int*[3];
        for( int i = 0 ; i < 3 ; i++)
            Board[i] = new int[3];

        initialize( );
        
    }
    EightPuzzle::EightPuzzle(const EightPuzzle& Obj)
    {
        setGameType(Obj.getGameType());
        
        Board = new int*[3];
        for(int i = 0; i < 3; i++)
            Board[i] = new int[3];
        for(int i = 0 ; i < 3; i++)
            for(int j = 0; j < 3; j++)
                Board[i][j] = Obj.Board[i][j];

    }
    EightPuzzle& EightPuzzle::operator=(const EightPuzzle& Obj)
    {
        
        setGameType(Obj.getGameType());
        
        for(int i = 0 ; i < 3; i++)
            for( int j = 0; j < 3; j++)
                Board[i][j] = Obj.Board[i][j];

        return *this;
    }
    
     EightPuzzle::~EightPuzzle( ){

         for(int i = 0; i < 3; i++)
            delete[]Board[i];

        delete[] Board;

     }
    
    void EightPuzzle::initialize( ){
        createBoard( );
        
        while(isSolvable( ) != true)
            createBoard( );
        
    }

    void EightPuzzle::createBoard( )
    { 
        char empty[]="\0";
        int counter = 0 ,  element = 0, random_index = 0, k = 0;
        
        int set_array[9];   /* In first, define a 1D array to keep our generated numbers 1 to (N*N-1) */
        unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()); 
        mt19937 number_generator(seed);
        
        
        for(k = 0 ; k < 8 ; k++) /* Generate all the numbers 1 to (N*N-1) and keep them in 1D array*/
            set_array[k] = k + 1 ;
           
        
        set_array[8] = 0; /* Assign blank space as an element of our game matrix */
    
        uniform_int_distribution<int>random_index_creator(0, 8);  
        
        
        for (int i = 0; i < 9; i++) {    /* I used this block to randomize all the generated numbers 1 to (N*N-1) without repetition of numbers*/
            element = set_array[i];              
            random_index = random_index_creator(number_generator);
            set_array[i] = set_array[random_index];     
            set_array[random_index] = element;   
        }                              

        
        for(int i = 0; i < 3; i++){            
            
            for(int j = 0; j < 3; j++ ){         
                Board[i][j] = set_array[counter]; 
                counter++;
            }
        
        }

    }
    
    bool EightPuzzle::isValidInput(string input) const{
        
        int row = 3;
        int column = 3; /* which represents last letter */                                                      
        char ch='a', ch2='A', max_row_num='0';                     
        bool return_value=false;
        
        for(int i=1; i<column; ++i){
            ch+=1;
            ch2+=1;
        }
        for(int i=0; i<row; ++i)
            max_row_num+=1;

        if( ( input[0]<=ch2 && input[0]>='A' ) || ( input[0]>='a' && input[0]<=ch ) ){ 
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
    
    bool EightPuzzle::isSolvable( )const{
        
        int inversion_count=0, empty_position, k=0; 
        int array[9]; 
        
        for(int i =0; i < 3; i++) /* Copy 2D array's elements into 1D (N*N) array */ 
            for(int j = 0; j < 3; j++){
                array[k]=Board[i][j];
                k++;
            }

        for (int i = 0 ; i < 8 ; i++)     /* Finding the inversion count */
                for (int j = i + 1 ; j < 9 ; j++)
                    if (array[j] && array[i] && array[i] > array[j])
                        inversion_count++;
                
            

        if(9 % 2 != 0) /* If N is odd and inversion count is even it means that puzzle solveable  */
            if( inversion_count % 2==0)
                return 1;
            else
                return 0; 
        else if(9 % 2==0){      /* If N is even there are two possibility */
            for (int i = 2 ; i >= 0; i--)     /* From bottom to top we need to find blank space's position */
                for (int j = 2; j >= 0; j--)
                    if ( Board[i][j] == 0)
                        empty_position= 3 - i;
            
            if( empty_position % 2 != 0) /* If row count of blank space from the bottom is an odd and inversion count is even it means that puzzle is solveable*/
                if(inversion_count % 2 == 0)
                    return true;
                else
                    return false;
            else if(empty_position % 2 == 0)/*If row count of blank space from the bottom is even and inversion count is odd it means that puzzle is solveable*/
            if( inversion_count %2 != 0)
                    return true;
                else
                    return false;
        }

    }


    void EightPuzzle::printHorizantonal() const{       
        for(int i =0 ; i < 25; i++)
            cout<<("-");
    }

    
    void EightPuzzle::print( ) const{
        string empty =" ";
        
        cout << "\x1b[2J"; 
        cout << "\033[0;0H"; 
        cout << endl << endl;
        
        cout<<"    a    "<<"   b    "<<"   c   "<<endl;
        cout<<" ";
        printHorizantonal( );
        cout<<endl;
        for(int i = 0 ; i < 3 ; i++ ){
            cout<<i+1;
            for(int j = 0; j < 3; j++){
                if(Board[i][j]==0)
                    cout<<"|   "<<empty<<"   ";
                else
                    cout<<"|   "<<Board[i][j]<<"   ";
            
            }
            cout<<"|";
            
            cout<<endl;
            cout<<" ";
            printHorizantonal( );
            cout<<endl;
        }
    
    }
    
    void EightPuzzle:: playUser(string move){
        
        char direction = move[3];
        int row = move[1] - '1';
        int column = 0;
        
        if( move[0]<='Z' && move[0]>='A')
            column = move[0] - 'A';
        else if( move[0]<='z' && move[0]>='a' )
            column = move[0] - 'a';
        
        
        switch(direction){         
            case 'R':                     
                setMove(Direction::RIGHT,row,column);
                break;
            case 'L':
                setMove(Direction::LEFT,row,column);
                break;
            case 'U':
                setMove(Direction::UP,row,column);
                break;
            case 'D': 
                setMove(Direction::DOWN,row,column);
                break;
        
            default:      
                break;
        }

    }
    void EightPuzzle::setMove(Direction direction, int row, int column){
        int i = 0, j = 0, empty_index; 
        bool valid_move = false;
        int copyArray[3][3];   /*Define a copy array to make slide movements more effectively */

        for(i = 0 ; i < 3; i++)          /* Equalize matrices each other*/
            for(j = 0; j < 3; j++)
                copyArray[i][j] = Board[i][j]; 

        switch(direction){                
            case Direction::RIGHT:                              /* RIGHT DIRECTION */
                for(i = column + 1; i <= 2; i++)           /* At first, check given movement is valid or not  */
                    if(Board[row][i] == 0){
                        empty_index = i;              /*If the given movement is valid, then take the index of blank space */
                        valid_move = true ;               
                    }   
                if(valid_move == true){
                    Board[row][column] = copyArray[row][empty_index];/* Change the input's position with blank space's position */
                    for( i = column ; i < empty_index; i++)
                        Board[row][i+1] = copyArray[row][i];     /*Slide right every element of given row till reach blank space's initial index */      
                }                                                   
            
            break;
            case Direction::LEFT:                           /* LEFT DIRECTION */
                for(i = column - 1 ; i >= 0 ; i--)            /* Check validity of movement by decrementing given index in given row */
                    if( Board[row][i] == 0){  
                        empty_index = i;             /* If the given movement is valid, then take the index of blank space */
                        valid_move = true;
                    }
                if(valid_move == true){
                    Board[row][column] = copyArray[row][empty_index];   /* Change the input's position with blank space's position */
                    for( i = column ; i > empty_index ; i--)
                        Board[row][i-1]=copyArray[row][i];   /* Slide left every element of given row till reach the blank space's initial index*/
                }
            break;
            case Direction::UP:
                for( i = row-1 ; i >=0 ; i--)              /* UP DIRECTION */
                    if( Board[i][column]==0 ){               /* Up movement algorithm is the same with Left movement algorithm*/
                        empty_index = i;                              
                        valid_move = true;             /*The only diffrences are sliding way and constant indexes */                           
                    }
                if( valid_move == true){
                    Board[row][column] = copyArray[empty_index][column];
                        for( i = row ; i > empty_index ; i--)
                            Board[i-1][column]=copyArray[i][column];
                }
            break;
            case Direction::DOWN:                           /* DOWN DIRECTION */
                for( i = row+1 ; i <=2 ; i++)                     /* Up movement algorithm is the same with Left movement algorithm*/
                    if(Board[i][column]==0){       
                        empty_index = i;              /*The only diffrences are sliding way and constant indexes */ 
                        valid_move = true;
                    }
                if( valid_move == true){
                    Board[row][column]=copyArray[empty_index][column];
                    for(i=row; i<empty_index; i++)
                        Board[i+1][column]=copyArray[i][column];
                }   
            break;

            default:
                break;
        }
        if( valid_move == true)
            print( );
    }


    void EightPuzzle:: playAuto( )
    {
        int row = 0, column = 0, direction = 0;
        Direction direct;
        unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()); 
        mt19937 number_generator(seed);
        uniform_int_distribution<int>random_row(0, 2); 
        uniform_int_distribution<int>random_column(0, 2); 
        uniform_int_distribution<int>random_direction(0, 3);
        
        row = random_row(number_generator);
        column = random_column(number_generator);
        direction = random_direction(number_generator);
        if( direction == 0)    
            direct = Direction::LEFT;
        else if(direction == 1)
            direct = Direction::RIGHT;
        else if(direction == 2)
            direct = Direction::UP;
        else if(direction == 3)
            direct = Direction::DOWN;
        
        setMove(direct, row, column);

    }

    
    bool EightPuzzle::endGame( ) const
    
    { 
        bool checkWin = true;
        int counter=1;
        int winCondition[3][3];

        for(int i = 0; i < 3; i++){            /* Create a solved matrix to compare with our number puzzle matrix */
            for(int  j = 0 ; j < 3 ; j++){
                if(j==2 && i==2) 
                    winCondition[i][j] = 0;
                else{
                winCondition[i][j] = counter;
                counter++;
                }
            }
        }
        
        for(int i = 0 ; i < 3 ; i++){           
            for(int j = 0 ; j < 3; j++){                   
                if(winCondition[i][j] != Board[i][j]){
                    checkWin = false;  
                    break;
                }
            }
        }

        return checkWin; /* Return the check_win to check win condition in other functions */
    }

}