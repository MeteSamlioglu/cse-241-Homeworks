#include"Klotski.h"
using namespace std;



namespace SavitcGames{
    Klotski::Klotski( )
        :BoardGame2D( )
    {
        Board = new KlotskiElements*[12];
        for(int i = 0; i < 12; i++)
            Board[i] = new KlotskiElements[10];
        
        initialize( );
        //checkGametype( );
        
        
    }
    Klotski::Klotski(string GameType)
        :BoardGame2D(GameType)
    {
        Board = new KlotskiElements*[12];
        for(int i = 0; i < 12; i++)
            Board[i] = new KlotskiElements[10];
        initialize( );
        //checkGametype( );

    }
    Klotski::~Klotski( ){
        for(int i = 0; i < 12; i++)
            delete[] Board[i];
        
        delete [] Board;
    }
    Klotski::Klotski(const Klotski& Obj){
        
        setGameType(Obj.getGameType());
        Board = new KlotskiElements*[12];
        for(int i = 0; i < 12; i++)
            Board[i] = new KlotskiElements[10];
        
        for(int i = 0 ; i < 12; i++)
            for(int j = 0; j < 10; j++)
                Board[i][j] = Obj.Board[i][j];

    }
    Klotski& Klotski::operator=(const Klotski& Obj)
    {
        
        setGameType(Obj.getGameType());
        for(int i = 0 ; i < 12; i++)
            for( int j = 0; j < 10; j++)
                Board[i][j] = Obj.Board[i][j];

        return *this;
    }
    

    void Klotski::initialize( ){
        KlotskiElements gameBoard[12][10] ={    { WALL ,WALL ,WALL ,WALL, WALL, WALL, WALL, WALL, WALL, WALL},
                                                {WALL, S1, S1, RED, RED, RED, RED, S2, S2, WALL},
                                                {WALL, S1, S1, RED, RED, RED, RED, S2, S2, WALL},
                                                {WALL, S3, S3, RED, RED, RED, RED, S4, S4, WALL},
                                                {WALL, S3, S3, RED , RED, RED, RED, S4, S4, WALL},
                                                {WALL, R1, R1, S5, S5, S6, S6, R2, R2, WALL},
                                                {WALL, R1, R1, S5, S5, S6, S6, R2, R2, WALL},
                                                {WALL, R1, R1, S7, S7, S8, S8, R2, R2, WALL},
                                                {WALL, R1, R1, S7, S7, S8, S8, R2, R2, WALL},
                                                {WALL, S9, S9, EMPTY, EMPTY, EMPTY, EMPTY, S0, S0, WALL},
                                                {WALL, S9, S9, EMPTY, EMPTY, EMPTY, EMPTY, S0, S0, WALL},
                                                {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
                                            
                                            };     
        for(int i = 0; i < 12; i++)
            for(int j = 0; j < 10; j++)
                Board[i][j] = gameBoard[i][j];
    
    }
    void Klotski::print( )const{
        
        cout << "\x1b[2J"; 
        cout << "\033[0;0H"; 
        cout << endl << endl;
        
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 10 ; j++){
                if(Board[i][j]== WALL && ( j== 0 || j==9))
                    cout<<"* ";
                else if(Board[i][j]== WALL && (i==0 || i==11))
                    cout<<"* * ";
                
                else if(Board[i][j]== S1)
                    cout<<"S1  ";
                else if(Board[i][j]== S2)
                    cout<<"S2  ";
                 else if(Board[i][j]== S3)
                    cout<<"S3  ";
                else if(Board[i][j]== S4)
                    cout<<"S4  ";
                else if(Board[i][j]==S5)
                    cout<<"S5  ";
                else if( Board[i][j]== S6)
                    cout<<"S6  ";
                else if( Board[i][j]== S7)
                    cout<<"S7  ";    
                else if( Board[i][j]== S8)
                    cout<<"S8  ";
                else if( Board[i][j]== S9)
                    cout<<"S9  ";
                else if( Board[i][j]== S0)
                    cout<<"S0  ";
                else if( Board[i][j]== R1)
                    cout<<"R1  ";
                else if( Board[i][j]== R2)
                    cout<<"R2  ";
                else if( Board[i][j]==RED)
                    cout<<"RED ";
                else if(Board[i][j]== EMPTY)
                    cout<<"    ";
            }   
            cout<<endl;
        }
    }
    
    
    
    bool Klotski::isValidMove(KlotskiElements element, Direction direction) const{
        
        int up_row_index = 0, down_row_index = 0, left_column_index = 0, right_column_index = 0, width = 0, length = 0;
        int empty_width = 0, empty_length = 0;
        bool isFound = false, validity = false;
        
        //Get indexes
        for(int i = 0; i < 12; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if( Board[i][j] == element){
        
                    for(int k = j; Board[i][k] == element; k++ )
                        width++;
                            
                    isFound = true;         
                    up_row_index = i;
                    left_column_index = j;
                    right_column_index = j + width - 1;
                    break;
                }
                    
            }
            if(isFound ==true){
                for(int k = up_row_index; Board[k][left_column_index] == element; k++)
                    length++;
                
                down_row_index = up_row_index + length - 1;
                break;
            }
        }

        // We have all the indexes for regarding element
        switch(direction)
        {
            case Direction::RIGHT:
                for(int i = right_column_index + 1; Board[up_row_index][i] == EMPTY; i++ )
                    empty_width++;

                for(int i = up_row_index; Board[i][right_column_index + 1] == EMPTY; i++)
                    empty_length++;

                break;
            
            case Direction::LEFT:
                for(int i = left_column_index - 1; Board[up_row_index][i] == EMPTY; i--)
                    empty_width++;
                for(int i = up_row_index; Board[i][left_column_index - 1] == EMPTY; i++)
                    empty_length++;
                break;
            
            case Direction::DOWN:
                for(int i = left_column_index ; Board[down_row_index + 1][i] == EMPTY ; i++)
                    empty_width++;
                for(int i = down_row_index + 1; Board[i][left_column_index] == EMPTY; i++)
                    empty_length++;
        
                break;
            
            case Direction::UP:
                for(int i = left_column_index; Board[up_row_index - 1][i] == EMPTY; i++)
                    empty_width++;
                for(int i = up_row_index - 1; Board[i][left_column_index] == EMPTY; i--)
                    empty_length++;
                
                break;
            default:
                
                break;
        }    
        if(element != R1 && element != R2 && element != RED){
            
            if( (length <= empty_length) && ( width <= empty_width ))
                    validity = true;    
        }
        else if(element == R1 || element== R2 || element ==RED){
            
            if(element == RED){
                if( direction == Direction::RIGHT || direction == Direction::LEFT)
                    if( ( length <=empty_length ) && ( width / 2 <=empty_width) )
                        validity = true;
                if( direction == Direction::UP || direction == Direction::DOWN)
                    if( ( length/2 <=empty_length ) && ( width <=empty_width) )
                        validity = true;
            }
            else if(element == R1 || element == R2)
            {
                
                if( Direction::RIGHT == direction || Direction::LEFT == direction)
                    if( ( length <=empty_length ) && ( width / 2 <=empty_width) )
                        validity = true;
                
                 if( Direction::UP == direction || Direction::DOWN == direction)
                    if( ( length / 2 <=empty_length ) && ( width <=empty_width) )
                        validity = true;
                
                
            }

        }
        
        return validity;

    }
    void Klotski::playUser( string move ){
        
        KlotskiElements element;
        Direction direct;

        if(move[3]=='L')
            direct = Direction::LEFT;
        else if(move[3] == 'R')
            direct = Direction::RIGHT;
        else if( move[3] =='U')
            direct = Direction::UP;
        else if( move[3] =='D')
            direct = Direction::DOWN;   


        if(move[0] == 'S' || move[0]=='s'){
              
            int number = 2; // Represents  S1 enum element */
            for(int i = 0; i < ( move[1] - '0'); i++)
                number = number + EMPTY; // S1 + 1
            
            element = static_cast<KlotskiElements>(number);
            
            if(isValidMove(element, direct)== true ){
                setSquareMove(element,direct);
                print( );
            }
            else
                cerr<<"Your move is not legal !" <<endl;
        }
        else if(move[0] =='R' || move[0]=='r'){
            string str = move.substr(0,3);
            
            if(str == "RED" || str=="red"){
                if(move[4]=='L')
                    direct = Direction::LEFT;
                else if(move[4] == 'R')
                    direct = Direction::RIGHT;
                else if( move[4] =='U')
                    direct = Direction::UP;
                else if( move[4] =='D')
                    direct = Direction::DOWN; 
                
                if(isValidMove(RED, direct) == true){
                    setRedMove(RED,direct);
                    print( );
                }
                else
                    cerr<<"Your move is not legal !" <<endl;
            }
            else{
                if(move[1]=='1')
                    if(isValidMove(R1, direct)==true){
                        setRectMove(R1,direct);
                        print( );
                    }
                    else
                        cerr<<"Your move is not legal !" <<endl;
                
                else if(move[1]=='2')
                    if(isValidMove(R2, direct)==true){
                        setRectMove(R2,direct);           
                        print( );
                    }
                    else
                        cerr<<"Your move is not legal !" <<endl;
            }
        }    
        
        

    }
    void Klotski::setRectMove(KlotskiElements element, Direction direction){

        int up_row_index = 0, down_row_index = 0, left_column_index = 0, right_column_index = 0, width = 0, length = 0;
        bool isFound = false;
    
        for(int i = 0; i < 12; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if( Board[i][j] == element){
        
                    for(int k = j; Board[i][k] == element; k++ )
                        width++;
                            
                    isFound = true;         
                    up_row_index = i;
                    left_column_index = j;
                    right_column_index = j + width - 1;
                    break;
                }
                    
            }
            if(isFound ==true){
                for(int k = up_row_index; Board[k][left_column_index] == element; k++)
                    length++;
                
                down_row_index = up_row_index + length - 1;
                break;
            }
        }
        switch(direction){
            
            case Direction::LEFT:
                
                for(int i = up_row_index; i <=down_row_index; i++){
                    Board[i][left_column_index - 1] = element;
                    Board[i][left_column_index - 2] = element;
                }
                for(int i = up_row_index; i<=down_row_index; i++){
                    Board[i][left_column_index] = EMPTY;
                    Board[i][left_column_index + 1] = EMPTY;

                }
                break;
            case Direction::RIGHT:
                for(int i = up_row_index; i <=down_row_index; i++){
                    Board[i][right_column_index + 1] = element;
                    Board[i][right_column_index + 2] = element;
                }
                for(int i = up_row_index; i <= down_row_index; i++){
                    Board[i][right_column_index] = EMPTY;
                    Board[i][right_column_index - 1] = EMPTY;
                }
                break;
            case Direction::UP:
                Board[up_row_index - 1][left_column_index] = element;
                Board[up_row_index - 1][left_column_index + 1] = element;
                Board[up_row_index -2 ] [left_column_index] = element;
                Board[up_row_index - 2] [left_column_index + 1] = element;
                for(int i = up_row_index + 2; i <= down_row_index; i++){
                    Board[i][left_column_index] = EMPTY;
                    Board[i][left_column_index + 1] =EMPTY; 
                }
                break;
            case Direction::DOWN:
                Board[down_row_index + 1][left_column_index] = element;
                Board[down_row_index + 1][left_column_index + 1] = element;
                Board[down_row_index + 2 ] [left_column_index] = element;
                Board[down_row_index + 2] [left_column_index + 1] = element;
                
                for(int i = up_row_index ; i <= (down_row_index - 2) ; i++){
                    Board[i][left_column_index] = EMPTY;
                    Board[i][left_column_index + 1] =EMPTY; 
                }
                break;
        
            default:
                break;
        
        }
    
    }
    
    
    void Klotski::setSquareMove(KlotskiElements element, Direction direction){
        
        int up_row_index = 0, down_row_index = 0, left_column_index = 0, right_column_index = 0, width = 0, length = 0;
        bool isFound = false;
        
        for(int i = 0; i < 12; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if( Board[i][j] == element){
        
                    for(int k = j; Board[i][k] == element; k++ )
                        width++;
                            
                    isFound = true;         
                    up_row_index = i;
                    left_column_index = j;
                    right_column_index = j + width - 1;
                    break;
                }
                    
            }
            if(isFound ==true){
                for(int k = up_row_index; Board[k][left_column_index] == element; k++)
                    length++;
                
                down_row_index = up_row_index + length - 1;
                break;
            }
        }
        
        switch(direction){
            
            case Direction::LEFT:
                
                for(int i = up_row_index ; i <= down_row_index; i++){
                    
                    Board[i][left_column_index  - 1] = element; 
                    Board[i][left_column_index  - 2] = element;
                    Board[i][left_column_index] = EMPTY;
                    Board[i][left_column_index + 1] = EMPTY;
                }
                break;
            case Direction::RIGHT:
                
                for(int i = up_row_index; i <= down_row_index; i++ ){
                    Board[i][right_column_index + 1] = element;
                    Board[i][right_column_index + 2] = element;
                    Board[i][right_column_index] = EMPTY;
                    Board[i][right_column_index - 1] = EMPTY;
                }    
                break;
            case Direction::DOWN :
                    
                    Board[down_row_index + 1][left_column_index] = element;  /* down_row_index + 2 could cause segment problems therfore, i wrote it manually */
                    Board[down_row_index + 1][right_column_index] = element;
                    Board[down_row_index + 2][left_column_index] = element;
                    Board[down_row_index + 2][right_column_index] = element;

                    for(int i = up_row_index; i <=down_row_index; i++){
                        Board[i][left_column_index] = EMPTY;
                        Board[i][right_column_index] = EMPTY;
                    }

                break;
            case Direction::UP:
                    Board[up_row_index - 1][ left_column_index ] = element;
                    Board[up_row_index - 1][ right_column_index] = element;
                    Board[up_row_index - 2][ left_column_index ] = element;
                    Board[up_row_index - 2][ right_column_index] = element;
                    for(int i = up_row_index; i <=down_row_index; i++){
                        Board[i][left_column_index] = EMPTY;
                        Board[i][right_column_index] = EMPTY;
                    }
                break;
            
            default:
                break;

        }
    }
    void Klotski::setRedMove(KlotskiElements element, Direction direction){
        
        int up_row_index = 0, down_row_index = 0, left_column_index = 0, right_column_index = 0, width = 0, length = 0;
        bool isFound = false;
        
        for(int i = 0; i < 12; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if( Board[i][j] == element){
        
                    for(int k = j; Board[i][k] == element; k++ )
                        width++;
                            
                    isFound = true;         
                    up_row_index = i;
                    left_column_index = j;
                    right_column_index = j + width - 1;
                    break;
                }
                    
            }
            if(isFound ==true){
                for(int k = up_row_index; Board[k][left_column_index] == element; k++)
                    length++;
                
                down_row_index = up_row_index + length - 1;
                break;
            }
        
        }
        switch(direction){

            case Direction::LEFT:
                for(int i = up_row_index; i <=down_row_index; i++)
                {
                    Board[i][left_column_index - 1] = element;
                    Board[i][left_column_index - 2] = element;
                }
                for(int i = up_row_index; i <=down_row_index; i++)
                {
                    Board[i][right_column_index] = EMPTY;
                    Board[i][right_column_index -1] = EMPTY;
                }

                break;
            case Direction::RIGHT:
                for(int i = up_row_index; i <=down_row_index; i++)
                {
                    Board[i][right_column_index + 1] = element;
                    Board[i][right_column_index + 2] = element;
                }
                for(int i = up_row_index; i <=down_row_index; i++)
                {
                    Board[i][left_column_index] = EMPTY;
                    Board[i][left_column_index + 1] = EMPTY;
                }
                break;
            case Direction::UP:
                  
                  Board[up_row_index - 1][left_column_index] = element;
                  Board[up_row_index - 1][left_column_index + 1] = element;
                  Board[up_row_index - 1][left_column_index + 2] = element;
                  Board[up_row_index - 1][right_column_index] = element;
                  Board[up_row_index - 2][left_column_index] = element;
                  Board[up_row_index - 2][left_column_index + 1] = element;
                  Board[up_row_index - 2][left_column_index + 2] = element;
                  Board[up_row_index - 2][right_column_index] = element;
                  
                  for(int i = up_row_index + 2; i <=down_row_index; i++){
                    Board[i][left_column_index] = EMPTY;
                    Board[i][left_column_index + 1] = EMPTY;
                    Board[i][left_column_index + 2] = EMPTY;
                    Board[i][right_column_index] = EMPTY; 
                  }
                
                break;
            
            case Direction::DOWN:
                  
                  Board[down_row_index + 1][left_column_index] = element;
                  Board[down_row_index + 1][left_column_index + 1] = element;
                  Board[down_row_index + 1][left_column_index + 2] = element;
                  Board[down_row_index + 1][right_column_index] = element;
                  Board[down_row_index + 2][left_column_index] = element;
                  Board[down_row_index + 2][left_column_index + 1] = element;
                  Board[down_row_index + 2][left_column_index + 2] = element;
                  Board[down_row_index + 2][right_column_index] = element;
                
                for(int i = up_row_index ; i <=(up_row_index + 1); i++){
                    Board[i][left_column_index] = EMPTY;
                    Board[i][left_column_index + 1] = EMPTY;
                    Board[i][left_column_index + 2] = EMPTY;
                    Board[i][right_column_index] = EMPTY; 
                }
                break;
            
            default:
                break;
        }
    
    }
    

    bool Klotski::isValidInput(string input) const {
        
        bool check = false, num_check = false, direction_check = false;
        int num = 0;
        
        if(input[0]=='S' || input[0]=='s'){
            num = input[1] - '0';
            
            for(int i = 0; i <= 9; i++)
                if(i == num){
                    num_check = true  ;
                    break;
                }
            if( input[3]=='R' || input[3]=='L' || input[3]=='U' || input[3]=='D')
                direction_check = true;
            
            if( num_check == true && input.size()==4 && input[2]=='-' && direction_check == true)
                check = true;
            
        }
        else if( input[0]=='R' || input[0]=='r' ){
            string str = input.substr(0, 3);
            
            if(str =="RED" || str=="red"){
                if( input[4]=='R' || input[4]=='L' || input[4]=='U' || input[4]=='D')
                    direction_check = true;
                if(direction_check == true && input[3]=='-')
                    check = true;
            }
            else{
                num = input[1] - '0';
                if( num == 1 || num == 2)
                    num_check = true;
                if( input[3]=='R' || input[3]=='L' || input[3]=='U' || input[3]=='D')
                    direction_check = true;
                if( num_check == true && input.size()==4 && input[2]=='-' && direction_check == true)
                    check = true;
            }
        
        }
        
        if(check == false)
            cerr<<"invalid input !"<<endl;

        return check;

    }
        
    void Klotski::playAuto( ){ // There is only one solution for this board, the move count is 29, Therefore i solved it manually
        
        if(auto_move == 1){
            setSquareMove(S9,Direction::RIGHT);
            print( );
        }
        else if( auto_move == 2)
        {
            setSquareMove(S0, Direction::LEFT);
            print( );
        }
        else if( auto_move == 3)
        {
            setRectMove(R1, Direction::DOWN);
            print( );
        }
        else if( auto_move == 4)
        {
            setRectMove(R2, Direction::DOWN);
            print( );
        }
        else if( auto_move == 5)
        {
            setSquareMove(S5, Direction::LEFT);
            print( );
        }
        else if(auto_move == 6)
        {
            setSquareMove(S6, Direction::RIGHT);
            print( );
        }
        else if( auto_move == 7)
        {
            setRedMove(RED, Direction::DOWN);
            print( );
        }
        else if( auto_move == 8)
        {
            setSquareMove(S1, Direction::RIGHT);
            print( );
        }
        else if(auto_move == 9)
        {
            setSquareMove(S2, Direction::LEFT);
            print( );
        }
        else if(auto_move == 10)
        {
            setSquareMove(S3, Direction::UP);
            print( );
        }
        else if(auto_move == 11)
        {
            setSquareMove(S4, Direction::UP);
            print( );
        }
        else if(auto_move == 12)
        {
            setSquareMove(S5, Direction::UP);
            print( );
        }
        else if(auto_move == 13)
        {
            setSquareMove(S6, Direction::UP);
            print( );
        }
        else if(auto_move == 14)
        {
            setRectMove(R1, Direction::UP);
            print( );
        }
        else if(auto_move == 15)
        {
            setRectMove(R2, Direction::UP);
            print( );
        }
        else if(auto_move == 16)
        {
            setSquareMove(S9, Direction::LEFT);
            print( );
        }
        else if(auto_move == 17)
        {
            setSquareMove(S0, Direction::RIGHT);
            print( );
        }
        else if(auto_move == 18)
        {
            setSquareMove(S7, Direction::DOWN);
            print( );
        }
        else if(auto_move == 19)
        {
            setSquareMove(S8, Direction::DOWN);
            print( );
        }
        else if(auto_move == 20)
        {
            setRedMove(RED, Direction::DOWN);
            print( );
        }
        else if(auto_move == 21)
        {
            setSquareMove(S5, Direction::RIGHT);
            print( );
        }
        else if(auto_move == 22)
        {
            setSquareMove(S6, Direction::LEFT);
            print( );
        }
           else if(auto_move == 23)
        {
            setRectMove(R1, Direction::UP);
            print( );
        }
        else if(auto_move == 24)
        {
            setRectMove(R2, Direction::UP);
            print( );
        }
          else if(auto_move == 25)
        {
            setSquareMove(S9, Direction::UP);
            print( );
        }
        else if(auto_move == 26)
        {
            setSquareMove(S0, Direction::UP);
            print( );
        }
        else if(auto_move == 27)
        {
            setSquareMove(S7, Direction::LEFT);
            print( );
        }
        else if(auto_move == 28)
        {
            setSquareMove(S8, Direction::RIGHT);
            print( );
        }
        else if(auto_move == 29)
        {
            setRedMove(RED, Direction::DOWN);
            print( );
        }
        auto_move++;

    }
    
    
    
    bool Klotski::endGame( ) const{
        
        bool win_condition = true;
        
        for(int i = 7; i <= 10; i++){
        
            for(int j = 3; j < 7; j++){
                if( Board[i][j] != RED ){
                    win_condition = false;
                    break;
                }
            }
        
        }
        
        return win_condition;
    }

}










//  void Klotski::playAuto( ){
        
//         KlotskiElements element;
//         Direction direct;
//         unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
//         mt19937 number_generator(seed);
//         uniform_int_distribution<int>random_element_creator(0, 2);   
//         uniform_int_distribution<int>number_creator(0, 9);
//         uniform_int_distribution<int>number_creator2(1, 2);
//         uniform_int_distribution<int>direction_creator(0, 3);
//         int random_element = random_element_creator(number_generator);
//         int random_direction = direction_creator(number_generator);
        
//         if(random_direction == 0)
//             direct = Direction::LEFT;
//         else if(random_direction == 1)
//             direct = Direction::RIGHT;
//         else if(random_direction == 2)
//             direct = Direction::UP;
//         else if(random_direction == 3)
//             direct = Direction::DOWN;

//         if( random_element == 0){
//             int number = 2; // Represents  S1 enum element */
//             int random_num = number_creator(number_generator);
//             for(int i = 0; i < random_num; i++)
//                 number = number + EMPTY; // S1 + 1
            
//             element = static_cast<KlotskiElements>(number);
//             if(isValidMove(element, direct)== true){
//                 setSquareMove(element,direct);
//                 print( );

//                 }
//         }
//         else if(random_element == 1)
//         {
//             int number2 = number_creator2(number_generator);
//             if(number2 == 1)
//                 element = R1;
//             else if(number2 ==2)
//                 element = R2;
            
//             if(isValidMove(element, direct)== true){
//                 setRectMove(element,direct);
//                 print( );
//             }
//         }
//         else{
//             if(isValidMove(RED, direct)== true){
//                 setRedMove(element,direct);
//                 print( );

//             }
//         }    
    
//     }