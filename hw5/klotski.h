#ifndef KLOTSKI_H
#define KLOTSKI_H
#include"BoardGame2d.h"
#include<string>
using namespace std;

namespace SavitcGames{
    typedef enum{ WALL , EMPTY,S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, R1, R2, RED, TARGET} KlotskiElements;

    class Klotski : public BoardGame2D
    {
        public:
           Klotski( );
           Klotski(string GameType);
           ~Klotski( );
           Klotski(const Klotski& Obj);
           Klotski& operator=(const Klotski& Obj);             
           
           void initialize( ) override;
           void print( ) const override;
           void playUser(string move) override;
           void setRectMove(KlotskiElements element, Direction direction);
           void setSquareMove(KlotskiElements element, Direction direction);
           void setRedMove(KlotskiElements element, Direction direction);
           void playAuto( ) override;
           bool endGame( ) const override;
           bool isValidInput(string input)const override;
           bool isValidMove(KlotskiElements element, Direction direction) const;
        
        private:
            KlotskiElements **Board;
            int auto_move = 1;

    };




}
#endif