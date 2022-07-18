#include"solitaire.h"

int main(){
            
  /* PegSolitaire game(game_board, game_type) */
  /* Constructors's first parameter is game board, second one is game type */
  int menu_choice=0;
  
  PegSolitaire game1(3,1);
  PegSolitaire game2(4,2);
  PegSolitaire game3(5,1);
  PegSolitaire game4(2); /* Game is type is not choosen */
  PegSolitaire game5;   /* Both game board and game type is not choosen (Default game) */
  while(1){                                
    cout<<endl<<"ALL GAME OBJECTS"<<endl;      
    cout<<"1-)"<<endl;
    game1.display_object_info();
    cout<<"2-)"<<endl;
    game2.display_object_info();
    cout<<"3-)"<<endl;
    game3.display_object_info();
    cout<<"4-)"<<endl;
    game4.display_object_info();
    cout<<"5-)"<<endl;
    game5.display_object_info();
    cout<<"6-) EXIT"<<endl;
    
    cout<<endl<<"Total Number of Pegs : "<<PegSolitaire::getTotalPegs()<<endl; //sumTotalPegs function will calculate TotalPegsCount for activated games !!
    PegSolitaire::setToZero();                                               // if object is not choosen/initialized function will not take it into Account
    
    cout<<"Choose your game/object: ";
        cin>>menu_choice;
        while(1){
            if(menu_choice>6 || menu_choice<1){                /* Check user's input */
                cerr<<"Your option is not valid, please enter a valid input!"<<endl;
                cin.clear();
                cin.ignore(256,'\n');
                cout<<"Choose your game/object: ";
                cin>>menu_choice;
            }
            else
                break;
        }  
        cin.ignore();
        cin.clear();
        
        if(menu_choice==1)
            game1.Start();
        else if(menu_choice==2)
            game2.Start();
        else if(menu_choice==3)
            game3.Start();
        else if(menu_choice==4)
            game4.Start();
        else if(menu_choice==5)
            game5.Start();
        else if(menu_choice==6)
            break;

  }
    
    /* I didn't find appropriate position to implement this function , Therefore i will show this function in here */

    if(game1.CompareGames(game2)==true)
        cout<<endl<<"Game1 Object  has more pegs than Game2 Object ";
    else
        cout<<endl<<"Game2 Object has more pegs than Game1 Object ";



    return 0;

}





