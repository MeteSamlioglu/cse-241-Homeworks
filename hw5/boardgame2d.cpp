#include"boardgame2d.h"

using namespace std;
namespace SavitcGames{

    BoardGame2D::BoardGame2D( )
        :GameType("No type yet"), score(0)
    {
        //deliberately empty
    }
    BoardGame2D::BoardGame2D(string _GameType)
        :GameType(_GameType), score(0)
    {
        //deliberately empty
    }     


    void BoardGame2D::playUser( ){        
        string move;
        
        print( );
        while(1){
            if(endGame( ) != true){
                cout<<"Make a move : ";
                cin>>move;
                if(isValidInput(move)==true)
                    playUser(move);
            }
            else{
                cout<<"Your score is "<<boardScore( )<<endl;

            }

            cin.clear();
            cin.ignore(256,'\n');
        }
    }
    
    void BoardGame2D::playAutoAll( ){

        print( );
        
        while(1){
            if(endGame( ) != true){
                playAuto( );
                this_thread::sleep_for (chrono::milliseconds(100));
            }
            else{
                cout<<"Your score is "<<boardScore( )<<endl;
                break;
                
            }

        }
   }
   
    void BoardGame2D::start( ){
        int choice = 0;
        string input;
        
        while(1){
            input = getGameType( );
            
            if( input=="Human" ){
                BoardGame2D::playUser( );
                break;
            }
            else if( input == "Computer" ){
                BoardGame2D::playAutoAll( );
                break;
            }
            else{
                cout<<"Choose the game type"<<endl;
                cout<<"1-)Computer Game"<<endl;
                cout<<"2-)Human Game "<<endl;
                cout<<"Choice : ";
                cin>>choice;
                if( choice == 1)
                    setGameType("Computer");
                else if( choice == 2)
                    setGameType("Human");
                else
                    cerr<<"Error!, please choose an exist option "<<endl;   
                cin.clear( );
                cin.ignore( );
            }
        }
    }
    
     ostream& operator<<(ostream& os, const BoardGame2D& Obj){

         Obj.print( );
         return os;

     }
    
    void BoardGame2D::playVector(vector<BoardGame2D*>v){

        for(int i = 0 ; i < v.size(); i++)
            v[i]->start( );
              
    }


    void BoardGame2D::setScore(int _score){
        score = _score;
    }
    int BoardGame2D::boardScore( ) const
    {
        return score;
    }
    string BoardGame2D::getGameType( )const{
        return GameType;
    }
    void BoardGame2D::setGameType(string type)
    {
        GameType = type;
    }

}
