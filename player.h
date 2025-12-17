//
// Created by Jake Power on 3/10/24.
//

#ifndef WORDLE_PLAYER_H
#define WORDLE_PLAYER_H
#include <iostream>
using namespace std;
class Player
{
public:
    friend class Word;
    Player();
    void setName(string );
    string getName() const;
    int calculateScore(int );
    int getScore() const ;
    void addScore(int );
private:
       int score;
       string name;


};
#endif //WORDLE_PLAYER_H
