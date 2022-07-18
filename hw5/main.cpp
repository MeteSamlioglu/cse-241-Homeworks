#include<iostream>
#include"PegSolitaire.h"
#include"eightpuzzle.h"
#include"Klotski.h"
using namespace std;
using SavitcGames::BoardGame2D;
using SavitcGames::PegSolitaire;
using SavitcGames::EightPuzzle;
using SavitcGames::Klotski;

void testAuto(){ // Computer will play all the games in a row
    vector<BoardGame2D*> v;
    BoardGame2D *P1;
    BoardGame2D *P2;
    BoardGame2D *P3;   
    
    P1 = new PegSolitaire("Computer");
    P2 = new EightPuzzle("Computer");
    P3 = new Klotski("Computer");
    
    v.push_back(P1);
    v.push_back(P3);
    v.push_back(P2);
    
    BoardGame2D::playVector(v);
}
void testUser(){  // Play all games in a row
    vector<BoardGame2D*> v;
    BoardGame2D *P1, *P2, *P3;    
    P1 = new PegSolitaire("Human");
    P2 = new EightPuzzle("Human");
    P3 = new Klotski("Human");
    v.push_back(P2);
    v.push_back(P1);
    v.push_back(P3);
    BoardGame2D::playVector(v);
}
void testMix( ){
    vector<BoardGame2D*> v;
    BoardGame2D *P1, *P2, *P3, *P4, *P5, *P6;    
    P1 = new PegSolitaire("Human");
    P2 = new EightPuzzle("Human");
    P3 = new Klotski("Human");
    P4 = new PegSolitaire("Computer");
    P5 = new EightPuzzle("Computer");
    P6 = new Klotski("Computer");
    v.push_back(P3);
    v.push_back(P2);
    v.push_back(P1);
    v.push_back(P4);
    v.push_back(P5);
    v.push_back(P6);
    BoardGame2D::playVector(v);
}
void playKlotski( ){
    vector<BoardGame2D*>v;
    BoardGame2D *P1, *P2;
    P1 = new Klotski("Human");
    /* P2 = new Klotski("Computer"); */ //for computer game
    v.push_back(P1);
    /* v.push_back(P2); */
    BoardGame2D::playVector(v);
}
void playEightPuzzle( ){
    vector<BoardGame2D*>v;
    BoardGame2D *P1, *P2;
    P1 = new EightPuzzle("Human");
    /* P2 = new EightPuzzle("Human"); */ //for computer game
    v.push_back(P1);
    /* v.push_back(P2); */
    BoardGame2D::playVector(v);
}

void playPegSolitaire( ){
    vector<BoardGame2D*>v;
    BoardGame2D *P1, *P2;
    P1 = new PegSolitaire("Computer");
    /* P2 = new PegSolitaire("Computer"); */ //for computer game
    v.push_back(P1);
    /* v.push_back(P2); */
    BoardGame2D::playVector(v);
}
void testOstream( ){ //testing ostream operator 
    BoardGame2D *P1;
    P1 = new PegSolitaire("Computer");
    P1->start( );
    cout<<endl<<"Final board "<<endl;
    cout<<(*P1);


}
// Note; for playAuto function it takes 5-10 minutes to solve Klotski game
// Score function only works properly for PegSolitaire game, For others I haven't found any way to calculate score 
// You can try every test function they work as expected

// Example inputs 
/*
PegSolitaire -->  b4-U
Klotski ---> S8-U  / RED-D / S9-L
EightPuzzle--> a1-U  / b7-D



*/



int main(){
     testAuto( );
    //testUser( );
    //testMix( );    
    //playKlotski( );
     //playEightPuzzle( );
    //playPegSolitaire( );
    //testOstream( );


}